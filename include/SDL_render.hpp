#pragma once
#ifndef _SDL_RENDER_HPP
#define _SDL_RENDER_HPP

#include "SDL_stdinc.hpp"

#include "SDL_error.hpp"
#include "SDL_rect.hpp"
#include "SDL_video.hpp"

#include <memory>

SDL_NAMESPACE_BEGIN
#include <SDL_render.h>
SDL_NAMESPACE_END

namespace SDL
{
	//template <>	struct enum_info<enum class BlendMode> { using base = SDL_NAMESPACE::SDL_BlendMode; using type = std::underlying_type_t<base>; };
	ENUM_CLASS_BASE( BlendMode, SDL_NAMESPACE::SDL_BlendMode )
	{
		None	= SDL_NAMESPACE::SDL_BLENDMODE_NONE,
		Blend	= SDL_NAMESPACE::SDL_BLENDMODE_BLEND,
		Add		= SDL_NAMESPACE::SDL_BLENDMODE_ADD,
		Mod		= SDL_NAMESPACE::SDL_BLENDMODE_MOD,
	};
	ENUM_INFO_BASE( BlendMode, SDL_NAMESPACE::SDL_BlendMode );
	ENUM_BITWISE( BlendMode );

	class Texture;

	class Renderer
	{
		using ptr_type = SDL_NAMESPACE::SDL_Renderer;
		std::shared_ptr<ptr_type>	ptr;

		PTR_DELETER( SDL_NAMESPACE::SDL_DestroyRenderer )

	public:
		PTR_AUTOCAST;

		ENUM_CLASS_BASE( Flags, SDL_NAMESPACE::SDL_RendererFlags )
		{
			None			= 0,
			Software		= SDL_NAMESPACE::SDL_RENDERER_SOFTWARE,
			Accelerated		= SDL_NAMESPACE::SDL_RENDERER_ACCELERATED,
			PresentVSync	= SDL_NAMESPACE::SDL_RENDERER_PRESENTVSYNC,
			Targettexture	= SDL_NAMESPACE::SDL_RENDERER_TARGETTEXTURE,
		};

		ENUM_CLASS_BASE( Flip, SDL_NAMESPACE::SDL_RendererFlip )
		{
			None		= SDL_NAMESPACE::SDL_FLIP_NONE,
			Horizontal	= SDL_NAMESPACE::SDL_FLIP_HORIZONTAL,
			Vertical	= SDL_NAMESPACE::SDL_FLIP_VERTICAL,
		};

		/* TODO
		SDL_CreateTexture 
		SDL_CreateTextureFromSurface 
		SDL_CreateWindowAndRenderer
		SDL_GetRendererInfo
		*/

		constexpr inline
		Renderer() noexcept
			: ptr()
		{}
		
		inline
		Renderer( Window & window, int index, Flags flags = Flags::None ) noexcept
			: ptr( SDL_NAMESPACE::SDL_CreateRenderer( window, index, to_underlying( flags ) ), deleter )
		{}

		// software renderer
		inline
		Renderer( Surface & surface ) noexcept
			: ptr( SDL_NAMESPACE::SDL_CreateSoftwareRenderer( surface ), deleter )
		{}

		/*
		inline
		~Renderer() noexcept
		{}
		*/

		int GetDrawBlendMode( BlendMode & blendMode ) noexcept;

		inline
		int
		GetDrawColor( Uint8 & r, Uint8 & g, Uint8 & b, Uint8 & a ) noexcept
		{
			return SDL_NAMESPACE::SDL_GetRenderDrawColor( *this, &r, &g, &b, &a );
		}

		inline
		int
		GetDrawColor( Color & color ) noexcept
		{
			return SDL_NAMESPACE::SDL_GetRenderDrawColor( *this, &color.r, &color.g, &color.b, &color.a );
		}

		// TODO SDL_GetRendererInfo

		inline
		int
		GetOutputSize( int & w, int & h ) noexcept
		{
			return SDL_NAMESPACE::SDL_GetRendererOutputSize( *this, &w, &h );
		}

		Texture GetRenderTarget() noexcept;

