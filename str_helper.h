/*

String Helper. Provides to_string() function.

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

// $Revision: 3689 $ $Date:: 2016-04-09 #$ $Author: serge $

#ifndef GENERIC_REQUEST_STR_HELPER_H
#define GENERIC_REQUEST_STR_HELPER_H

#include "request.h"            // Request

namespace generic_request
{

class StrHelper
{
public:
    static std::string to_string( const Request & l );

private:
    static std::string to_string( const Request::ParamMap & l );
    static std::string to_string( const Request::ParamMap::value_type & l );
};

} // namespace generic_request

#endif // GENERIC_REQUEST_STR_HELPER_H
