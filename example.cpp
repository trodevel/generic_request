#include <iostream>

#include "request_parser.h" // to_request()

void test_4( const generic_request::Request & r )
{
    auto & params = r.get_untouched_params();

    std::cout << "untouched params:\n";

    for( auto & p : params )
    {
        std::cout << p.first << " = " << p.second << "\n";
    }
}

int main()
{
    auto r = generic_request::RequestParser::to_request( "A=1&B=2&C=xx,yy,zz&D=1,2,3&E=1,,, 2,3 ,4,&PAR_1=untouched param&PAR_2=another param" );

    std::cout << r.get_param( "A" ) << "\n";
    std::cout << r.get_param( "B" ) << "\n";
    std::cout << r.get_param( "C" ) << "\n";
    std::cout << r.get_param( "D" ) << "\n";
    std::cout << r.get_param( "E" ) << "\n";

    std::vector<std::string>    vs;
    std::vector<uint32_t>       vi;
    std::vector<uint32_t>       vi2;

    r.get_vector( "C", vs );
    r.get_vector_uint32( "D", vi );
    r.get_vector_uint32( "E", vi2 );

    for( auto & s : vs )
    {
        std::cout << s << " ";
    }
    std::cout << "\n";

    for( auto & s : vi )
    {
        std::cout << s << " ";
    }
    std::cout << "\n";

    for( auto & s : vi2 )
    {
        std::cout << s << " ";
    }
    std::cout << "\n";

    test_4( r );

    return 0;
}
