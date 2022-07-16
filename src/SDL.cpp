#include <iostream>

#define HIDE_ORIGINAL_SDL

#include "SDL.hpp"
#include "SDL_error.hpp"
#include "SDL_events.hpp"
#include "SDL_exception.hpp"
#include "SDL_image.hpp"
#include "SDL_joystick.hpp"
#include "SDL_keyboard.hpp"
#include "SDL_keycode.hpp"
#include "SDL_net.hpp"
#include "SDL_pixels.hpp"
#include "SDL_rect.hpp"
#include "SDL_render.hpp"
#include "SDL_rwops.hpp"
#include "SDL_scancode.hpp"
#include "SDL_surface.hpp"
#include "SDL_ttf.hpp"
#include "SDL_video.hpp"

void SDL::dummy()
{
	using namespace SDL;

	Init      init;
	IMG::Init img_init;
	TTF::Init ttf_init;
	NET::Init net_init;
	Window    win = Window( "blah", Window::Pos(19), Window::Pos::Undefined, 90, 91, Window::Flags::None );
	TTF::Font f;
	Surface s;

	std::cout << "Hello, World!" << std::endl;
}
