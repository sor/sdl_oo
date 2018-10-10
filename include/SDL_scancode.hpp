#pragma once
#ifndef _SDL_SCANCODE_HPP
#define _SDL_SCANCODE_HPP

#include "SDL_stdinc.hpp"

namespace SDL
{
	namespace C
	{
		#include <SDL_scancode.h>
	}

	class Scancode
	{
	public:
		// SDL_SCANCODE_*
		enum Code : std::underlying_type<C::SDL_Scancode>::type
		{
			V		= C::SDL_SCANCODE_V,

			ESCAPE	= C::SDL_SCANCODE_ESCAPE,

			F1		= C::SDL_SCANCODE_F1,
			F2		= C::SDL_SCANCODE_F2,
			F3		= C::SDL_SCANCODE_F3,
			F4		= C::SDL_SCANCODE_F4,
			F5		= C::SDL_SCANCODE_F5,
			F6		= C::SDL_SCANCODE_F6,
			F7		= C::SDL_SCANCODE_F7,
			F8		= C::SDL_SCANCODE_F8,
			F9		= C::SDL_SCANCODE_F9,
			F10		= C::SDL_SCANCODE_F10,
			F11		= C::SDL_SCANCODE_F11,
			F12		= C::SDL_SCANCODE_F12,

			RIGHT   = C::SDL_SCANCODE_RIGHT,
			LEFT    = C::SDL_SCANCODE_LEFT,
			DOWN    = C::SDL_SCANCODE_DOWN,
			UP      = C::SDL_SCANCODE_UP,

			NUM     = C::SDL_NUM_SCANCODES
		};
		
	private:
		Code code;

	public:
		__alwaysinline
		/* implicit */
		Scancode( const Code code )
			: code( code )
		{}

		__alwaysinline
		/* implicit */
		Scancode( const C::SDL_Scancode code )
			: code( static_cast<Code>( code ) )
		{}

		__alwaysinline
		bool operator==( const Scancode & other ) const
		{
			return code == other.code;
		}

		__alwaysinline
		bool operator==( const Code & other_code ) const
		{
			return code == other_code;
		}
	};
}

#endif
