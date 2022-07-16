#pragma once
#ifndef _SDL_ERROR_HPP
#define _SDL_ERROR_HPP

#include "SDL_stdinc.hpp"

#define THROW_SDL_ERROR( code )\
	throw SDL::Exception( code, SDL::Error(), __FILE__, __LINE__ )

#define THROW_SDL_EXCEPTION( code, text )\
	throw SDL::Exception( code, text, __FILE__, __LINE__ )

SDL_NAMESPACE_BEGIN
#include <SDL_error.h>
SDL_NAMESPACE_END

namespace SDL
{
	static inline
	const char *
	Error() noexcept
	{
		return SDL_NAMESPACE::SDL_GetError();
	}

	class Exception
	{
		int				code;
		std::string		text;
		const char *	file;
		int				line;

	public:
		inline
		Exception( const int code, const char * text ) noexcept
			: code( code ), text( text )
		{}

		inline
		Exception( const int code, const char * text, const char * file, int line ) noexcept
			: code( code ), text( text ), file( file ), line( line )
		{}

		/*
		inline
		Exception( const int code, const std::string & text ) noexcept
		:	code( code ), text( text )
		{}
		*/

		inline
		int
		Code() const noexcept
		{
			return code;
		}

		inline
		std::string &
		Text() noexcept
		{
			return text;
		}

		inline
		const std::string &
		Text() const noexcept
		{
			return text;
		}
	};
}

#endif
