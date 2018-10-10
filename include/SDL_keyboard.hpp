#pragma once
#ifndef _SDL_KEYBOARD_HPP
#define _SDL_KEYBOARD_HPP

#include "SDL_stdinc.hpp"
#include "SDL_error.hpp"
#include "SDL_keycode.hpp"
#include "SDL_video.hpp"

namespace SDL
{
	namespace C
	{
		#include <SDL_keyboard.h>
	}

	struct Keysym
	{
		// this one is no ptr
		C::SDL_Keysym self;
		
		__alwaysinline
		Keysym()
		{
			SDL::zerop( &self );
		}

		__alwaysinline
		Keysym( const C::SDL_Keysym & other )
		:	self( other )
		{}

		__alwaysinline
		Scancode::Code
		scancode()
		{
			return static_cast<Scancode::Code>( self.scancode );
		}

		__alwaysinline
		Keymod
		mod()
		{
			return static_cast<Keymod>( self.mod );
		}

		__alwaysinline
		C::SDL_Keycode
		sym()
		{
			return static_cast<C::SDL_Keycode>( self.sym );
		}

		// FIXME: should not be needed in the end
		__alwaysinline
		Keysym &
		operator=( const C::SDL_Keysym & other )
		{
			self = other;
			return *this;
		}
	};

	// FIXME: no class
	__alwaysinline
	const Uint8 * GetKeyboardState( int * numkeys )
	{
		return C::SDL_GetKeyboardState( numkeys );
	}
}

#endif
