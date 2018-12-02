#pragma once
#ifndef _SDL_ERROR_HPP
#define _SDL_ERROR_HPP

#include "SDL_stdinc.hpp"

#define THROW_SDL_ERROR( code )\
	throw SDL::Exception( code, SDL::Error(), __FILE__, __LINE__ )

#define THROW_SDL_EXCEPTION( code, text )\
	throw SDL::Exception( code, text, __FILE__, __LINE__ )

namespace SDL
{
	namespace C
	{
		#include <SDL_error.h>
	}

	static __alwaysinline
	const char *
	Error() noexcept
	{
		return C::SDL_GetError();
	}

	class Exception
	{
		int				code;
		std::string		text;
		const char *	file;
		int				line;

	public:
		__alwaysinline
		Exception( const int code, const char * text ) noexcept
			: code( code ), text( text )
		{}

		__alwaysinline
		Exception( const int code, const char * text, const char * file, int line ) noexcept
			: code( code ), text( text ), file( file ), line( line )
		{}

		/*
		__alwaysinline
		Exception( const int code, const std::string & text ) noexcept
		:	code( code ), text( text )
		{}
		*/

		__alwaysinline
		int
		Code() const noexcept
		{
			return code;
		}

		__alwaysinline
		std::string &
		Text() noexcept
		{
			return text;
		}

		__alwaysinline
		const std::string &
		Text() const noexcept
		{
			return text;
		}
	};
}

#endif
