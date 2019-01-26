#pragma once
#ifndef _SDL_RENDER_HPP
#define _SDL_RENDER_HPP

#include "SDL_stdinc.hpp"
#include "SDL_rect.hpp"
#include "SDL_video.hpp"

#include <memory>

namespace SDL
{
	namespace C
	{
		#include <SDL_render.h>
	}

	enum class BlendMode
		: std::underlying_type<C::SDL_BlendMode>::type
	{
		NONE	= C::SDL_BLENDMODE_NONE,
		BLEND	= C::SDL_BLENDMODE_BLEND,
		ADD		= C::SDL_BLENDMODE_ADD,
		MOD		= C::SDL_BLENDMODE_MOD
	};
	ENUM_CLASS_BITWISE(BlendMode)

	class Texture;

	class Renderer
	{
		typedef C::SDL_Renderer		ptr_type;
		std::shared_ptr<ptr_type>	ptr;

		PTR_DELETER( C::SDL_DestroyRenderer )

	public:
		PTR_AUTOCAST

		enum class Flags
			: std::underlying_type<C::SDL_RendererFlags>::type
		{
			NONE			= 0,
			SOFTWARE		= C::SDL_RENDERER_SOFTWARE,
			ACCELERATED		= C::SDL_RENDERER_ACCELERATED,
			PRESENTVSYNC	= C::SDL_RENDERER_PRESENTVSYNC,
			TARGETTEXTURE	= C::SDL_RENDERER_TARGETTEXTURE
		};

		__alwaysinline
		Renderer() noexcept
			: ptr()
		{}

		__alwaysinline
		Renderer( Window & window, int index, Flags flags ) noexcept
			: ptr( C::SDL_CreateRenderer( window, index, base_cast( flags ) ), deleter )
		{}

		__alwaysinline
		~Renderer() noexcept
		{}

		__alwaysinline
		int
		SetDrawColor( Uint8 r, Uint8 g, Uint8 b ) noexcept
		{
			return C::SDL_SetRenderDrawColor( *this, r, g, b, 255 );
		}

		__alwaysinline
		int
		SetDrawColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a ) noexcept
		{
			return C::SDL_SetRenderDrawColor( *this, r, g, b, a );
		}

		__alwaysinline
		int
		SetDrawColor( const SDL::Color & color ) noexcept
		{
			return C::SDL_SetRenderDrawColor( *this, color.r, color.g, color.b, color.a );
		}

		__alwaysinline
		int
		SetDrawBlendMode( const BlendMode blendMode ) noexcept
		{
			return C::SDL_SetRenderDrawBlendMode(
				*this,
				static_cast<C::SDL_BlendMode>( blendMode ) );
		}

		int Copy( Texture & texture ) noexcept;

		int Copy( Texture & texture, const Rect & dstrect ) noexcept;

		int Copy( Texture & texture, const Rect & srcrect, const Rect & dstrect ) noexcept;

		__alwaysinline
		int
		Clear() noexcept
		{
			return C::SDL_RenderClear( *this );
		}

