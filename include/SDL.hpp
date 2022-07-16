#pragma once
#ifndef _SDL_HPP
#define _SDL_HPP

//#define NO_SDL_GLEXT

#include "SDL_stdinc.hpp"

#include "SDL_error.hpp"
#include "SDL_events.hpp"
#include "SDL_render.hpp"
#include "SDL_video.hpp"

#if defined( SDL_VIDEO_OPENGL ) && defined( NO_SDL_GLEXT )
#include "GLEW.hpp"
#endif

/*
#include "SDL_main.h"
#include "SDL_stdinc.h"
#include "SDL_assert.h"
#include "SDL_atomic.h"
#include "SDL_audio.h"
#include "SDL_clipboard.h"
#include "SDL_cpuinfo.h"
#include "SDL_endian.h"
#include "SDL_hints.h"
#include "SDL_loadso.h"
#include "SDL_log.h"
#include "SDL_mutex.h"
#include "SDL_power.h"
#include "SDL_rwops.h"
#include "SDL_thread.h"
#include "SDL_timer.h"
#include "SDL_version.h"
*/

SDL_NAMESPACE_BEGIN
#include <SDL.h>
SDL_NAMESPACE_END

namespace SDL
{
	/// Wait a specified number of milliseconds before returning.
	inline
	void
	Delay( const Uint32 ms ) noexcept
	{
		// TODO move to timer.hpp
		SDL_NAMESPACE::SDL_Delay( ms );
	}

	/// Wait a specified number of milliseconds before returning.
	template<class R, class P>
	inline
	void
	Delay( const std::chrono::duration<R, P> & dur ) noexcept
	{
		// TODO move to timer.hpp
		Uint32 ms = static_cast<Uint32>( std::chrono::duration_cast<std::chrono::milliseconds>( dur ).count() );
		SDL_NAMESPACE::SDL_Delay( ms );
	}

	/// Set a hint with normal priority
	/// returns true if the hint was set, false otherwise
	inline
	bool
	SetHint( const char * name, const char * value ) noexcept
	{
		// TODO move to hints.hpp
		return SDL_NAMESPACE::SDL_SetHint( name, value ) == SDL_NAMESPACE::SDL_TRUE;
	}

	class Init
	{
	public:
		ENUM_CLASS_TYPE( Flags, Uint32 )
		{
			None			= 0,
			Timer			= SDL_INIT_TIMER,
			Audio			= SDL_INIT_AUDIO,
			Video			= SDL_INIT_VIDEO,
			Joystick		= SDL_INIT_JOYSTICK,
			Haptic			= SDL_INIT_HAPTIC,
			GameController	= SDL_INIT_GAMECONTROLLER,
			Events			= SDL_INIT_EVENTS,
			NoParachute		= SDL_INIT_NOPARACHUTE,
			Everything		= SDL_INIT_EVERYTHING
		};

		inline
		Init( const Flags flags = Flags::Everything )
		{
			const int code = SDL_NAMESPACE::SDL_Init( to_underlying( flags ) );
			if( code < 0 )
				THROW_SDL_ERROR( code );
		}

		inline
		~Init() noexcept
		{
			SDL_NAMESPACE::SDL_Quit();
		}
	};

	ENUM_INFO_TYPE( Init::Flags, Uint32 );
	ENUM_BITWISE( Init::Flags );

	// this is just here to determine if static linking worked
	void dummy();
}

#endif
