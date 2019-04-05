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

#include "request.h"        // self

#include <sstream>          // std::stringstream
#include <stdexcept>        // std::runtime_error

#include "../utils/to_value.h"  // to_value()

namespace generic_request
{

Request::Request()
{
}

Request::Request(
        const ParamMap  & params ):
            params_( params ),
            untouched_params_( params )

{
}

const Request::ParamMap & Request::get_params() const
{
    return params_;
}

const Request::ParamMap & Request::get_untouched_params() const
{
    return untouched_params_;
}

const std::string & Request::get_param( const std::string & key ) const
{
    static const std::string empty;

    auto it = params_.find( key );

    if( it == params_.end() )
        return empty;

    touch( key );

    return it->second;
}

bool Request::has_param( const std::string & key ) const
{
    return params_.count( key ) > 0;
}

bool Request::get_value( const std::string & key, std::string & value, bool throw_on_error ) const
{
    auto it = params_.find( key );

    if( it == params_.end() )
    {
        if( throw_on_error )
            throw std::runtime_error( "cannot find key '" + key + "'" );

        return false;
    }

    touch( key );
    value = it->second;

    return true;
}

void Request::touch( const std::string & key ) const
{
    untouched_params_.erase( key );
}

template <class T>
bool Request::get_value_converted_t( T * res, const std::string & key, bool throw_on_error ) const
{
    std::string val_str;

    if( get_value( key, val_str, throw_on_error ) == false )
        return false;

    try
    {
        utils::to_value( res, val_str );

        return true;
    }
    catch( std::exception & e )
    {
        if( throw_on_error )
            throw std::runtime_error( "conversion error: key '" + key + "', value '" + val_str + "'" );

        return false;
    }
}

template <class T>
bool Request::get_vector_converted_t( const std::string & key, std::vector<T> & v, bool throw_on_error ) const
{
    std::vector<std::string> vs;

    if( get_vector( key, vs, throw_on_error ) == false )
        return false;

    for( auto & s : vs )
    {
        if( s.empty() == false )
        {
            try
            {
                T value;

                utils::to_value( & value, s );

                v.push_back( value );
            }
            catch( std::exception & e )
            {
                if( throw_on_error )
                    throw std::runtime_error( "vector conversion error: key '" + key + "', value '" + s + "'" );

                return false;
            }
        }
    }
    return true;
}

bool Request::get_value_converted( const std::string & key, double & value, bool throw_on_error ) const
{
    return get_value_converted_t( & value, key, throw_on_error );
}

bool Request::get_value_converted( const std::string & key, float & value, bool throw_on_error ) const
{
    return get_value_converted_t( & value, key, throw_on_error );
}

bool Request::get_value_converted( const std::string & key, uint64_t & value, bool throw_on_error ) const
{
    return get_value_converted_t( & value, key, throw_on_error );
}

bool Request::get_value_converted( const std::string & key, uint32_t & value, bool throw_on_error ) const
{
    return get_value_converted_t( & value, key, throw_on_error );
}

bool Request::get_value_converted( const std::string & key, uint16_t & value, bool throw_on_error ) const
{
    return get_value_converted_t( & value, key, throw_on_error );
}

bool Request::get_value_converted( const std::string & key, uint8_t & value, bool throw_on_error ) const
{
    return get_value_converted_t( & value, key, throw_on_error );
}

bool Request::get_value_converted( const std::string & key, bool & value, bool throw_on_error ) const
{
    return get_value_converted_t( & value, key, throw_on_error );
}

bool Request::get_vector( const std::string & key, std::vector<std::string> & v, bool throw_on_error ) const
{
    std::string val;

    if( get_value( key, val, throw_on_error ) == false )
        return false;

    try
    {
        std::stringstream ss( val );
        std::string s;

        while( getline( ss, s, ',' ) )
        {
            v.push_back( s );
        }
        return true;
    }
    catch( std::exception & e )
    {
        return false;
    }

}

bool Request::get_vector_uint32( const std::string & key, std::vector<uint32_t> & v, bool throw_on_error ) const
{
    return get_vector_converted_t( key, v, throw_on_error );
}


} // namespace generic_request
