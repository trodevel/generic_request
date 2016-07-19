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

#include "request.h"        // self

#include <sstream>          // std::stringstream

namespace generic_request
{

Request::Request()
{
}

Request::Request(
        const ParamMap  & params ):
            params_( params )
{
}

const Request::ParamMap & Request::get_params() const
{
    return params_;
}

const std::string & Request::get_param( const std::string & key ) const
{
    static const std::string empty;

    ParamMap::const_iterator it_end = params_.end();
    ParamMap::const_iterator it = params_.find( key );

    if( it == it_end )
        return empty;

    return it->second;
}

bool Request::has_param( const std::string & key ) const
{
    return params_.count( key ) > 0;
}

bool Request::get_value( const std::string & key, std::string & value ) const
{
    auto it = params_.find( key );

    if( it == params_.end() )
        return false;

    value = it->second;

    return true;
}

bool Request::get_value_uint32( const std::string & key, uint32_t & value ) const
{
    std::string s;

    if( get_value( key, s ) == false )
        return false;

    try
    {
        value = std::stoul( s );
        return true;
    }
    catch( std::exception & e )
    {
        return false;
    }
}

bool Request::get_value_uint16( const std::string & key, uint16_t & value ) const
{
    std::string s;

    if( get_value( key, s ) == false )
        return false;

    try
    {
        value = std::stoul( s );
        return true;
    }
    catch( std::exception & e )
    {
        //( "get_value_uint16: " + key + " is not numerical" );
        return false;
    }
}

bool Request::get_value_uint8( const std::string & key, uint8_t & value ) const
{
    std::string s;

    if( get_value( key, s ) == false )
        return false;

    try
    {
        value = (uint8_t)std::stoul( s );
        return true;
    }
    catch( std::exception & e )
    {
        return false;
    }
}

bool Request::get_vector( const std::string & key, std::vector<std::string> & v ) const
{
    std::string val;

    if( get_value( key, val ) == false )
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

bool Request::get_vector_uint32( const std::string & key, std::vector<uint32_t> & v ) const
{
    std::vector<std::string> vs;

    if( get_vector( key, vs ) == false )
        return false;

    try
    {
        for( auto & s : vs )
        {
            if( s.empty() == false )
            {
                uint32_t value = (uint8_t)std::stoul( s );

                v.push_back( value );
            }
        }
        return true;
    }
    catch( std::exception & e )
    {
        return false;
    }
}


} // namespace generic_request
