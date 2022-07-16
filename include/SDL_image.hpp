#pragma once
#ifndef _SDL_IMG_HPP
#define _SDL_IMG_HPP

#include "SDL_stdinc.hpp"

#include "SDL_error.hpp"
#include "SDL_render.hpp"
#include "SDL_surface.hpp"

#define THROW_IMG_ERROR( code )\
	throw SDL::Exception( code, SDL::IMG::Error(), __FILE__, __LINE__ )

SDL_NAMESPACE_BEGIN
#include <SDL_image.h>
SDL_NAMESPACE_END

namespace SDL
{
	namespace IMG
	{
		static inline
		const char *
		Error() noexcept
		{
			return SDL_NAMESPACE::IMG_GetError();
		}

		class Init
		{
		public:
			ENUM_CLASS_BASE( Flags, SDL_NAMESPACE::IMG_InitFlags )
			{
				None       = 0,
				JPG        = SDL_NAMESPACE::IMG_INIT_JPG,
				PNG        = SDL_NAMESPACE::IMG_INIT_PNG,
				TIF        = SDL_NAMESPACE::IMG_INIT_TIF,
				WEBP       = SDL_NAMESPACE::IMG_INIT_WEBP,
				Everything = JPG | PNG | TIF | WEBP
			};

			inline
			Init( const Flags flags = Flags::Everything )
			{
				const int code = SDL_NAMESPACE::IMG_Init( to_underlying( flags ) );
				if( code < 0 )
					THROW_IMG_ERROR( code );
			}

			inline
			~Init() noexcept
			{
				SDL_NAMESPACE::IMG_Quit();
			}
		};

		ENUM_BITWISE( Init::Flags );

		static inline
		Surface
		Load( const char* file )
		{
			auto srf = SDL_NAMESPACE::IMG_Load( file );
			if( !srf )
				THROW_IMG_ERROR( -1 );

			return Surface( srf );
		}

		static inline
		Texture
		LoadTexture( Renderer& renderer, const char* file, const Uint32 color_key = SDL_MAX_UINT32 )
		{
			Surface surface = SDL_NAMESPACE::IMG_Load( file );

			if( !surface )
				THROW_IMG_ERROR( -1 );

			if( color_key != SDL_MAX_UINT32 )
				SDL_NAMESPACE::SDL_SetColorKey( surface, SDL_NAMESPACE::SDL_TRUE, color_key );

			return Texture( renderer, surface );
		}
	}

	ENUM_INFO_BASE( IMG::Init::Flags, SDL_NAMESPACE::IMG_InitFlags );
}

#endif