		inline
		int
		Clear() noexcept
		{
			return SDL_NAMESPACE::SDL_RenderClear( *this );
		}

		int Copy( Texture & texture                                             ) noexcept;
		int Copy( Texture & texture,                       const Rect & dstrect ) noexcept;
		int Copy( Texture & texture, const Rect & srcrect, const Rect & dstrect ) noexcept;

		int CopyEx( Texture & texture,                                             const double angle, const Point * center = nullptr, const Flip flip = Flip::None) noexcept;
		int CopyEx( Texture & texture,                       const Rect & dstrect, const double angle, const Point * center = nullptr, const Flip flip = Flip::None) noexcept;
		int CopyEx( Texture & texture, const Rect & srcrect, const Rect & dstrect, const double angle, const Point * center = nullptr, const Flip flip = Flip::None) noexcept;

		// Works only when using SDLs OpenGL
		inline
		int
		DrawLine( int x1, int y1, int x2, int y2 ) noexcept
		{
			return SDL_NAMESPACE::SDL_RenderDrawLine( *this, x1, y1, x2, y2 );
		}

		// Works only when using SDLs OpenGL
		inline
		int
		DrawLine( const Point src, const Point dst ) noexcept
		{
			return DrawLine( src.x, src.y, dst.x, dst.y );
		}

		// Works only when using SDLs OpenGL
		inline
		int
		DrawLines( const Point points[], const int count ) noexcept
		{
			return SDL_NAMESPACE::SDL_RenderDrawLines( *this, points, count );
		}

		// Works only when using SDLs OpenGL
		inline
		int
		DrawPoint( int x, int y ) noexcept
		{
			return SDL_NAMESPACE::SDL_RenderDrawPoint( *this, x, y );
		}

		// Works only when using SDLs OpenGL
		inline
		int
		DrawPoint( const Point pos ) noexcept
		{
			return DrawPoint( pos.x, pos.y );
		}

		// Works only when using SDLs OpenGL
		inline
		int
		DrawPoints( const Point points[], const int count ) noexcept
		{
			return SDL_NAMESPACE::SDL_RenderDrawPoints( *this, points, count );
		}

		// Works only when using SDLs OpenGL
		inline
		void
		DrawRect( const Rect & rect ) noexcept
		{
			SDL_NAMESPACE::SDL_RenderDrawRect( *this, &rect );
		}
		
		// Works only when using SDLs OpenGL
		inline
		void
		DrawRects( const Rect rects[], const int count ) noexcept
		{
			SDL_NAMESPACE::SDL_RenderDrawRects( *this, rects, count );
		}

		inline
		void
		FillRect( const Rect & rect ) noexcept
		{
			SDL_NAMESPACE::SDL_RenderFillRect( *this, &rect );
		}

		inline
		void
		FillRects( const Rect & rects, const int count ) noexcept
		{
			SDL_NAMESPACE::SDL_RenderFillRects( *this, &rects, count );
		}

		inline
		void
		GetClipRect( Rect & rect ) noexcept
		{
			SDL_NAMESPACE::SDL_RenderGetClipRect( *this, &rect );
		}

		inline
		bool
		GetIntegerScale() noexcept
		{
			return SDL_NAMESPACE::SDL_RenderGetIntegerScale( *this ) == SDL_NAMESPACE::SDL_TRUE;
		}

		inline
		void
		GetLogicalSize( int & w, int & h ) noexcept
		{
			SDL_NAMESPACE::SDL_RenderGetLogicalSize( *this, &w, &h );
		}
		
		inline
		void
		GetScale( float & scaleX, float & scaleY ) noexcept
		{
			SDL_NAMESPACE::SDL_RenderGetScale( *this, &scaleX, &scaleY );
		}

		inline
		void
		GetViewport( Rect & rect ) noexcept
		{
			SDL_NAMESPACE::SDL_RenderGetViewport( *this, &rect );
		}

