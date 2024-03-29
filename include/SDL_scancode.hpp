#pragma once
#ifndef _SDL_SCANCODE_HPP
#define _SDL_SCANCODE_HPP

#include "SDL_stdinc.hpp"

SDL_NAMESPACE_BEGIN
#include <SDL_scancode.h>
SDL_NAMESPACE_END

namespace SDL
{
	ENUM_CLASS_BASE( Scancode, SDL_NAMESPACE::SDL_Scancode )
	{
		A           = SDL_NAMESPACE::SDL_SCANCODE_A,
		B           = SDL_NAMESPACE::SDL_SCANCODE_B,
		C           = SDL_NAMESPACE::SDL_SCANCODE_C,
		D           = SDL_NAMESPACE::SDL_SCANCODE_D,
		E           = SDL_NAMESPACE::SDL_SCANCODE_E,
		F           = SDL_NAMESPACE::SDL_SCANCODE_F,
		G           = SDL_NAMESPACE::SDL_SCANCODE_G,
		H           = SDL_NAMESPACE::SDL_SCANCODE_H,
		I           = SDL_NAMESPACE::SDL_SCANCODE_I,
		J           = SDL_NAMESPACE::SDL_SCANCODE_J,
		K           = SDL_NAMESPACE::SDL_SCANCODE_K,
		L           = SDL_NAMESPACE::SDL_SCANCODE_L,
		M           = SDL_NAMESPACE::SDL_SCANCODE_M,
		N           = SDL_NAMESPACE::SDL_SCANCODE_N,
		O           = SDL_NAMESPACE::SDL_SCANCODE_O,
		P           = SDL_NAMESPACE::SDL_SCANCODE_P,
		Q           = SDL_NAMESPACE::SDL_SCANCODE_Q,
		R           = SDL_NAMESPACE::SDL_SCANCODE_R,
		S           = SDL_NAMESPACE::SDL_SCANCODE_S,
		T           = SDL_NAMESPACE::SDL_SCANCODE_T,
		U           = SDL_NAMESPACE::SDL_SCANCODE_U,
		V           = SDL_NAMESPACE::SDL_SCANCODE_V,
		W           = SDL_NAMESPACE::SDL_SCANCODE_W,
		X           = SDL_NAMESPACE::SDL_SCANCODE_X,
		Y           = SDL_NAMESPACE::SDL_SCANCODE_Y,
		Z           = SDL_NAMESPACE::SDL_SCANCODE_Z,

		_1          = SDL_NAMESPACE::SDL_SCANCODE_1,
		_2          = SDL_NAMESPACE::SDL_SCANCODE_2,
		_3          = SDL_NAMESPACE::SDL_SCANCODE_3,
		_4          = SDL_NAMESPACE::SDL_SCANCODE_4,
		_5          = SDL_NAMESPACE::SDL_SCANCODE_5,
		_6          = SDL_NAMESPACE::SDL_SCANCODE_6,
		_7          = SDL_NAMESPACE::SDL_SCANCODE_7,
		_8          = SDL_NAMESPACE::SDL_SCANCODE_8,
		_9          = SDL_NAMESPACE::SDL_SCANCODE_9,
		_0          = SDL_NAMESPACE::SDL_SCANCODE_0,

		Return      = SDL_NAMESPACE::SDL_SCANCODE_RETURN,
		Escape      = SDL_NAMESPACE::SDL_SCANCODE_ESCAPE,
		Backspace   = SDL_NAMESPACE::SDL_SCANCODE_BACKSPACE,
		Tab         = SDL_NAMESPACE::SDL_SCANCODE_TAB,
		Space       = SDL_NAMESPACE::SDL_SCANCODE_SPACE,

		F1          = SDL_NAMESPACE::SDL_SCANCODE_F1,
		F2          = SDL_NAMESPACE::SDL_SCANCODE_F2,
		F3          = SDL_NAMESPACE::SDL_SCANCODE_F3,
		F4          = SDL_NAMESPACE::SDL_SCANCODE_F4,
		F5          = SDL_NAMESPACE::SDL_SCANCODE_F5,
		F6          = SDL_NAMESPACE::SDL_SCANCODE_F6,
		F7          = SDL_NAMESPACE::SDL_SCANCODE_F7,
		F8          = SDL_NAMESPACE::SDL_SCANCODE_F8,
		F9          = SDL_NAMESPACE::SDL_SCANCODE_F9,
		F10         = SDL_NAMESPACE::SDL_SCANCODE_F10,
		F11         = SDL_NAMESPACE::SDL_SCANCODE_F11,
		F12         = SDL_NAMESPACE::SDL_SCANCODE_F12,

		Right       = SDL_NAMESPACE::SDL_SCANCODE_RIGHT,
		Left        = SDL_NAMESPACE::SDL_SCANCODE_LEFT,
		Down        = SDL_NAMESPACE::SDL_SCANCODE_DOWN,
		Up          = SDL_NAMESPACE::SDL_SCANCODE_UP,

		KP_Divide   = SDL_NAMESPACE::SDL_SCANCODE_KP_DIVIDE,
		KP_Multiply = SDL_NAMESPACE::SDL_SCANCODE_KP_MULTIPLY,
		KP_Minus    = SDL_NAMESPACE::SDL_SCANCODE_KP_MINUS,
		KP_Plus     = SDL_NAMESPACE::SDL_SCANCODE_KP_PLUS,
		KP_Enter    = SDL_NAMESPACE::SDL_SCANCODE_KP_ENTER,
		KP_1        = SDL_NAMESPACE::SDL_SCANCODE_KP_1,
		KP_2        = SDL_NAMESPACE::SDL_SCANCODE_KP_2,
		KP_3        = SDL_NAMESPACE::SDL_SCANCODE_KP_3,
		KP_4        = SDL_NAMESPACE::SDL_SCANCODE_KP_4,
		KP_5        = SDL_NAMESPACE::SDL_SCANCODE_KP_5,
		KP_6        = SDL_NAMESPACE::SDL_SCANCODE_KP_6,
		KP_7        = SDL_NAMESPACE::SDL_SCANCODE_KP_7,
		KP_8        = SDL_NAMESPACE::SDL_SCANCODE_KP_8,
		KP_9        = SDL_NAMESPACE::SDL_SCANCODE_KP_9,
		KP_0        = SDL_NAMESPACE::SDL_SCANCODE_KP_0,
		KP_Period   = SDL_NAMESPACE::SDL_SCANCODE_KP_PERIOD,

		LCtrl       = SDL_NAMESPACE::SDL_SCANCODE_LCTRL,
		LShift      = SDL_NAMESPACE::SDL_SCANCODE_LSHIFT,
		LAlt        = SDL_NAMESPACE::SDL_SCANCODE_LALT,    /**< alt, option */
		LGui        = SDL_NAMESPACE::SDL_SCANCODE_LGUI,    /**< windows, command (apple), meta */
		RCtrl       = SDL_NAMESPACE::SDL_SCANCODE_RCTRL,
		RShift      = SDL_NAMESPACE::SDL_SCANCODE_RSHIFT,
		RAlt        = SDL_NAMESPACE::SDL_SCANCODE_RALT,    /**< alt gr, option */
		RGui        = SDL_NAMESPACE::SDL_SCANCODE_RGUI,    /**< windows, command (apple), meta */
		Mode        = SDL_NAMESPACE::SDL_SCANCODE_MODE,

		// TODO, missing codes

		Num         = SDL_NAMESPACE::SDL_NUM_SCANCODES,
		Count       = SDL_NAMESPACE::SDL_NUM_SCANCODES
	};

	ENUM_INFO_BASE( Scancode, SDL_NAMESPACE::SDL_Scancode );
}

#endif
