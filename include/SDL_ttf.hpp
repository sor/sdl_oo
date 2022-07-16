#pragma once
#ifndef _SDL_TTF_HPP
#define _SDL_TTF_HPP

#include "SDL_stdinc.hpp"

#include "SDL_error.hpp"
#include "SDL_surface.hpp"

#define THROW_TTF_ERROR( code )\
	throw SDL::Exception( code, SDL::TTF::Error(), __FILE__, __LINE__ )

SDL_NAMESPACE_BEGIN
#include <SDL_ttf.h>
SDL_NAMESPACE_END

namespace SDL
{
	namespace TTF
	{
		static const char * Error() noexcept;

		// add virtual to dtor if final gets removed
		class Init final
		{
		public:
			Init();
			~Init() noexcept;
		};

		// add virtual dtor if final gets removed
		class Font final
		{
			using ptr_type = SDL_NAMESPACE::TTF_Font;
			std::shared_ptr<ptr_type>	ptr;

			PTR_DELETER( SDL_NAMESPACE::TTF_CloseFont )

		public:
			PTR_AUTOCAST

			enum class Style
			{
				Normal          = TTF_STYLE_NORMAL,
				Bold            = TTF_STYLE_BOLD,
				Italic          = TTF_STYLE_ITALIC,
				Underline       = TTF_STYLE_UNDERLINE,
				Strikethrough   = TTF_STYLE_STRIKETHROUGH,
			};

			constexpr Font() noexcept = default;
			Font(const char *file, int ptsize);

			Surface RenderText_Shaded(const char *text, Color fg, Color bg);
			Surface RenderText_Shaded(const std::string text, Color fg, Color bg);
			Surface RenderText_Blended(const char *text, Color fg);
			Surface RenderText_Blended(const std::string text, Color fg);
			Surface RenderUTF8_Blended(const char *text, Color fg);
			Surface RenderUTF8_Blended(const std::string text, Color fg);
			Surface RenderUTF8_Blended_Wrapped(const char *text, Color fg, Uint32 wrapLength);
			Surface RenderUTF8_Blended_Wrapped(const std::string text, Color fg, Uint32 wrapLength);
		};

		ENUM_BITWISE( Font::Style );

		static inline
		const char *
		Error() noexcept
		{
			return SDL_NAMESPACE::TTF_GetError();
		}

		inline
		Init::Init()
		{
			const int code = SDL_NAMESPACE::TTF_Init();
			if( code < 0 )
				THROW_TTF_ERROR( code );
		}

		inline
		Init::~Init() noexcept
		{
			SDL_NAMESPACE::TTF_Quit();
		}

		inline
		Font::Font( const char * file, int ptsize )
			: ptr( SDL_NAMESPACE::TTF_OpenFont( file, ptsize ), deleter )
		{
			if( !*this )
				THROW_TTF_ERROR( -1 );
		}

		inline
		Surface
		Font::RenderText_Shaded( const char * text, Color fg, Color bg )
		{
			return SDL_NAMESPACE::TTF_RenderText_Shaded(*this, text, fg, bg);
		}

		inline
		Surface
		Font::RenderText_Shaded( const std::string text, Color fg, Color bg )
		{
			return SDL_NAMESPACE::TTF_RenderText_Shaded( *this, text.c_str(), fg, bg );
		}

		inline
		Surface
		Font::RenderText_Blended( const char * text, Color fg )
		{
			return SDL_NAMESPACE::TTF_RenderText_Blended( *this, text, fg );
		}

		inline
		Surface
		Font::RenderText_Blended( const std::string text, Color fg )
		{
			return SDL_NAMESPACE::TTF_RenderText_Blended( *this, text.c_str(), fg );
		}

		inline
		Surface
		Font::RenderUTF8_Blended( const char *text, Color fg )
		{
			return SDL_NAMESPACE::TTF_RenderUTF8_Blended( *this, text, fg );
		}

		inline
		Surface
		Font::RenderUTF8_Blended( const std::string text, Color fg )
		{
			return SDL_NAMESPACE::TTF_RenderUTF8_Blended( *this, text.c_str(), fg );
		}

		inline
		Surface
		Font::RenderUTF8_Blended_Wrapped( const char *text, Color fg, Uint32 wrapLength )
		{
			return SDL_NAMESPACE::TTF_RenderUTF8_Blended_Wrapped( *this, text, fg, wrapLength );
		}

		inline
		Surface
		Font::RenderUTF8_Blended_Wrapped( const std::string text, Color fg, Uint32 wrapLength )
		{
			return SDL_NAMESPACE::TTF_RenderUTF8_Blended_Wrapped( *this, text.c_str(), fg, wrapLength );
		}
	}
}
#endif
