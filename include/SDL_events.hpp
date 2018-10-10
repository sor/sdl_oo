#pragma once
#ifndef _SDL_EVENTS_HPP
#define _SDL_EVENTS_HPP

#include "SDL_stdinc.hpp"
#include "SDL_keyboard.hpp"
#include "SDL_joystick.hpp"

/*
#include "SDL_stdinc.h"
#include "SDL_error.h"
#include "SDL_video.h"
#include "SDL_keyboard.h"
#include "SDL_mouse.h"
#include "SDL_joystick.h"
#include "SDL_gamecontroller.h"
#include "SDL_quit.h"
#include "SDL_gesture.h"
#include "SDL_touch.h"
*/

namespace SDL
{
	namespace C
	{
		#include <SDL_events.h>
	}

	class Event
	{
		// this one is no ptr, its a union
		C::SDL_Event self;

	public:
		enum class Type
			: std::underlying_type<C::SDL_EventType>::type
		{
			FIRSTEVENT      = C::SDL_FIRSTEVENT,        /**< Unused (do not remove) */
			QUIT            = C::SDL_QUIT,              /**< User-requested quit */
			WINDOWEVENT     = C::SDL_WINDOWEVENT,       /**< Window state change */
			SYSWMEVENT      = C::SDL_SYSWMEVENT,        /**< System specific event */
			KEYDOWN         = C::SDL_KEYDOWN,           /**< Key pressed */
			KEYUP           = C::SDL_KEYUP,             /**< Key released */
			TEXTEDITING     = C::SDL_TEXTEDITING,       /**< Keyboard text editing (composition) */
			TEXTINPUT       = C::SDL_TEXTINPUT,         /**< Keyboard text input */
			MOUSEMOTION     = C::SDL_MOUSEMOTION,       /**< Mouse moved */
			MOUSEBUTTONDOWN = C::SDL_MOUSEBUTTONDOWN,   /**< Mouse button pressed */
			MOUSEBUTTONUP   = C::SDL_MOUSEBUTTONUP,     /**< Mouse button released */
			MOUSEWHEEL      = C::SDL_MOUSEWHEEL,        /**< Mouse wheel motion */
			JOYAXISMOTION   = C::SDL_JOYAXISMOTION,     /**< Joystick axis motion */
			JOYBALLMOTION   = C::SDL_JOYBALLMOTION,     /**< Joystick trackball motion */
			JOYHATMOTION    = C::SDL_JOYHATMOTION,      /**< Joystick hat position change */
			JOYBUTTONDOWN   = C::SDL_JOYBUTTONDOWN,     /**< Joystick button pressed */
			JOYBUTTONUP     = C::SDL_JOYBUTTONUP,       /**< Joystick button released */
			FINGERDOWN      = C::SDL_FINGERDOWN,
			FINGERUP        = C::SDL_FINGERUP,
			FINGERMOTION    = C::SDL_FINGERMOTION,
			DOLLARGESTURE   = C::SDL_DOLLARGESTURE,
			DOLLARRECORD    = C::SDL_DOLLARRECORD,
			MULTIGESTURE    = C::SDL_MULTIGESTURE,
			CLIPBOARDUPDATE = C::SDL_CLIPBOARDUPDATE,   /**< The clipboard changed */
			DROPFILE        = C::SDL_DROPFILE,          /**< Drag and Drop: The system requests a file open */
			USEREVENT       = C::SDL_USEREVENT,         /**< Events ::SDL_USEREVENT through ::SDL_LASTEVENT are for your use, and should be allocated with SDL_RegisterEvents() */
			LASTEVENT       = C::SDL_LASTEVENT,         /**< This last event is only for bounding internal arrays */
		};

		union EventType
		{
			Uint32 int_type;
			Type   enum_type;
		};

		// STATIC
		static __alwaysinline
		void
		Pump()
		{
			C::SDL_PumpEvents();
		}

		static __alwaysinline
		int
		Poll( Event& evt )
		{
			return C::SDL_PollEvent( evt );
		}

		/*
		static __alwaysinline
		int
		Push( Event & evt )
		{
			return C::SDL_PushEvent( evt );
		}
		*/

		// CONSTRUCTION
		__alwaysinline
		Event()
		{
			SDL::zerop( &self );
			self.type = base_cast( Type::FIRSTEVENT );
		}

		__alwaysinline
		Event( const Type type )
		{
			SDL::zerop( &self );
			self.type = base_cast( type );
		}

		__alwaysinline
		Event( const C::SDL_Event& evt )
		{
			self = evt;
		}


		// INSTANCE
		__alwaysinline
		int
		Push()
		{
			return C::SDL_PushEvent( *this );
		}

		// FIXME: is this portable? needs -fno-strict-aliasing to work :(
		__alwaysinline
		Type&
		type() noexcept
		{
			return reinterpret_cast<Type&>( this->self.type );
		}

		__alwaysinline
		C::SDL_KeyboardEvent&
		Keyboard() noexcept
		{
			return this->self.key;
		}

		/* right now useless => disabled
		__alwaysinline
		C::SDL_TextEditingEvent & TextEditing() noexcept
		{
			return this->self.edit;
		}

		__alwaysinline
		C::SDL_TextInputEvent & TextInput() noexcept
		{
			return this->self.text;
		}
		*/

		__alwaysinline
		C::SDL_MouseButtonEvent&
		MouseButton() noexcept
		{
			return this->self.button;
		}

		__alwaysinline
		C::SDL_MouseMotionEvent&
		MouseMotion() noexcept
		{
			return this->self.motion;
		}

		__alwaysinline
		C::SDL_JoyAxisEvent&
		JoyAxis() noexcept
		{
			return this->self.jaxis;
		}

		__alwaysinline
		C::SDL_JoyButtonEvent&
		JoyButton() noexcept
		{
			return this->self.jbutton;
		}

		// AUTOCASTS
		__alwaysinline
		operator C::SDL_Event*() noexcept
		{
			return &this->self;
		}

		__alwaysinline
		operator const C::SDL_Event*() const noexcept
		{
			return &this->self;
		}
	};
}

#endif
