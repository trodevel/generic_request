/*

Generic Request.

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

// $Revision: 4217 $ $Date:: 2016-07-19 #$ $Author: serge $

#ifndef GENERIC_REQUEST_H
#define GENERIC_REQUEST_H

#include <string>       // std::string
#include <map>
#include <vector>       // std::vector

namespace generic_request
{

class Request
{
    friend class StrHelper;

public:
    typedef std::map< std::string, std::string >    ParamMap;
    typedef ParamMap::key_type                      Param;

public:
    Request();

    Request(
            const ParamMap  & params );

    const ParamMap  & get_params() const;

    const std::string & get_param( const std::string & key ) const;
    bool has_param( const std::string & key ) const;
    bool get_value( const std::string & key, std::string & value ) const;
    bool get_value_uint32( const std::string & key, uint32_t & value ) const;
    bool get_value_uint16( const std::string & key, uint16_t & value ) const;
    bool get_value_uint8( const std::string & key, uint8_t & value ) const;
    bool get_vector( const std::string & key, std::vector<std::string> & v ) const;
    bool get_vector_uint32( const std::string & key, std::vector<uint32_t> & v ) const;

private:
    ParamMap        params_;
};

} // namespace generic_request

#endif // GENERIC_REQUEST_H
