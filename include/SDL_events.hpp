#pragma once
#ifndef _SDL_EVENTS_HPP
#define _SDL_EVENTS_HPP

#include "SDL_stdinc.hpp"

#include "SDL_keyboard.hpp"
#include "SDL_joystick.hpp"

/*
#include "SDL_error.h"
#include "SDL_video.h"
#include "SDL_mouse.h"
#include "SDL_gamecontroller.h"
#include "SDL_quit.h"
#include "SDL_gesture.h"
#include "SDL_touch.h"
*/

SDL_NAMESPACE_BEGIN
#include <SDL_events.h>
SDL_NAMESPACE_END

namespace SDL
{
	class Event
	{
		// this is no ptr, its a union, thats why it can't be derived from
		SDL_NAMESPACE::SDL_Event self;

	public:
		ENUM_CLASS_BASE( Type, SDL_NAMESPACE::SDL_EventType )
		{
			FirstEvent          = SDL_NAMESPACE::SDL_FIRSTEVENT, 
			Quit                = SDL_NAMESPACE::SDL_QUIT,
			WindowEvent         = SDL_NAMESPACE::SDL_WINDOWEVENT,
			SyswmEvent          = SDL_NAMESPACE::SDL_SYSWMEVENT,
			KeyDown             = SDL_NAMESPACE::SDL_KEYDOWN,
			KeyUp               = SDL_NAMESPACE::SDL_KEYUP,
			TextEditing         = SDL_NAMESPACE::SDL_TEXTEDITING,
			TextInput           = SDL_NAMESPACE::SDL_TEXTINPUT,
			MouseMotion         = SDL_NAMESPACE::SDL_MOUSEMOTION,
			MouseButtonDown     = SDL_NAMESPACE::SDL_MOUSEBUTTONDOWN,
			MouseButtonUp       = SDL_NAMESPACE::SDL_MOUSEBUTTONUP,
			MouseWheel          = SDL_NAMESPACE::SDL_MOUSEWHEEL,
			JoyAxisMotion       = SDL_NAMESPACE::SDL_JOYAXISMOTION,
			JoyBallMotion       = SDL_NAMESPACE::SDL_JOYBALLMOTION,
			JoyHatMotion        = SDL_NAMESPACE::SDL_JOYHATMOTION,
			JoyButtonDown       = SDL_NAMESPACE::SDL_JOYBUTTONDOWN,
			JoyButtonUp         = SDL_NAMESPACE::SDL_JOYBUTTONUP,
			FingerDown          = SDL_NAMESPACE::SDL_FINGERDOWN,
			FingerUp            = SDL_NAMESPACE::SDL_FINGERUP,
			FingerMotion        = SDL_NAMESPACE::SDL_FINGERMOTION,
			DollarGesture       = SDL_NAMESPACE::SDL_DOLLARGESTURE,
			DollarRecord        = SDL_NAMESPACE::SDL_DOLLARRECORD,
			MultiGesture        = SDL_NAMESPACE::SDL_MULTIGESTURE,
			ClipboardUpdate     = SDL_NAMESPACE::SDL_CLIPBOARDUPDATE,
			DropFile            = SDL_NAMESPACE::SDL_DROPFILE,
			UserEvent           = SDL_NAMESPACE::SDL_USEREVENT,
			LastEvent           = SDL_NAMESPACE::SDL_LASTEVENT,
		};

