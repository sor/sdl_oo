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
#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_hints.h"
#include "SDL_loadso.h"
#include "SDL_log.h"
#include "SDL_mutex.h"
#include "SDL_power.h"
#include "SDL_render.h"
#include "SDL_rwops.h"
#include "SDL_thread.h"
#include "SDL_timer.h"
#include "SDL_version.h"
#include "SDL_video.h"
*/

namespace SDL
{
	namespace C
	{
		#include "SDL.h"
	}

	/// Wait a specified number of milliseconds before returning.
	__alwaysinline
	void
	Delay( const Uint32 ms ) noexcept
	{
		C::SDL_Delay( ms );
	}

	/// Wait a specified number of milliseconds before returning.
	template<class R, class P>
	__alwaysinline
	void
	Delay( const std::chrono::duration<R, P> & dur ) noexcept
	{
		Uint32 ms = static_cast<Uint32>( std::chrono::duration_cast<std::chrono::milliseconds>( dur ).count() );
		C::SDL_Delay( ms );
	}

	/// Set a hint with normal priority
	/// returns true if the hint was set, false otherwise
	__alwaysinline
	bool
	SetHint( const char *name, const char *value ) noexcept
	{
		return C::SDL_SetHint( name, value ) == C::SDL_TRUE;
	}

	/**
	* FIXME: add singleton or refcounting
	**/
	class Init
	{
	public:
		enum class Flags : Uint32
		{
			NONE			= 0,
			TIMER			= SDL_INIT_TIMER,
			AUDIO			= SDL_INIT_AUDIO,
			VIDEO			= SDL_INIT_VIDEO,
			JOYSTICK		= SDL_INIT_JOYSTICK,
			HAPTIC			= SDL_INIT_HAPTIC,
			GAMECONTROLLER	= SDL_INIT_GAMECONTROLLER,
			EVENTS			= SDL_INIT_EVENTS,
			NOPARACHUTE		= SDL_INIT_NOPARACHUTE,
			EVERYTHING		= SDL_INIT_EVERYTHING
		};

		__alwaysinline
		void
		initialize( Flags flags = Flags::NONE ) const
		{
			const int code = C::SDL_Init( static_cast<Uint32>( flags ) );
			if( code < 0 )
				THROW_SDL_ERROR( code );
		}

		__alwaysinline
		~Init() noexcept
		{
			C::SDL_Quit();
		}
	};

	__alwaysinline constexpr
	Init::Flags
	operator|( Init::Flags lhs, Init::Flags rhs )
	{
		return static_cast<Init::Flags>( static_cast<Uint32>( lhs ) | static_cast<Uint32>( rhs ) );
	}

	__alwaysinline
	Init::Flags &
	operator|=( Init::Flags & lhs, Init::Flags rhs )
	{
		lhs = static_cast<Init::Flags>( static_cast<Uint32>( lhs ) | static_cast<Uint32>( rhs ) );
		return lhs;
	}

	// this is just here to determine if static linking worked
	void dummy();
}

#endif
