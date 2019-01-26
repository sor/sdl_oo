#pragma once
#ifndef _SDL_TTF_HPP
#define _SDL_TTF_HPP

#include "SDL_stdinc.hpp"

#include "SDL_error.hpp"
#include "SDL_surface.hpp"

#define THROW_TTF_ERROR( code )\
	throw SDL::Exception( code, SDL::TTF::Error(), __FILE__, __LINE__ )

namespace SDL
{
	namespace C
	{
		#include <SDL_ttf.h>
	}

	namespace TTF
	{
		static __alwaysinline
		const char *
		Error() noexcept
		{
			return C::TTF_GetError();
		}

		class Init
		{
		public:
			__alwaysinline
			void
			initialize() const
			{
				const int code = C::TTF_Init();
				if( code < 0 )
					THROW_TTF_ERROR( code );
			}

			__alwaysinline
			~Init() noexcept
			{
				C::TTF_Quit();
			}
		};

		class Font
		{
			using ptr_type = C::TTF_Font;
			std::shared_ptr<ptr_type>	ptr;

			PTR_DELETER( C::TTF_CloseFont )

		public:
			PTR_AUTOCAST

			enum class Style
			{
				NORMAL			= TTF_STYLE_NORMAL,
				BOLD			= TTF_STYLE_BOLD,
				ITALIC			= TTF_STYLE_ITALIC,
				UNDERLINE		= TTF_STYLE_UNDERLINE,
				STRIKETHROUGH	= TTF_STYLE_STRIKETHROUGH
			};

			__alwaysinline
			Font() noexcept
				: ptr()
			{}

			__alwaysinline
			Font( const char *file, int ptsize )
				: ptr( C::TTF_OpenFont( file, ptsize ), deleter )
			{
				if( !*this )
					THROW_TTF_ERROR( -1 );
			}

			__alwaysinline
			~Font() noexcept
			{}

			__alwaysinline
			Surface
			RenderText_Shaded( const char *text, Color fg, Color bg )
			{
				return C::TTF_RenderText_Shaded(*this, text, fg, bg);
			}

			__alwaysinline
			Surface
			RenderText_Shaded( const std::string text, Color fg, Color bg )
			{
				return C::TTF_RenderText_Shaded( *this, text.c_str(), fg, bg );
			}

			__alwaysinline
			Surface
			RenderText_Blended( const char *text, Color fg )
			{
				return C::TTF_RenderText_Blended( *this, text, fg );
			}

			__alwaysinline
			Surface
			RenderText_Blended( const std::string text, Color fg )
			{
				return C::TTF_RenderText_Blended( *this, text.c_str(), fg );
			}

			__alwaysinline
			Surface
			RenderUTF8_Blended( const char *text, Color fg )
			{
				return C::TTF_RenderUTF8_Blended( *this, text, fg );
			}

			__alwaysinline
			Surface
			RenderUTF8_Blended( const std::string text, Color fg )
			{
				return C::TTF_RenderUTF8_Blended( *this, text.c_str(), fg );
			}

			__alwaysinline
			Surface
			RenderUTF8_Blended_Wrapped( const char *text, Color fg, Uint32 wrapLength )
			{
				return C::TTF_RenderUTF8_Blended_Wrapped( *this, text, fg, wrapLength );
			}

			__alwaysinline
			Surface
			RenderUTF8_Blended_Wrapped( const std::string text, Color fg, Uint32 wrapLength )
			{
				return C::TTF_RenderUTF8_Blended_Wrapped( *this, text.c_str(), fg, wrapLength );
			}
		};

		ENUM_CLASS_BITWISE( Font::Style )
	}
}
#endif
