#pragma once
#ifndef _SDL_KEYBOARD_HPP
#define _SDL_KEYBOARD_HPP

#include "SDL_stdinc.hpp"

#include "SDL_error.hpp"
#include "SDL_keycode.hpp"
#include "SDL_scancode.hpp"
#include "SDL_video.hpp"

SDL_NAMESPACE_BEGIN
#include <SDL_keyboard.h>
SDL_NAMESPACE_END

namespace SDL
{
	struct Keysym // TODO derive from SDL_NAMESPACE::SDL_Keysym
	{
		// this one is no ptr
		SDL_NAMESPACE::SDL_Keysym self;
		
		inline
		Keysym()
		{
			// TODO: zero instead of zerop
			zerop( &self );
		}

		/* implicit */ inline
		Keysym( const SDL_NAMESPACE::SDL_Keysym & other )
			: self( other )
		{}

		// TODO: maybe return a reference to the original data?
		inline
		Scancode
		scancode() const
		{
			return static_cast<Scancode>( self.scancode );
		}

		inline
		Keymod
		mod() const
		{
			return static_cast<Keymod>( self.mod );
		}

		inline
		Keycode
		sym() const
		{
			return static_cast<Keycode>( self.sym );
		}

		// FIXME: should not be needed in the end
		inline
		Keysym &
		operator=( const SDL_NAMESPACE::SDL_Keysym & other )
		{
			self = other;
			return *this;
		}
	};

	class Keyboard
	{
	public:
		class State
		{
			const Uint8 * data; // do not free

		public:
			explicit constexpr inline
			State( const Uint8 * data )
				: data( data )
			{}

			constexpr inline
			bool
			operator[]( const Scancode scancode ) const
			{
				// A array element with a value of 1 means that the key is pressed and a value of 0 means that it is not.
				return data[ to_underlying( scancode ) ] == 1;
			}
		};

		static inline
		State GetState( int * numkeys = nullptr )
		{
			return State( SDL_NAMESPACE::SDL_GetKeyboardState( numkeys ) );
		}
	};
}

#endif
