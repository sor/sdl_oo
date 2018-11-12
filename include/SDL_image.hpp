#pragma once
#ifndef _SDL_IMG_HPP
#define _SDL_IMG_HPP

#include "SDL_stdinc.hpp"
#include "SDL_error.hpp"
#include "SDL_surface.hpp"
#include "SDL_render.hpp"

#define THROW_IMG_ERROR( code )\
	throw SDL::Exception( code, SDL::IMG::Error(), __FILE__, __LINE__ )

namespace SDL
{
	namespace C
	{
		#include <SDL_image.h>
	}

	namespace IMG
	{
		static __alwaysinline
		const char*
		Error() noexcept
		{
			return C::IMG_GetError();
		}

		static __alwaysinline
		SDL::Surface
		Load( const char* file )
		{
			auto srf = C::IMG_Load( file );
			if( !srf )
				THROW_IMG_ERROR( -1 );

			return SDL::Surface( srf );
		}

		static __alwaysinline
		SDL::Texture
		LoadTexture( SDL::Renderer& renderer, const char* file )
		{
			auto img = C::IMG_LoadTexture( static_cast<C::SDL_Renderer*>(renderer), file );
			if( !img )
				THROW_IMG_ERROR( -1 );

			return SDL::Texture( renderer, img );
		}

		class Init
		{
		public:
			enum class Flags
				: std::underlying_type<C::IMG_InitFlags>::type
			{
				NONE       = 0,
				JPG        = C::IMG_INIT_JPG,
				PNG        = C::IMG_INIT_PNG,
				TIF        = C::IMG_INIT_TIF,
				WEBP       = C::IMG_INIT_WEBP,
				EVERYTHING = JPG | PNG | TIF | WEBP
			};

			__alwaysinline
			void
			initialize( Flags flags = Flags::NONE ) const
			{
				const int code = C::IMG_Init( static_cast<int>(flags) );
				if( code < 0 )
					THROW_IMG_ERROR( code );
			}

			__alwaysinline
			~Init() noexcept
			{
				C::IMG_Quit();
			}
		};

		ENUM_CLASS_BITWISE( Init::Flags )
	}
}

#endif
