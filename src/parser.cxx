#include <parser.hpp>

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>
#include <fstream>


template <typename Iterator>
bool parse_input(Iterator first, Iterator last) {
    using namespace boost::spirit;

    using x3::phrase_parse;
    using x3::ascii::space;
    using x3::lit;
    using x3::string;
    using x3::uint_;
    using x3::eol;

    auto ident = x3::lexeme [ (x3::alpha | '_') >> *(x3::alnum | '_') ];
    auto point     = x3::rule<struct _, std::vector<int> >{} = '(' >> uint_ >> ',' >> uint_ >> ')';
    auto rectangle = x3::rule<struct _, std::vector<int> >{} = point >> point;
    auto layer = ident >> (point | rectangle);
    auto path = lit("PATH") >> uint_ >> (+layer) >> lit("ENDPATH");
    auto bit = lit("BIT") >> ident >> path >> lit("ENDBIT");
    auto bits = +bit;
    auto bus = lit("BUS") >> ident >> bits >> lit("ENDBUS");


    bool r = phrase_parse(
        first,                          //  Start Iterator
        last,                           //  End Iterator
        bit,   //  The Parser
        (space | eol)                   //  The Skip-Parser
    );
    if (first != last) // fail if we did not get a full match
        return false;
    return true;
}

bool parse() {
    return true;
}
 
bool parse_file(char* filename) {
    std::ifstream input(filename);
    // input.unsetf(std::ios::skipws);
    boost::spirit::istream_iterator begin(input);
    boost::spirit::istream_iterator end;
    return parse_input(begin, end);
}