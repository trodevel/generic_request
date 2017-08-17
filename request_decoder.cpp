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

// $Revision: 3689 $ $Date:: 2016-04-09 #$ $Author: serge $

#include "request_decoder.h"                // self

#include <stdexcept>                        // std::invalid_argument
#include <boost/algorithm/string/predicate.hpp>     // boost::algorithm::ends_with
#include <boost/algorithm/hex.hpp>                  // boost::unhex

#define MODULENAME      "RequestDecoder"

namespace generic_request
{

bool decode_key_value_x( std::string & new_key, std::string & new_val, const std::string & key, const std::string & val, bool throw_on_error )
{
    new_key = key.substr( 0, key.size() - 2 );

    if( new_key.empty() )
    {
        if( throw_on_error )
        {
            throw std::invalid_argument( ( "name of param '" + key + "' is invalid" ).c_str() );
        }
        else
        {
            return false;
        }
    }

    try
    {
        new_val = boost::algorithm::unhex( val );

        return true;
    }
    catch( std::exception & e )
    {
        if( throw_on_error )
        {
            throw std::invalid_argument( ( "value of '" + key + "' is not hex-encoded" ).c_str() );
        }
        else
        {
            return false;
        }
    }
}

Request decode_request( const Request & r, bool throw_on_error )
{
    const Request::ParamMap  & params = r.get_params();

    Request::ParamMap new_params;

    for( auto & e : params )
    {
        auto & key = e.first;
        auto & val = e.second;

        if( boost::algorithm::ends_with( key, ":X" ) )
        {
            std::string new_key;
            std::string new_val;

            if( decode_key_value_x( new_key, new_val, key, val, throw_on_error ) == false )
                continue;

            new_params.insert( Request::ParamMap::value_type( new_key, new_val ) );
        }
        else
        {
            new_params.insert( Request::ParamMap::value_type( key, val ) );
        }
    }

    return Request( new_params );
}

} // namespace generic_request
