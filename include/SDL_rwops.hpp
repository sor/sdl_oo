#pragma once

#ifndef _SDL_RWOPS_HPP
#define _SDL_RWOPS_HPP

#include "SDL_stdinc.hpp"

SDL_NAMESPACE_BEGIN
#include <SDL_rwops.h>
SDL_NAMESPACE_END

namespace SDL
{
	struct RWops
		: public SDL_NAMESPACE::SDL_RWops
	{
		constexpr inline
		RWops() noexcept
			: SDL_NAMESPACE::SDL_RWops{}
		{}
	};
}

#endif