		/**
		* Clears the screen with the given color.<br>
		* <b>Warning:</b> Also changes the current draw color.
		* @param r red
		* @param g green
		* @param b blue
		* @param a alpha (defaults to opaque)
		* @return 0 on success, negative error code on failure
		*/
		__alwaysinline
		int
		ClearColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255 ) noexcept
		{
			C::SDL_SetRenderDrawColor( *this, r, g, b, a );
			return C::SDL_RenderClear( *this );
		}

		__alwaysinline
		void
		Present() noexcept
		{
			C::SDL_RenderPresent( *this );
		}

		// Works only when using SDLs OpenGL
		__alwaysinline
		int
		DrawPoints( const Point * points, const int count ) noexcept
		{
			return C::SDL_RenderDrawPoints( *this, points, count );
		}

		// Works only when using SDLs OpenGL
		__alwaysinline
		int
		DrawLines( const Point points[], const int count ) noexcept
		{
			return C::SDL_RenderDrawLines( *this, points, count );
		}

		// Works only when using SDLs OpenGL
		__alwaysinline
		void
		DrawRect( const Rect & rect ) noexcept
		{
			C::SDL_RenderDrawRect( *this, &rect );
		}

		__alwaysinline
		void
		FillRect( const Rect & rect ) noexcept
		{
			C::SDL_RenderFillRect( *this, &rect );
		}
	};

	ENUM_CLASS_BITWISE( Renderer::Flags )

	class Texture
	{
		typedef C::SDL_Texture		ptr_type;
		std::shared_ptr<ptr_type>	ptr;

		PTR_DELETER( C::SDL_DestroyTexture )

		Surface		surf;
		Renderer	rend;

		PixelFormat::Type	format;
		int					access, w, h;

	public:
		PTR_AUTOCAST

		__alwaysinline
		Texture() noexcept
		{}

		__alwaysinline
		~Texture() noexcept
		{}

		Texture( Renderer & rend, const char * file );
		Texture( Renderer & rend, Surface & surf ) noexcept;
		//Texture( Renderer & rend, C::SDL_Surface * surf ) noexcept;
		Texture( Renderer & rend, C::SDL_Texture * tex ) noexcept;
		
		//void destroy() noexcept;
		//Texture & operator=( Texture && other ) noexcept;

		// Draws the texture at the given position with its normal size
		void Draw( const Point & pos ) noexcept;

		// Draws the texture at the given position with its normal size, stretching the image to fit dst
		void Draw( const Rect & dstrect ) noexcept;

		// Draws the texture at the given position with its normal size, given a subset
		void Draw( const Point & pos, const Rect & srcrect ) noexcept;

		// Draws the texture at the given position with a scaled size
		void Draw( const Point & pos, const float scale ) noexcept;

		// Draws the selected sprite at the given position  with its normal size
		void DrawSprite( const Point & pos, const Point & count, const Point & index ) noexcept;

		// Draws the selected sprite at the given position with a scaled size
		void DrawSprite( const Point & pos, const Point & count, const Point & index, const float scale ) noexcept;
		void DrawSprite( const Point & pos, const Point & count, const Rect & indexAndAmount, const float scale ) noexcept;

		// Use this method to set an additional color value multiplied into render copy operations
		int SetColorMod( const Uint8 r, const Uint8 g, const Uint8 b );

		// Use this method to set an additional color value multiplied into render copy operations
		int SetColorMod( const Color & color );

		// Use this method to get the additional color value multiplied into render copy operations
		int GetColorMod( Uint8 & r, Uint8 & g, Uint8 & b );

		// Use this method to get the additional color value multiplied into render copy operations
		int GetColorMod( Color & color );

		// Use this method to set an additional alpha value multiplied into render copy operations
		int SetAlphaMod( const Uint8 a );

		// Use this method to get the additional alpha value multiplied into render copy operations
		int GetAlphaMod( Uint8 & a );
	};

	__alwaysinline
	int
	Renderer::Copy( Texture & texture ) noexcept
	{
		return C::SDL_RenderCopy( *this, texture, nullptr, nullptr);
	}

	__alwaysinline
	int
	Renderer::Copy( Texture & texture, const Rect & dstrect ) noexcept
	{
		return C::SDL_RenderCopy( *this, texture, nullptr, &dstrect );
	}

	__alwaysinline
	int
	Renderer::Copy( Texture & texture, const Rect & srcrect, const Rect & dstrect ) noexcept
	{
		return C::SDL_RenderCopy( *this, texture, &srcrect, &dstrect );
	}

	// TEX

	__alwaysinline
	Texture::Texture( Renderer & rend, const char * file )
		: rend( rend )
	{
		auto srf = C::SDL_LoadBMP_RW( C::SDL_RWFromFile( file, "rb" ), 1 );
		if( !srf )
			THROW_SDL_ERROR( -1 );

		this->surf = srf;
		this->ptr  = std::shared_ptr<ptr_type>(
			C::SDL_CreateTextureFromSurface( this->rend, this->surf ),
			deleter );

		Uint32 fmt;
		C::SDL_QueryTexture( this->ptr.get(), &fmt, &access, &w, &h );
		format = static_cast<PixelFormat::Type>( fmt );
	}

	__alwaysinline
	Texture::Texture( Renderer & rend, Surface & surf ) noexcept
		: rend( rend )
	{
		this->surf	= surf;

		this->ptr	= std::shared_ptr<ptr_type>(
			C::SDL_CreateTextureFromSurface( this->rend, this->surf ),
			deleter );

		Uint32 fmt;
		C::SDL_QueryTexture( this->ptr.get(), &fmt, &access, &w, &h );
		format = static_cast<PixelFormat::Type>( fmt );
	}

	// no surf, maybe not good
	__alwaysinline
	Texture::Texture( Renderer & rend, C::SDL_Texture * tex ) noexcept
		: rend( rend )
	{
		this->ptr	= std::shared_ptr<ptr_type>( tex, deleter );
		Uint32 fmt;
		C::SDL_QueryTexture( this->ptr.get(), &fmt, &access, &w, &h );
		format = static_cast<PixelFormat::Type>( fmt );
	}

	// Draws the texture at the given position with its normal size
	__alwaysinline
	void
	Texture::Draw( const Point & pos ) noexcept
	{
		this->rend.Copy( *this, Rect( pos.x, pos.y, this->w, this->h ) );
	}

	// Draws the texture at the given position with its normal size, stretching the image to fit dst
	__alwaysinline
	void
	Texture::Draw( const Rect & dstrect ) noexcept
	{
		this->rend.Copy(
			*this,
			dstrect);
	}

	// Draws the texture at the given position with its normal size, given a subset
	__alwaysinline
	void
	Texture::Draw( const Point & pos, const Rect & srcrect ) noexcept
	{
		this->rend.Copy(
			*this,
			srcrect,
			Rect( pos.x, pos.y, srcrect.w, srcrect.h ) );
	}

	// Draws the texture at the given position with a scaled size
	__alwaysinline
	void
	Texture::Draw( const Point & pos, const float scale ) noexcept
	{
		this->rend.Copy(
			*this,
			Rect(	pos.x,
					pos.y,
					(int) (this->w*scale),
					(int) (this->h*scale) ) );
	}

	// Draws the selected sprite at the given position with its normal size
	__alwaysinline
	void
	Texture::DrawSprite( const Point & pos, const Point & count, const Point & index ) noexcept
	{
		const int w_rel = this->w / count.x;
		const int h_rel = this->h / count.y;
		const Rect source( w_rel * index.x, h_rel * index.y, w_rel, h_rel );

		this->rend.Copy(
			*this,
			source,
			Rect( pos.x, pos.y, w_rel, h_rel )
		);
	}

	// Draws the selected sprite at the given position with a scaled size
	__alwaysinline
	void
	Texture::DrawSprite( const Point & pos, const Point & count, const Point & index, const float scale ) noexcept
	{
		const int w_rel = this->w / count.x;
		const int h_rel = this->h / count.y;
		const Rect source( w_rel * index.x, h_rel * index.y, w_rel, h_rel );

		this->rend.Copy(
			*this,
			source,
			Rect(pos.x, pos.y, (int) (w_rel*scale), (int) (h_rel*scale) )
		);
	}

	// Draws the selected sprite at the given position with a scaled size
	__alwaysinline
	void
	Texture::DrawSprite( const Point & pos, const Point & count, const Rect & indexAndAmount, const float scale ) noexcept
	{
		const int w_rel = this->w / count.x;
		const int h_rel = this->h / count.y;
		const Rect source( w_rel * indexAndAmount.x, h_rel * indexAndAmount.y, w_rel * indexAndAmount.w, h_rel * indexAndAmount.h );

		this->rend.Copy(
			*this,
			source,
			Rect(pos.x, pos.y, (int) (w_rel * indexAndAmount.w * scale), (int) (h_rel * indexAndAmount.h * scale) )
		);
	}

	__alwaysinline
	int
	Texture::SetColorMod( const Uint8 r, const Uint8 g, const Uint8 b )
	{
		return C::SDL_SetTextureColorMod( *this, r, g, b );
	}
	
	__alwaysinline
	int
	Texture::SetColorMod( const Color & color )
	{
		return C::SDL_SetTextureColorMod( *this, color.r, color.g, color.b );
	}
	
	__alwaysinline
	int
	Texture::GetColorMod( Uint8 & r, Uint8 & g, Uint8 & b )
	{
		return C::SDL_GetTextureColorMod( *this, &r, &g, &b );
	}

	__alwaysinline
	int
	Texture::GetColorMod( Color & color )
	{
		return C::SDL_GetTextureColorMod( *this, &color.r, &color.g, &color.b );
	}

	__alwaysinline
	int
	Texture::SetAlphaMod( const Uint8 alpha )
	{
		return C::SDL_SetTextureAlphaMod( *this, alpha );
	}

	__alwaysinline
	int
	Texture::GetAlphaMod( Uint8 & alpha )
	{
		return C::SDL_GetTextureAlphaMod( *this, &alpha );
	}
}

#endif