		inline
		bool
		IsClipEnabled() noexcept
		{
			return SDL_NAMESPACE::SDL_RenderIsClipEnabled( *this ) == SDL_NAMESPACE::SDL_TRUE;
		}
		inline
		void
		Present() noexcept
		{
			SDL_NAMESPACE::SDL_RenderPresent( *this );
		}

		// TODO SDL_RenderReadPixels
		// TODO SDL_RenderSetClipRect
		// TODO SDL_RenderSetIntegerScale
		// TODO SDL_RenderSetLogicalSize
		// TODO SDL_RenderSetScale
		// TODO SDL_RenderSetViewport
		// TODO SDL_RenderTargetSupported

		inline
		int
		SetDrawBlendMode( const BlendMode blendMode ) noexcept
		{
			return SDL_NAMESPACE::SDL_SetRenderDrawBlendMode( *this, to_base( blendMode ) );
		}

		inline
		int
		SetDrawColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a ) noexcept
		{
			return SDL_NAMESPACE::SDL_SetRenderDrawColor( *this, r, g, b, a );
		}

		inline
		int
		SetDrawColor( Uint8 r, Uint8 g, Uint8 b ) noexcept
		{
			return SetDrawColor( r, g, b, 255 );
		}

		inline
		int
		SetDrawColor( const Color & color ) noexcept
		{
			return SDL_NAMESPACE::SDL_SetRenderDrawColor( *this, color.r, color.g, color.b, color.a );
		}

		// TODO SDL_SetRenderTarget

