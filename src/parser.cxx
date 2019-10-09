#include <parser.hpp>

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>
#include <fstream>
#include <iostream>
#include <optional>

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>

#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>

namespace x3 = boost::spirit::x3;



namespace parser {
    struct error_handler
    {
        template <typename Iterator, typename Exception, typename Context>
        x3::error_handler_result on_error(
            Iterator& first, Iterator const& last
        , Exception const& x, Context const& context)
        {
            auto& error_handler = x3::get<x3::error_handler_tag>(context).get();
            std::string message = "Error! Expecting: " + x.which() + " here:";
            error_handler(x.where(), message);
            return x3::error_handler_result::fail;
        }
    };
    using x3::phrase_parse;
    using x3::lit;
    using x3::string;
    using x3::uint_;
    
    struct point_tag;
    struct rectangle_tag;
    struct ident_tag;
    struct layer_tag;
    struct path_tag;
    struct bit_tag;
    struct bits_tag;
    struct bus_tag;

    x3::rule<ident_tag, std::string> ident = "identifier";
    auto const ident_def = x3::lexeme [ (x3::alpha | '_') >> *(x3::alnum | '_') ];
    
    x3::rule<point_tag, std::vector<int> > point = "point";
    auto const point_def = '(' > uint_ > uint_ > ')';

    x3::rule<rectangle_tag, std::vector<int> > rectangle = "rectangle";
    auto const rectangle_def = point > point;
    
    x3::rule<layer_tag> layer = "layer";
    auto const layer_def = ident >> (point >> -point);


    x3::rule<path_tag> path = "path";
    auto const path_def = lit("PATH") > uint_ > +layer > lit("ENDPATH");

    x3::rule<bit_tag> bit = "bit";
    auto const bit_def = lit("BIT") > uint_ > path > lit("ENDBIT");

    x3::rule<bits_tag> bits = "bits";
    auto const bits_def = +bit;

    x3::rule<bus_tag> bus = "bus";
    auto const bus_def = lit("BUS") > ident > bits > lit("ENDBUS");


    BOOST_SPIRIT_DEFINE(ident, point, rectangle, layer, path, bit, bits, bus);

    struct bit_tag : error_handler {};
    struct bus_tag : error_handler {};

    template <typename Iterator>
    std::optional<Input> parse_input(Iterator first, Iterator last) {



        using x3::ascii::space;
        using x3::eol;


        // using x3::with;
        // using x3::error_handler_tag;
        using error_handler_type = x3::error_handler<Iterator>;

        // // Our error handler
        error_handler_type error_handler(first, last, std::cerr);

        // Our parser
        auto const parser =
            // we pass our error handler to the parser so we can access
            // it later in our on_error and on_sucess handlers
            x3::with<x3::error_handler_tag>(std::ref(error_handler))
            [
                parser::bus
            ];
            // ;

        Input input;
        bool r = phrase_parse(
            first,                          //  Start Iterator
            last,                           //  End Iterator
            parser,   //  The Parser
            (space | eol)                   //  The Skip-Parser
        );
        return (r && first == last) ? std::optional<Input>{input} : std::nullopt;
    }

    bool parse() {
        return true;
    }
    
    std::optional<Input> parse_file(char* filename) {
        std::ifstream input(filename);
        input.unsetf(std::ios::skipws);
        boost::spirit::istream_iterator begin(input);
        boost::spirit::istream_iterator end;
        return parse_input(begin, end);
    }
}