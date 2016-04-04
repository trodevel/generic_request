/*

Request decoder.

Copyright (C) 2015 Sergey Kolevatov

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

// $Revision: 3626 $ $Date:: 2016-04-05 #$ $Author: serge $


#ifndef GENERIC_REQUEST_REQUEST_DECODER_H
#define GENERIC_REQUEST_REQUEST_DECODER_H

#include "request.h"    // Request

namespace generic_request
{

Request decode_request( const Request & r, bool throw_on_error = true );

} // namespace generic_request

#endif // GENERIC_REQUEST_REQUEST_DECODER_H