		/**
		* Clears the screen with the given color.<br>
		* <b>Warning:</b> Also changes the current draw color.
		* @param r red
		* @param g green
		* @param b blue
		* @param a alpha (defaults to opaque)
		* @return 0 on success, negative error code on failure
		*/
		inline
		int
		ClearWithColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255 ) noexcept
		{
			SetDrawColor( r, g, b, a );
			return Clear();
		}

	};

	ENUM_INFO_BASE( Renderer::Flags, SDL_NAMESPACE::SDL_RendererFlags );
	ENUM_INFO_BASE( Renderer::Flip,  SDL_NAMESPACE::SDL_RendererFlip  );

	ENUM_BITWISE( Renderer::Flags );
	ENUM_BITWISE( Renderer::Flip );

	class Texture
	{
		using ptr_type = SDL_NAMESPACE::SDL_Texture;
		std::shared_ptr<ptr_type>	ptr;

		PTR_DELETER( SDL_NAMESPACE::SDL_DestroyTexture )

		Renderer	rend;

		PixelFormat::Type	format;
		int					access, w, h;

	public:
		PTR_AUTOCAST

		inline int width()  const { return w; }
		inline int height() const { return h; }

		inline
		Texture() noexcept
		{}

		inline
		~Texture() noexcept
		{}

		Texture( Renderer & rend, const int width, const int height );
		Texture( Renderer & rend, const char * file );
		Texture( Renderer & rend, Surface & surf ) noexcept;
		//Texture( Renderer & rend, SDL_NAMESPACE::SDL_Surface * surf ) noexcept;
		Texture( Renderer & rend, SDL_NAMESPACE::SDL_Texture * tex ) noexcept;

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

		// Draws the selected sprite at the given position with its normal size
		void DrawSprite( const Point & pos, const Point & count, const Point & index ) noexcept;

		// Draws the selected sprite at the given position with a scaled size
		void DrawSprite( const Point & pos, const Point & count, const Point & index, const float scale ) noexcept;
		void DrawSprite( const Point & pos, const Point & count, const Rect & indexAndAmount, const float scale ) noexcept;

		int Update(Surface & surface, const Rect * rect = nullptr)
		{
			return SDL_NAMESPACE::SDL_UpdateTexture( *this, rect, surface.pixels(), surface.pitch() );
		}

		// Use this method to set an additional alpha value multiplied into render copy operations
		int SetAlphaMod( const Uint8 a );

		// Use this method to get the additional alpha value multiplied into render copy operations
		int GetAlphaMod( Uint8 & a );

		// Use this function to set the blend mode for a texture, used by SDL_RenderCopy(). 
		int SetBlendMode( SDL_NAMESPACE::SDL_BlendMode blendMode );

		// Use this function to get the blend mode used for texture copy operations. 
		int GetBlendMode( SDL_NAMESPACE::SDL_BlendMode & blendMode );

		// Use this function to set the blend mode for a texture, used by SDL_RenderCopy(). 
		int SetBlendMode( BlendMode blendMode );

		// Use this function to get the blend mode used for texture copy operations. 
		int GetBlendMode( BlendMode& blendMode );

		// Use this method to set an additional color value multiplied into render copy operations
		int SetColorMod( const Uint8 r, const Uint8 g, const Uint8 b );

		// Use this method to set an additional color value multiplied into render copy operations
		int SetColorMod( const Color & color );

		// Use this method to get the additional color value multiplied into render copy operations
		int GetColorMod( Uint8 & r, Uint8 & g, Uint8 & b );

		// Use this method to get the additional color value multiplied into render copy operations
		int GetColorMod( Color & color );
	};

	inline
	int
	Renderer::GetDrawBlendMode( BlendMode & blendMode ) noexcept
	{
		return SDL_NAMESPACE::SDL_GetRenderDrawBlendMode( *this, to_base_ptr( &blendMode ) );
	}

	inline
	Texture
	Renderer::GetRenderTarget() noexcept
	{
		return Texture( *this, SDL_NAMESPACE::SDL_GetRenderTarget( *this ) );
	}

	inline
	int
	Renderer::Copy( Texture & texture ) noexcept
	{
		return SDL_NAMESPACE::SDL_RenderCopy( *this, texture, nullptr, nullptr);
	}

	inline
	int
	Renderer::Copy( Texture & texture, const Rect & dstrect ) noexcept
	{
		return SDL_NAMESPACE::SDL_RenderCopy( *this, texture, nullptr, &dstrect );
	}

	inline
	int
	Renderer::Copy( Texture & texture, const Rect & srcrect, const Rect & dstrect ) noexcept
	{
		return SDL_NAMESPACE::SDL_RenderCopy( *this, texture, &srcrect, &dstrect );
	}

	inline
	int
	Renderer::CopyEx( Texture & texture, const double angle, const Point * center /* = nullptr */, const Flip flip /* = Flip::NONE */ ) noexcept
	{
		return SDL_NAMESPACE::SDL_RenderCopyEx( *this, texture, nullptr, nullptr, angle, center, to_base( flip ) );
	}

	inline
	int
	Renderer::CopyEx( Texture & texture, const Rect & dstrect, const double angle, const Point * center /* = nullptr */, const Flip flip /* = Flip::NONE */ ) noexcept
	{
		return SDL_NAMESPACE::SDL_RenderCopyEx( *this, texture, nullptr, &dstrect, angle, center, to_base( flip ) );
	}

	inline
	int
	Renderer::CopyEx( Texture & texture, const Rect & srcrect, const Rect & dstrect, const double angle, const Point * center /* = nullptr */, const Flip flip /* = Flip::NONE */ ) noexcept
	{
		return SDL_NAMESPACE::SDL_RenderCopyEx( *this, texture, &srcrect, &dstrect, angle, center, to_base( flip ) );
	}

	// TEXTURE

	Texture::Texture( Renderer & rend, const int width, const int height )
		: rend(rend)
	{
		this->ptr = std::shared_ptr<ptr_type>(
			SDL_NAMESPACE::SDL_CreateTexture( this->rend, SDL_NAMESPACE::SDL_PIXELFORMAT_RGBA32, SDL_NAMESPACE::SDL_TEXTUREACCESS_STREAMING, width, height ),
			deleter);

		Uint32 fmt;
		SDL_NAMESPACE::SDL_QueryTexture( this->ptr.get(), &fmt, &access, &w, &h );
		format = static_cast<PixelFormat::Type>( fmt );
	}

	// TODO: rework so that this uses IMG_Load, so that there is no longer need for IMG::LoadTexture
	inline
	Texture::Texture( Renderer & rend, const char * file )
		: rend( rend )
	{
		Surface surf( file );
		//auto surf = SDL_NAMESPACE::SDL_LoadBMP_RW( SDL_NAMESPACE::SDL_RWFromFile( file, "rb" ), 1 );
		if( !surf )
			THROW_SDL_ERROR( -1 );

		this->ptr  = std::shared_ptr<ptr_type>(
			SDL_NAMESPACE::SDL_CreateTextureFromSurface( this->rend, surf ),
			deleter );

		Uint32 fmt;
		SDL_NAMESPACE::SDL_QueryTexture( this->ptr.get(), &fmt, &access, &w, &h );
		format = static_cast<PixelFormat::Type>( fmt );
	}

	inline
	Texture::Texture( Renderer & rend, Surface & surf ) noexcept
		: rend( rend )
	{
		this->ptr	= std::shared_ptr<ptr_type>(
			SDL_NAMESPACE::SDL_CreateTextureFromSurface( this->rend, surf ),
			deleter );

		Uint32 fmt;
		SDL_NAMESPACE::SDL_QueryTexture( this->ptr.get(), &fmt, &access, &w, &h );
		format = static_cast<PixelFormat::Type>( fmt );
	}

	inline
	Texture::Texture( Renderer & rend, SDL_NAMESPACE::SDL_Texture * tex ) noexcept
		: rend( rend )
	{
		this->ptr	= std::shared_ptr<ptr_type>( tex, deleter );

		Uint32 fmt;
		SDL_NAMESPACE::SDL_QueryTexture( this->ptr.get(), &fmt, &access, &w, &h );
		format = static_cast<PixelFormat::Type>( fmt );
	}

	// Draws the texture at the given position with its normal size
	inline
	void
	Texture::Draw( const Point & pos ) noexcept
	{
		this->rend.Copy( *this, Rect( pos.x, pos.y, this->w, this->h ) );
	}

	// Draws the texture at the given position with its normal size, stretching the image to fit dst
	inline
	void
	Texture::Draw( const Rect & dstrect ) noexcept
	{
		this->rend.Copy(
			*this,
			dstrect);
	}

	// Draws the texture at the given position with its normal size, given a subset
	inline
	void
	Texture::Draw( const Point & pos, const Rect & srcrect ) noexcept
	{
		this->rend.Copy(
			*this,
			srcrect,
			Rect( pos.x, pos.y, srcrect.w, srcrect.h ) );
	}

	// Draws the texture at the given position with a scaled size
	inline
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
	inline
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
	inline
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
	inline
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

	inline
	int
	Texture::SetAlphaMod( const Uint8 alpha )
	{
		return SDL_NAMESPACE::SDL_SetTextureAlphaMod( *this, alpha );
	}

	inline
	int
	Texture::GetAlphaMod( Uint8 & alpha )
	{
		return SDL_NAMESPACE::SDL_GetTextureAlphaMod( *this, &alpha );
	}

	inline
	int
	Texture::SetBlendMode( BlendMode blendMode )
	{
		return SDL_NAMESPACE::SDL_SetTextureBlendMode( *this, to_base( blendMode ) );
	}

	inline
	int
	Texture::GetBlendMode( BlendMode& blendMode )
	{
		return SDL_NAMESPACE::SDL_GetTextureBlendMode( *this, to_base_ptr( &blendMode ) );
	}

	inline
	int
	Texture::SetColorMod( const Uint8 r, const Uint8 g, const Uint8 b )
	{
		return SDL_NAMESPACE::SDL_SetTextureColorMod( *this, r, g, b );
	}
	
	inline
	int
	Texture::SetColorMod( const Color & color )
	{
		return SDL_NAMESPACE::SDL_SetTextureColorMod( *this, color.r, color.g, color.b );
	}
	
	inline
	int
	Texture::GetColorMod( Uint8 & r, Uint8 & g, Uint8 & b )
	{
		return SDL_NAMESPACE::SDL_GetTextureColorMod( *this, &r, &g, &b );
	}

	inline
	int
	Texture::GetColorMod( Color & color )
	{
		return SDL_NAMESPACE::SDL_GetTextureColorMod( *this, &color.r, &color.g, &color.b );
	}
}

#endif
