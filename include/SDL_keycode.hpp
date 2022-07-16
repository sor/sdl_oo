#pragma once
#ifndef _SDL_KEYCODE_HPP
#define _SDL_KEYCODE_HPP

#include "SDL_stdinc.hpp"

SDL_NAMESPACE_BEGIN
#include <SDL_keycode.h>
SDL_NAMESPACE_END

#include "SDL_scancode.hpp"

namespace SDL
{
	using Keycode = SDL_NAMESPACE::SDL_Keycode;

	// TODO: Port all the SDLK_* to a Keycode enum class

	ENUM_CLASS_BASE( Keymod, SDL_NAMESPACE::SDL_Keymod )
	{
		None		= SDL_NAMESPACE::KMOD_NONE,

		LShift		= SDL_NAMESPACE::KMOD_LSHIFT,
		RShift		= SDL_NAMESPACE::KMOD_RSHIFT,
		Shift		= (LShift|RShift),

		LCtrl		= SDL_NAMESPACE::KMOD_LCTRL,
		RCtrl		= SDL_NAMESPACE::KMOD_RCTRL,
		Ctrl		= (LCtrl|RCtrl),

		LAlt		= SDL_NAMESPACE::KMOD_LALT,
		RAlt		= SDL_NAMESPACE::KMOD_RALT,
		Alt			= (LAlt|RAlt),

		LGui		= SDL_NAMESPACE::KMOD_LGUI,
		RGui		= SDL_NAMESPACE::KMOD_RGUI,
		Gui			= (LGui|RGui),

		Num			= SDL_NAMESPACE::KMOD_NUM,
		Caps		= SDL_NAMESPACE::KMOD_CAPS,
		Mode		= SDL_NAMESPACE::KMOD_MODE,
		Reserved	= SDL_NAMESPACE::KMOD_RESERVED
	};

	ENUM_INFO_BASE( Keymod, SDL_NAMESPACE::SDL_Keymod );
	ENUM_BITWISE( Keymod );
}

#endif
