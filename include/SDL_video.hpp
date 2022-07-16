#pragma once
#ifndef _SDL_VIDEO_HPP
#define _SDL_VIDEO_HPP

#include "SDL_stdinc.hpp"

#include "SDL_rect.hpp"
#include "SDL_surface.hpp"

SDL_NAMESPACE_BEGIN
#include <SDL_video.h>
SDL_NAMESPACE_END

namespace SDL
{
	// add virtual dtor if final gets removed
	class Window final
	{
		using ptr_type = SDL_NAMESPACE::SDL_Window;
		std::shared_ptr<ptr_type>	ptr;

		PTR_DELETER( SDL_NAMESPACE::SDL_DestroyWindow )

	public:
		PTR_AUTOCAST

		ENUM_CLASS_BASE( Flags, SDL_NAMESPACE::SDL_WindowFlags )
		{
			None                = 0,
			Fullscreen          = SDL_NAMESPACE::SDL_WINDOW_FULLSCREEN,
			FullscreenDesktop   = SDL_NAMESPACE::SDL_WINDOW_FULLSCREEN_DESKTOP,
			OpenGL              = SDL_NAMESPACE::SDL_WINDOW_OPENGL,
			Vulkan              = SDL_NAMESPACE::SDL_WINDOW_VULKAN,
			Metal               = SDL_NAMESPACE::SDL_WINDOW_METAL,
			Shown               = SDL_NAMESPACE::SDL_WINDOW_SHOWN,
			Hidden              = SDL_NAMESPACE::SDL_WINDOW_HIDDEN,
			Borderless          = SDL_NAMESPACE::SDL_WINDOW_BORDERLESS,
			Resizable           = SDL_NAMESPACE::SDL_WINDOW_RESIZABLE,
			Minimized           = SDL_NAMESPACE::SDL_WINDOW_MINIMIZED,
			Maximized           = SDL_NAMESPACE::SDL_WINDOW_MAXIMIZED,
			InputGrabbed        = SDL_NAMESPACE::SDL_WINDOW_INPUT_GRABBED,
			InputFocus          = SDL_NAMESPACE::SDL_WINDOW_INPUT_FOCUS,
			MouseGrabbed        = SDL_NAMESPACE::SDL_WINDOW_MOUSE_GRABBED, // same as Input_Grabbed
			MouseFocus          = SDL_NAMESPACE::SDL_WINDOW_MOUSE_FOCUS,
			MouseCapture        = SDL_NAMESPACE::SDL_WINDOW_MOUSE_CAPTURE,
			KeyboardGrabbed     = SDL_NAMESPACE::SDL_WINDOW_KEYBOARD_GRABBED,
			Foreign             = SDL_NAMESPACE::SDL_WINDOW_FOREIGN,
			AllowHighDPI        = SDL_NAMESPACE::SDL_WINDOW_ALLOW_HIGHDPI,
			AlwaysOnTop         = SDL_NAMESPACE::SDL_WINDOW_ALWAYS_ON_TOP,
			SkipTaskbar         = SDL_NAMESPACE::SDL_WINDOW_SKIP_TASKBAR,
			Utility             = SDL_NAMESPACE::SDL_WINDOW_UTILITY,
			Tooltip             = SDL_NAMESPACE::SDL_WINDOW_TOOLTIP,
			PopupMenu           = SDL_NAMESPACE::SDL_WINDOW_POPUP_MENU,
		};

		ENUM_CLASS_TYPE( Pos, int ) // they are passed as int by the C functions
		{
			Undefined           = SDL_WINDOWPOS_UNDEFINED,
			Centered            = SDL_WINDOWPOS_CENTERED,
		};

		constexpr Window() noexcept = default;
		Window(const char *title, Pos x, Pos y, int w, int h, Flags flags) noexcept;

		void SetTitle(const std::string & title) noexcept;
		void SetTitle(const char * title) noexcept;
	};

