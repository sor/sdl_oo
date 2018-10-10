#pragma once
#ifndef _SDL_JOYSTICK_HPP
#define _SDL_JOYSTICK_HPP

#include "SDL_stdinc.hpp"
//#include "SDL_rect.hpp"
//#include "SDL_surface.hpp"

namespace SDL
{
	namespace C
	{
		#include <SDL_joystick.h>
	}

	class Joystick
	{
		typedef C::SDL_Joystick		ptr_type;
		std::shared_ptr<ptr_type>	ptr;

		PTR_DELETER( C::SDL_JoystickClose )

	public:
		PTR_AUTOCAST

		struct State
		{
			int deadband_x;
			int deadband_y;
			int maxband_x;
			int maxband_y;

			int raw_x;
			int raw_y;
			float x;		// values in [-1,1]
			float y;		// values in [-1,1]
			float norm_x;	// fully pressed bottom and right results in norm_x = sqrt(0.5)
			float norm_y;	// fully pressed bottom and right results in norm_y = sqrt(0.5)

			__alwaysinline
			State(
				const int deadband_x = 1600,
				const int deadband_y = 1600,
				const int maxband_x = 31100,
				const int maxband_y = 31100 )
			:	deadband_x( deadband_x ),
				deadband_y( deadband_y ),
				maxband_x( maxband_x ),
				maxband_y( maxband_y ),
				raw_x( 0 ),
				raw_y( 0 )
			{
				calculate();
			}

			__alwaysinline
			void calculate()
			{
				// x values
				if( raw_x > deadband_x )		// more than dead
				{
					if( raw_x > maxband_x )			// more than maximum
					{
						x = 1;
					}
					else							// inside positive area
					{
						x = (float) (raw_x - deadband_x) / (float) (maxband_x - deadband_x);
					}
				}
				else if( raw_x < -deadband_x )	// less than minus dead
				{
					if( raw_x < -maxband_x )		// less than minus maximum
					{
						x = -1;
					}
					else							// inside negative area
					{
						x = (float) (raw_x + deadband_x) / (float) (maxband_x - deadband_x);
					}
				}
				else							// in the deadzone
				{
					x = 0;
				}

				// y values
				if( raw_y > deadband_y )		// more than dead
				{
					if( raw_y > maxband_y )			// more than maximum
					{
						y = 1;
					}
					else							// inside positive area
					{
						y = (float) (raw_y - deadband_y) / (float) (maxband_y - deadband_y);
					}
				}
				else if( raw_y < -deadband_y )	// less than minus dead
				{
					if( raw_y < -maxband_y )		// less than minus maximum
					{
						y = -1;
					}
					else							// inside negative area
					{
						y = (float) (raw_y + deadband_y) / (float) (maxband_y - deadband_y);
					}
				}
				else							// in the deadzone
				{
					y = 0;
				}

				// normalized values
				if( x == 0 && y == 0 )			// both are zero
				{
					norm_x =
					norm_y = 0;
				}
				else							// calculate normalized vector
				{
					const float length = sqrt( x*x + y*y );
					if( length > 1 )
					{
						norm_x = x / length;
						norm_y = y / length;
					}
					else
					{
						norm_x = x;
						norm_y = y;
					}
				}
			}
		};

		// STATIC
		__alwaysinline
		static int Num()
		{
			return C::SDL_NumJoysticks();
		}

		__alwaysinline
		Joystick() noexcept
		{}

		__alwaysinline
		~Joystick() noexcept
		{}

		__alwaysinline
		Joystick( int device_index ) noexcept
		:	ptr( C::SDL_JoystickOpen( device_index ), deleter )
		{}
	};
}

#endif
