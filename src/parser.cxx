#include <parser.hpp>
#include <ast_adapt.hpp>

#include <fstream>
#include <iostream>
#include <optional>
#include <vector>
#include <variant>


#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>
#include <boost/spirit/home/x3.hpp>
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
    using x3::attr;
    using x3::omit;
    
    struct point_tag;
    struct rectangle_tag;
    struct ident_tag;
    struct bit_tag;
    struct bus_tag;
    struct boundary_tag;
    struct routedshape_tag;
    struct obstacles_tag;
    struct width_tag;
    struct buses_tag;
    struct layer_tag;
    struct layers_tag;
    struct track_tag;
    struct tracks_tag;
    struct parameters_tag;
    struct input_tag;

    x3::rule<ident_tag, std::string> const ident = "identifier";
    auto const ident_def = x3::lexeme [ +(x3::alnum | '_' | '<' | '>') ];
    
    x3::rule<point_tag, ast::Point> const point = "point";
    auto const point_def = '(' > uint_ > uint_ > ')';

    x3::rule<rectangle_tag, ast::Rectangle> const rectangle = "rectangle";
    auto const rectangle_def = point > point;

    x3::rule<boundary_tag, ast::Rectangle> const boundary = "boundary";
    auto const boundary_def = lit("DESIGN_BOUNDARY") > rectangle;

    x3::rule<routedshape_tag, ast::RoutedShape> const routedshape = "routedshape";
    auto const routedshape_def = ident-lit("ENDOBSTACLES")-lit("ENDBIT")-lit("ENDTRACKS") > rectangle;

    x3::rule<obstacles_tag, std::vector<ast::RoutedShape>> const obstacles = "obstacles";
    auto const obstacles_def = lit("OBSTACLES") > omit[uint_] > *routedshape > lit("ENDOBSTACLES");

    x3::rule<bit_tag, ast::Bit> const bit = "bit";
    auto const bit_def = lit("BIT") > ident > +routedshape > lit("ENDBIT");

    x3::rule<width_tag, std::vector<int>> const width = "width";
    auto const width_def = lit("WIDTH") > omit[uint_] > +uint_ > lit("ENDWIDTH");

    x3::rule<bus_tag, ast::Bus> const bus = "bus";
    auto const bus_def = lit("BUS") > ident > omit[+uint_] > width > +bit > lit("ENDBUS");

    x3::rule<buses_tag, std::vector<ast::Bus>> const buses = "buses";
    auto const buses_def = lit("BUSES") > omit[uint_] > +bus > lit("ENDBUSES");

    x3::rule<layer_tag, ast::Layer> const layer = "layer";
    auto const layer_def = ident-lit("ENDLAYERS") > ((lit("horizontal") >> attr(true)) | (lit("vertical") >> attr(false))) > uint_;

    x3::rule<layers_tag, std::vector<ast::Layer>> const layers = "layers";
    auto const layers_def = lit("LAYERS") > omit[uint_] > +layer > lit("ENDLAYERS");
    
    x3::rule<track_tag, ast::Track> const track = "track";
    auto const track_def = routedshape > uint_;

    x3::rule<tracks_tag, std::vector<ast::Track>> const tracks = "tracks";
    auto const tracks_def = lit("TRACKS") > omit[uint_] > +track > lit("ENDTRACKS");

    x3::rule<parameters_tag, ast::Parameters> const parameters = "parameters";
    auto const parameters_def = lit("RUNTIME") > uint_ > lit("ALPHA") > uint_ > lit("BETA") > uint_ > lit("GAMMA") > uint_ > lit("DELTA") > uint_ > lit("EPSILON") > uint_;

    x3::rule<input_tag, ast::Input> const input = "input";
    auto const input_def = parameters > boundary > layers > tracks > buses > obstacles;

    BOOST_SPIRIT_DEFINE(ident, point, rectangle, boundary, routedshape, obstacles, bit, width, bus, buses, layer, layers, track, tracks, parameters, input);

    struct input_tag : error_handler {};

    template <typename Iterator>
    std::optional<ast::Input> parse_input(Iterator first, Iterator last) {

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
                parser::input
            ];
            // ;

        ast::Input output;
        bool r = phrase_parse(
            first,                          //  Start Iterator
            last,                           //  End Iterator
            parser,                         //  The Parser
            (space | eol),                  //  The Skip-Parser
            output
        );
        return (r && first == last) ? std::optional<ast::Input>{output} : std::nullopt;
    }

    bool parse() {
        return true;
    }
    
    std::optional<ast::Input> parse_file(const char* filename) {
        std::ifstream input(filename);
        input.unsetf(std::ios::skipws);
        boost::spirit::istream_iterator begin(input);
        boost::spirit::istream_iterator end;
        return parse_input(begin, end);
    }
}
