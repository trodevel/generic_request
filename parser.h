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

// $Revision: 12747 $ $Date:: 2020-02-15 #$ $Author: serge $

#ifndef GENERIC_REQUEST_REQUEST_PARSER_H
#define GENERIC_REQUEST_REQUEST_PARSER_H

#include <stdexcept>            // std::runtime_error

#include "request.h"            // Request

namespace generic_request
{

class Parser
{
public:
    struct MalformedRequest: public std::runtime_error
    {
        MalformedRequest( const std::string & str ):
            std::runtime_error( str )
        {}
    };


public:
    static Request   to_request( const std::string & s );
};

} // namespace generic_request

#endif // GENERIC_REQUEST_REQUEST_PARSER_H
