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
		enum Code
			: std::underlying_type<C::SDL_Scancode>::type
		{
			A		= C::SDL_SCANCODE_A,
			B		= C::SDL_SCANCODE_B,
			C		= C::SDL_SCANCODE_C,
			D		= C::SDL_SCANCODE_D,
			E		= C::SDL_SCANCODE_E,
			F		= C::SDL_SCANCODE_F,
			G		= C::SDL_SCANCODE_G,
			H		= C::SDL_SCANCODE_H,
			I		= C::SDL_SCANCODE_I,
			J		= C::SDL_SCANCODE_J,
			K		= C::SDL_SCANCODE_K,
			L		= C::SDL_SCANCODE_L,
			M		= C::SDL_SCANCODE_M,
			N		= C::SDL_SCANCODE_N,
			O		= C::SDL_SCANCODE_O,
			P		= C::SDL_SCANCODE_P,
			Q		= C::SDL_SCANCODE_Q,
			R		= C::SDL_SCANCODE_R,
			S		= C::SDL_SCANCODE_S,
			T		= C::SDL_SCANCODE_T,
			U		= C::SDL_SCANCODE_U,
			V		= C::SDL_SCANCODE_V,
			W		= C::SDL_SCANCODE_W,
			X		= C::SDL_SCANCODE_X,
			Y		= C::SDL_SCANCODE_Y,
			Z		= C::SDL_SCANCODE_Z,

			_1		= C::SDL_SCANCODE_1,
			_2		= C::SDL_SCANCODE_2,
			_3		= C::SDL_SCANCODE_3,
			_4		= C::SDL_SCANCODE_4,
			_5		= C::SDL_SCANCODE_5,
			_6		= C::SDL_SCANCODE_6,
			_7		= C::SDL_SCANCODE_7,
			_8		= C::SDL_SCANCODE_8,
			_9		= C::SDL_SCANCODE_9,
			_0		= C::SDL_SCANCODE_0,

			RETURN	= C::SDL_SCANCODE_RETURN,
			ESCAPE	= C::SDL_SCANCODE_ESCAPE,
			BACKSPACE= C::SDL_SCANCODE_BACKSPACE,
			TAB		= C::SDL_SCANCODE_TAB,
			SPACE	= C::SDL_SCANCODE_SPACE,

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

			RIGHT	= C::SDL_SCANCODE_RIGHT,
			LEFT	= C::SDL_SCANCODE_LEFT,
			DOWN	= C::SDL_SCANCODE_DOWN,
			UP		= C::SDL_SCANCODE_UP,

			KP_DIVIDE	= C::SDL_SCANCODE_KP_DIVIDE,
			KP_MULTIPLY	= C::SDL_SCANCODE_KP_MULTIPLY,
			KP_MINUS	= C::SDL_SCANCODE_KP_MINUS,
			KP_PLUS		= C::SDL_SCANCODE_KP_PLUS,
			KP_ENTER	= C::SDL_SCANCODE_KP_ENTER,
			KP_1		= C::SDL_SCANCODE_KP_1,
			KP_2		= C::SDL_SCANCODE_KP_2,
			KP_3		= C::SDL_SCANCODE_KP_3,
			KP_4		= C::SDL_SCANCODE_KP_4,
			KP_5		= C::SDL_SCANCODE_KP_5,
			KP_6		= C::SDL_SCANCODE_KP_6,
			KP_7		= C::SDL_SCANCODE_KP_7,
			KP_8		= C::SDL_SCANCODE_KP_8,
			KP_9		= C::SDL_SCANCODE_KP_9,
			KP_0		= C::SDL_SCANCODE_KP_0,
			KP_PERIOD	= C::SDL_SCANCODE_KP_PERIOD,

			LCTRL	= C::SDL_SCANCODE_LCTRL,
			LSHIFT	= C::SDL_SCANCODE_LSHIFT,
			LALT	= C::SDL_SCANCODE_LALT,	/**< alt, option */
			LGUI	= C::SDL_SCANCODE_LGUI,	/**< windows, command (apple), meta */
			RCTRL	= C::SDL_SCANCODE_RCTRL,
			RSHIFT	= C::SDL_SCANCODE_RSHIFT,
			RALT	= C::SDL_SCANCODE_RALT,	/**< alt gr, option */
			RGUI	= C::SDL_SCANCODE_RGUI,	/**< windows, command (apple), meta */

			NUM		= C::SDL_NUM_SCANCODES,
			COUNT	= C::SDL_NUM_SCANCODES
		};

	private:
		Code code;

	public:
		/* implicit */ constexpr __alwaysinline
		Scancode( const Code code )
			: code( code )
		{}

		/* implicit */ constexpr __alwaysinline
		Scancode( const C::SDL_Scancode code )
			: code( static_cast<Code>( code ) )
		{}

		constexpr __alwaysinline
		bool
		operator == ( const Scancode & other ) const
		{
			return code == other.code;
		}

		constexpr __alwaysinline
		bool
		operator != ( const Scancode & other ) const
		{
			return code != other.code;
		}

		constexpr __alwaysinline
		bool
		operator == ( const Code & other_code ) const
		{
			return code == other_code;
		}

		constexpr __alwaysinline
		bool
		operator != ( const Code & other_code ) const
		{
			return code != other_code;
		}
	};
}

#endif
