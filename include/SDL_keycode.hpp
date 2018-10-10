#pragma once
#ifndef _SDL_KEYCODE_HPP
#define _SDL_KEYCODE_HPP

#include "SDL_stdinc.hpp"
#include "SDL_scancode.hpp"

namespace SDL
{
	namespace C
	{
		#include <SDL_keycode.h>
	}

	enum class Keymod : std::underlying_type<C::SDL_Keymod>::type
	{
		NONE		= C::KMOD_NONE,

		LSHIFT		= C::KMOD_LSHIFT,
		RSHIFT		= C::KMOD_RSHIFT,
		SHIFT		= (LSHIFT|RSHIFT),

		LCTRL		= C::KMOD_LCTRL,
		RCTRL		= C::KMOD_RCTRL,
		CTRL		= (LCTRL|RCTRL),

		LALT		= C::KMOD_LALT,
		RALT		= C::KMOD_RALT,
		ALT			= (LALT|RALT),

		LGUI		= C::KMOD_LGUI,
		RGUI		= C::KMOD_RGUI,
		GUI			= (LGUI|RGUI),

		NUM			= C::KMOD_NUM,
		CAPS		= C::KMOD_CAPS,
		MODE		= C::KMOD_MODE,
		RESERVED	= C::KMOD_RESERVED
	};

	ENUM_CLASS_BITWISE( Keymod )
}

#endif