	namespace GL
	{
		ENUM_CLASS_BASE( Attr, SDL_NAMESPACE::SDL_GLattr )
		{
			RedSize                     = SDL_NAMESPACE::SDL_GL_RED_SIZE,
			GreenSize                   = SDL_NAMESPACE::SDL_GL_GREEN_SIZE,
			BlueSize                    = SDL_NAMESPACE::SDL_GL_BLUE_SIZE,
			AlphaSize                   = SDL_NAMESPACE::SDL_GL_ALPHA_SIZE,
			BufferSize                  = SDL_NAMESPACE::SDL_GL_BUFFER_SIZE,
			DoubleBuffer                = SDL_NAMESPACE::SDL_GL_DOUBLEBUFFER,
			DepthSize                   = SDL_NAMESPACE::SDL_GL_DEPTH_SIZE,
			StencilSize                 = SDL_NAMESPACE::SDL_GL_STENCIL_SIZE,
			AccumRedSize                = SDL_NAMESPACE::SDL_GL_ACCUM_RED_SIZE,
			AccumGreenSize              = SDL_NAMESPACE::SDL_GL_ACCUM_GREEN_SIZE,
			AccumBlueSize               = SDL_NAMESPACE::SDL_GL_ACCUM_BLUE_SIZE,
			AccumAlphaSize              = SDL_NAMESPACE::SDL_GL_ACCUM_ALPHA_SIZE,
			Stereo                      = SDL_NAMESPACE::SDL_GL_STEREO,
			MultisampleBuffers          = SDL_NAMESPACE::SDL_GL_MULTISAMPLEBUFFERS,
			MultisampleSamples          = SDL_NAMESPACE::SDL_GL_MULTISAMPLESAMPLES,
			AcceleratedVisual           = SDL_NAMESPACE::SDL_GL_ACCELERATED_VISUAL,
			RetainedBacking             = SDL_NAMESPACE::SDL_GL_RETAINED_BACKING,
			ContextMajorVersion         = SDL_NAMESPACE::SDL_GL_CONTEXT_MAJOR_VERSION,
			ContextMinorVersion         = SDL_NAMESPACE::SDL_GL_CONTEXT_MINOR_VERSION,
			ContextEGL                  = SDL_NAMESPACE::SDL_GL_CONTEXT_EGL,
			ContextFlags                = SDL_NAMESPACE::SDL_GL_CONTEXT_FLAGS,
			ContextProfileMask          = SDL_NAMESPACE::SDL_GL_CONTEXT_PROFILE_MASK,
			ShareWithCurrentContext     = SDL_NAMESPACE::SDL_GL_SHARE_WITH_CURRENT_CONTEXT,
			FramebufferSRGBCapable      = SDL_NAMESPACE::SDL_GL_FRAMEBUFFER_SRGB_CAPABLE,
			ContextReleaseBehavior      = SDL_NAMESPACE::SDL_GL_CONTEXT_RELEASE_BEHAVIOR,
			ContextResetNotification    = SDL_NAMESPACE::SDL_GL_CONTEXT_RESET_NOTIFICATION,
			ContextNoError              = SDL_NAMESPACE::SDL_GL_CONTEXT_NO_ERROR,
		};

		ENUM_CLASS_BASE( ContextProfile, SDL_NAMESPACE::SDL_GLprofile )
		{
			Core            = SDL_NAMESPACE::SDL_GL_CONTEXT_PROFILE_CORE,
			Compatibility   = SDL_NAMESPACE::SDL_GL_CONTEXT_PROFILE_COMPATIBILITY,
			ES              = SDL_NAMESPACE::SDL_GL_CONTEXT_PROFILE_ES
		};

		ENUM_CLASS_TYPE( SwapInterval, int )
		{
			Late_Sync   = -1,
			Immediate   = 0,	// this is the default as well
			Sync        = 1,
		};

		int SetAttribute( const Attr attr, const int value ) noexcept;
		int GetAttribute( const Attr attr, int * value ) noexcept;
		bool SetSwapInterval(const SwapInterval value) noexcept;
		SwapInterval GetSwapInterval() noexcept;
		bool ToggleSwapInterval() noexcept;
	}

	ENUM_INFO_BASE( Window::Flags, SDL_NAMESPACE::SDL_WindowFlags );
	ENUM_INFO_TYPE( Window::Pos,   int );

	ENUM_BITWISE( Window::Flags );

	ENUM_INFO_BASE( GL::Attr,           SDL_NAMESPACE::SDL_GLattr );
	ENUM_INFO_BASE( GL::ContextProfile, SDL_NAMESPACE::SDL_GLprofile );
	ENUM_INFO_TYPE( GL::SwapInterval,   int );

	inline
	// ctor
	Window::Window( const char *title, Pos x, Pos y, int w, int h, Flags flags ) noexcept
		: ptr( SDL_NAMESPACE::SDL_CreateWindow( title, to_underlying( x ), to_underlying( y ), w, h, to_underlying( flags ) ), deleter )
	{}

	inline
	void
	Window::SetTitle( const std::string & title ) noexcept
	{
		SetTitle( title.c_str() );
	}

	inline
	void
	Window::SetTitle( const char * title ) noexcept
	{
		SDL_NAMESPACE::SDL_SetWindowTitle( *this, title );
	}

	inline
	int
	GL::SetAttribute( const GL::Attr attr, const int value ) noexcept
	{
		return SDL_NAMESPACE::SDL_GL_SetAttribute( to_base( attr ), value );
	}
		
	inline
	int
	GL::GetAttribute( const GL::Attr attr, int * value ) noexcept
	{
		return SDL_NAMESPACE::SDL_GL_GetAttribute( to_base( attr ), value );
	}

	inline
	bool
	GL::SetSwapInterval( const GL::SwapInterval value ) noexcept
	{
		return SDL_NAMESPACE::SDL_GL_SetSwapInterval( to_underlying( value ) ) == 0;
	}

	inline
	GL::SwapInterval
	GL::GetSwapInterval() noexcept
	{
		return to_derived<GL::SwapInterval>( SDL_NAMESPACE::SDL_GL_GetSwapInterval() );
	}

	inline
	bool
	GL::ToggleSwapInterval() noexcept
	{
		return GL::SetSwapInterval(
			GL::GetSwapInterval() == GL::SwapInterval::Immediate
				? GL::SwapInterval::Sync
				: GL::SwapInterval::Immediate );
	}
}

#endif
