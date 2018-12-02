#pragma once
#ifndef _SDL_VIDEO_HPP
#define _SDL_VIDEO_HPP

#include "SDL_stdinc.hpp"

#include "SDL_rect.hpp"
#include "SDL_surface.hpp"

namespace SDL
{
	namespace C
	{
		#include <SDL_video.h>
	}

	class Window
	{
		using ptr_type = C::SDL_Window;
		std::shared_ptr<ptr_type>	ptr;

		PTR_DELETER( C::SDL_DestroyWindow )

	public:
		PTR_AUTOCAST

		enum class Flags
			: std::underlying_type<C::SDL_WindowFlags>::type
		{
			NONE               = 0,
			FULLSCREEN         = C::SDL_WINDOW_FULLSCREEN,
			OPENGL             = C::SDL_WINDOW_OPENGL,
			SHOWN              = C::SDL_WINDOW_SHOWN,
			HIDDEN             = C::SDL_WINDOW_HIDDEN,
			BORDERLESS         = C::SDL_WINDOW_BORDERLESS,
			RESIZABLE          = C::SDL_WINDOW_RESIZABLE,
			MINIMIZED          = C::SDL_WINDOW_MINIMIZED,
			MAXIMIZED          = C::SDL_WINDOW_MAXIMIZED,
			INPUT_GRABBED      = C::SDL_WINDOW_INPUT_GRABBED,
			INPUT_FOCUS        = C::SDL_WINDOW_INPUT_FOCUS,
			MOUSE_FOCUS        = C::SDL_WINDOW_MOUSE_FOCUS,
			FULLSCREEN_DESKTOP = C::SDL_WINDOW_FULLSCREEN_DESKTOP,
			FOREIGN            = C::SDL_WINDOW_FOREIGN,
			ALLOW_HIGHDPI      = C::SDL_WINDOW_ALLOW_HIGHDPI
		};

		enum class Pos
			: int // they are passed as int by the C functions
		{
			UNDEFINED_MASK	= SDL_WINDOWPOS_UNDEFINED_MASK,
			UNDEFINED		= SDL_WINDOWPOS_UNDEFINED,
			CENTERED_MASK	= SDL_WINDOWPOS_CENTERED_MASK,
			CENTERED		= SDL_WINDOWPOS_CENTERED
		};

		__alwaysinline
		Window() noexcept
			: ptr()
		{}

		__alwaysinline
		Window(	const char *title, Pos x, Pos y, int w, int h, Flags flags ) noexcept
			: ptr( C::SDL_CreateWindow( title, static_cast<int>( x ), static_cast<int>( y ), w, h, static_cast<Uint32>( flags ) ), deleter )
		{}

		__alwaysinline
		~Window() noexcept
		{}
	};

	ENUM_CLASS_BITWISE( Window::Flags )

	namespace GL
	{
		enum class Attr
			: std::underlying_type<C::SDL_GLattr>::type
		{
			RED_SIZE					= C::SDL_GL_RED_SIZE,
			GREEN_SIZE					= C::SDL_GL_GREEN_SIZE,
			BLUE_SIZE					= C::SDL_GL_BLUE_SIZE,
			ALPHA_SIZE					= C::SDL_GL_ALPHA_SIZE,
			BUFFER_SIZE					= C::SDL_GL_BUFFER_SIZE,
			DOUBLEBUFFER				= C::SDL_GL_DOUBLEBUFFER,
			DEPTH_SIZE					= C::SDL_GL_DEPTH_SIZE,
			STENCIL_SIZE				= C::SDL_GL_STENCIL_SIZE,
			ACCUM_RED_SIZE				= C::SDL_GL_ACCUM_RED_SIZE,
			ACCUM_GREEN_SIZE			= C::SDL_GL_ACCUM_GREEN_SIZE,
			ACCUM_BLUE_SIZE				= C::SDL_GL_ACCUM_BLUE_SIZE,
			ACCUM_ALPHA_SIZE			= C::SDL_GL_ACCUM_ALPHA_SIZE,
			STEREO						= C::SDL_GL_STEREO,
			MULTISAMPLEBUFFERS			= C::SDL_GL_MULTISAMPLEBUFFERS,
			MULTISAMPLESAMPLES			= C::SDL_GL_MULTISAMPLESAMPLES,
			ACCELERATED_VISUAL			= C::SDL_GL_ACCELERATED_VISUAL,
			RETAINED_BACKING			= C::SDL_GL_RETAINED_BACKING,
			CONTEXT_MAJOR_VERSION		= C::SDL_GL_CONTEXT_MAJOR_VERSION,
			CONTEXT_MINOR_VERSION		= C::SDL_GL_CONTEXT_MINOR_VERSION,
			CONTEXT_EGL					= C::SDL_GL_CONTEXT_EGL,
			CONTEXT_FLAGS				= C::SDL_GL_CONTEXT_FLAGS,
			CONTEXT_PROFILE_MASK		= C::SDL_GL_CONTEXT_PROFILE_MASK,
			SHARE_WITH_CURRENT_CONTEXT	= C::SDL_GL_SHARE_WITH_CURRENT_CONTEXT,
			FRAMEBUFFER_SRGB_CAPABLE	= C::SDL_GL_FRAMEBUFFER_SRGB_CAPABLE
		};

		enum class ContextProfile
			: std::underlying_type<C::SDL_GLprofile>::type
		{
			CORE			= C::SDL_GL_CONTEXT_PROFILE_CORE,
			COMPATIBILITY	= C::SDL_GL_CONTEXT_PROFILE_COMPATIBILITY,
			ES				= C::SDL_GL_CONTEXT_PROFILE_ES
		};

		enum class SwapInterval
			: int
		{
			LATE_SYNC = -1,
			IMMEDIATE = 0,	// this is the default as well
			SYNC = 1
		};

		__alwaysinline
		int
		SetAttribute( Attr attr, int value ) noexcept
		{
			return C::SDL_GL_SetAttribute( static_cast<C::SDL_GLattr>( attr ), value );
		}
		
		__alwaysinline
		int
		GetAttribute( Attr attr, int *value ) noexcept
		{
			return C::SDL_GL_GetAttribute( static_cast<C::SDL_GLattr>( attr ), value );
		}

		__alwaysinline
		bool
		SetSwapInterval( SwapInterval value ) noexcept
		{
			return C::SDL_GL_SetSwapInterval( static_cast<int>( value ) ) == 0;
		}

		__alwaysinline
		SwapInterval
		GetSwapInterval() noexcept
		{
			return static_cast<SwapInterval>( C::SDL_GL_GetSwapInterval() );
		}

		__alwaysinline
		bool
		ToggleSwapInterval() noexcept
		{
			return SetSwapInterval(
				GetSwapInterval() == SwapInterval::IMMEDIATE
					? SwapInterval::SYNC
					: SwapInterval::IMMEDIATE );
		}
	}
}

#endif
