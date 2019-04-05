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

// $Revision: 10772 $ $Date:: 2019-04-05 #$ $Author: serge $

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
    const ParamMap  & get_untouched_params() const;

    const std::string & get_param( const std::string & key ) const;
    bool has_param( const std::string & key ) const;
    bool get_value( const std::string & key, std::string & value, bool throw_on_error = false ) const;
    bool get_value_converted( const std::string & key, double & value, bool throw_on_error = false ) const;
    bool get_value_converted( const std::string & key, float & value, bool throw_on_error = false ) const;
    bool get_value_converted( const std::string & key, uint64_t & value, bool throw_on_error = false ) const;
    bool get_value_converted( const std::string & key, uint32_t & value, bool throw_on_error = false ) const;
    bool get_value_converted( const std::string & key, uint16_t & value, bool throw_on_error = false ) const;
    bool get_value_converted( const std::string & key, uint8_t & value, bool throw_on_error = false ) const;
    bool get_value_converted( const std::string & key, bool & value, bool throw_on_error = false ) const;
    bool get_vector( const std::string & key, std::vector<std::string> & v, bool throw_on_error = false ) const;
    bool get_vector_uint32( const std::string & key, std::vector<uint32_t> & v, bool throw_on_error = false ) const;

private:

    void touch( const std::string & key ) const;

    template <class T>
    bool get_value_converted_t( T * res, const std::string & key_name, bool throw_on_error ) const;

    template <class T>
    bool get_vector_converted_t( const std::string & key, std::vector<T> & v, bool throw_on_error ) const;

private:
    ParamMap            params_;
    mutable ParamMap    untouched_params_;
};

} // namespace generic_request

#endif // GENERIC_REQUEST_H
