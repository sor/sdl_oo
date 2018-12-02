#pragma once
#ifndef _SDL_KEYBOARD_HPP
#define _SDL_KEYBOARD_HPP

#include "SDL_stdinc.hpp"

#include "SDL_error.hpp"
#include "SDL_keycode.hpp"
#include "SDL_scancode.hpp"
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
			// TODO: zero instead of zerop
			zerop( &self );
		}

		__alwaysinline /* implicit */
		Keysym( const C::SDL_Keysym & other )
			: self( other )
		{}

		// TODO: maybe return a reference to the original data?
		__alwaysinline
		Scancode
		scancode() const
		{
			return Scancode( self.scancode );
			return static_cast<Scancode::Code>( self.scancode );
		}

		__alwaysinline
		Keymod
		mod() const
		{
			return static_cast<Keymod>( self.mod );
		}

		__alwaysinline
		Keycode
		sym() const
		{
			return static_cast<Keycode>( self.sym );
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