		// Not gonna wrap all those, for now just alias them
		using Common            = SDL_NAMESPACE::SDL_CommonEvent;
		using Window            = SDL_NAMESPACE::SDL_WindowEvent;
		using Keyboard          = SDL_NAMESPACE::SDL_KeyboardEvent;
		using TextEditing       = SDL_NAMESPACE::SDL_TextEditingEvent;
		using TextInput         = SDL_NAMESPACE::SDL_TextInputEvent;
		using MouseMotion       = SDL_NAMESPACE::SDL_MouseMotionEvent;
		using MouseButton       = SDL_NAMESPACE::SDL_MouseButtonEvent;
		using MouseWheel        = SDL_NAMESPACE::SDL_MouseWheelEvent;
		using JoyAxis           = SDL_NAMESPACE::SDL_JoyAxisEvent;
		using JoyBall           = SDL_NAMESPACE::SDL_JoyBallEvent;
		using JoyHat            = SDL_NAMESPACE::SDL_JoyHatEvent;
		using JoyButton         = SDL_NAMESPACE::SDL_JoyButtonEvent;
		using JoyDevice         = SDL_NAMESPACE::SDL_JoyDeviceEvent;
		using ControllerAxis    = SDL_NAMESPACE::SDL_ControllerAxisEvent;
		using ControllerButton  = SDL_NAMESPACE::SDL_ControllerButtonEvent;
		using ControllerDevice  = SDL_NAMESPACE::SDL_ControllerDeviceEvent;
		using AudioDevice       = SDL_NAMESPACE::SDL_AudioDeviceEvent;
		using TouchFinger       = SDL_NAMESPACE::SDL_TouchFingerEvent;
		using MultiGesture      = SDL_NAMESPACE::SDL_MultiGestureEvent;
		using DollarGesture     = SDL_NAMESPACE::SDL_DollarGestureEvent;
		using Drop              = SDL_NAMESPACE::SDL_DropEvent;
		using Quit              = SDL_NAMESPACE::SDL_QuitEvent;
		using OS                = SDL_NAMESPACE::SDL_OSEvent;
		using User              = SDL_NAMESPACE::SDL_UserEvent;
		using SysWM             = SDL_NAMESPACE::SDL_SysWMEvent;

		Type             & type            (){ return reinterpret_cast<Type &>( self.type ); }
		Common           & common          (){ return self.common;   }
		Window           & window          (){ return self.window;   }
		Keyboard         & keyboard        (){ return self.key;      }
		TextEditing      & textediting     (){ return self.edit;     }
		TextInput        & textinput       (){ return self.text;     }
		MouseMotion      & mousemotion     (){ return self.motion;   }
		MouseButton      & mousebutton     (){ return self.button;   }
		MouseWheel       & mousewheel      (){ return self.wheel;    }
		JoyAxis          & joyaxis         (){ return self.jaxis;    }
		JoyBall          & joyball         (){ return self.jball;    }
		JoyHat           & joyhat          (){ return self.jhat;     }
		JoyButton        & joybutton       (){ return self.jbutton;  }
		JoyDevice        & joydevice       (){ return self.jdevice;  }
		ControllerAxis   & controlleraxis  (){ return self.caxis;    }
		ControllerButton & controllerbutton(){ return self.cbutton;  }
		ControllerDevice & controllerdevice(){ return self.cdevice;  }
		AudioDevice      & audiodevice     (){ return self.adevice;  }
		Quit             & quit            (){ return self.quit;     }
		User             & user            (){ return self.user;     }
		SysWM            & syswm           (){ return self.syswm;    }
		TouchFinger      & touchfinger     (){ return self.tfinger;  }
		MultiGesture     & multigesture    (){ return self.mgesture; }
		DollarGesture    & dollargesture   (){ return self.dgesture; }
		Drop             & drop            (){ return self.drop;     }

		// STATIC
		static inline
		void
		Pump()
		{
			SDL_NAMESPACE::SDL_PumpEvents();
		}

		static inline
		int
		Poll( Event & evt )
		{
			return SDL_NAMESPACE::SDL_PollEvent( evt );
		}

		/* use instance method
		static inline
		int
		Push( Event & evt )
		{
			return SDL_NAMESPACE::SDL_PushEvent( evt );
		}
		*/

		// CONSTRUCTION
		inline
		Event()
		{
			// TODO: zero instead of zerop
			zerop( &self );
			self.type = to_underlying( Type::FirstEvent );
		}

		/* implicit */ inline
		Event( const Type type )
		{
			zerop( &self );
			self.type = to_underlying( type );
		}

		/* implicit */ inline
		Event( const SDL_NAMESPACE::SDL_Event & evt )
		{
			self = evt;
		}

		// INSTANCE
		inline
		int
		Push()
		{
			return SDL_NAMESPACE::SDL_PushEvent( *this );
		}

		// AUTOCASTS
		inline
		operator SDL_NAMESPACE::SDL_Event * () noexcept
		{
			return &this->self;
		}

		inline
		operator const SDL_NAMESPACE::SDL_Event * () const noexcept
		{
			return &this->self;
		}
	};

	ENUM_INFO_BASE( Event::Type, SDL_NAMESPACE::SDL_EventType );

	// FIXME: is this portable? needs -fno-strict-aliasing to work :(
	/*inline
	const Event::Type &
	Event::type() const noexcept
	{
		auto & a = this->self.type;
		return to_derived<Type>( a );
		return reinterpret_cast<const Type &>( this->self.type );
	}*/
}

#endif
