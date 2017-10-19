/*

Request Parser.

Copyright (C) 2014 Sergey Kolevatov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

// $Revision: 3617 $ $Date:: 2016-04-03 #$ $Author: serge $

#include "request_parser.h"         // self

#include "../utils/tokenizer.h"     // boost wrapper
#include "../utils/trim.h"          // trim

namespace generic_request
{

Request RequestParser::to_request( const std::string & str )
{
    std::vector< std::string > pars;
    tokenize_to_vector( pars, str, "&" );

    Request::ParamMap    params;

    for( auto & s: pars )
    {
        std::vector< std::string > key_value;
        tokenize_to_vector( key_value, s, "=" );

        if( key_value.size() != 2 )
            continue;

        const std::string & k = trim( key_value[0] );
        const std::string & v = trim( key_value[1] );

        params[ k ] = v;
    }

    Request res( params );

    return res;

}

} // namespace generic_request
