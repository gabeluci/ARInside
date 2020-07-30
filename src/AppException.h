//Copyright (C) 2009 Stefan Nerlich | stefan.nerlich@hotmail.com
//
//This file is part of ARInside.
//
//    ARInside is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, version 2 of the License.
//
//    ARInside is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

#pragma once
#include <exception>
#include <string>

class AppException : public std::exception
{
public:

	/**
	* Constructor.
	* \param text - The text of the exception.
	* \param id - The text identifying the argument source.
	* \param td - Text describing the type of ArgException it is.
	* of the exception.
	*/
	AppException( const std::string& text = "undefined exception", 
		const std::string& id = "undefined",
		const std::string& td = "Generic AppException")
		: std::exception(), 
		_errorText(text), 
		_argId( id ), 
		_typeDescription(td)
	{ 
	} 

	virtual ~AppException() throw() 
	{ 
	}

	string error() const 
	{ 
		return ( _errorText ); 
	}

	std::string argId() const  
	{ 
		if ( _argId == "undefined" )
			return " ";
		else
			return ( "Argument: " + _argId ); 
	}

	const char* what() const throw() 
	{
		static std::string ex; 
		ex = _argId + " -- " + _errorText;
		return ex.c_str();
	}

	std::string typeDescription() const
	{
		return _typeDescription; 
	}


private:
	std::string _errorText;
	std::string _argId;
	std::string _typeDescription;
};
