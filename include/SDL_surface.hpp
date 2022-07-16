#pragma once
#ifndef _SDL_SURFACE_HPP
#define _SDL_SURFACE_HPP

#include "SDL_stdinc.hpp"

#include "SDL_pixels.hpp"
#include "SDL_rect.hpp"
#include "SDL_rwops.hpp"

//#include "SDL_pixels.h"
//#include "SDL_blendmode.h"

SDL_NAMESPACE_BEGIN
#include <SDL_surface.h>
SDL_NAMESPACE_END

namespace SDL
{
	class Surface
	{
		using ptr_type = SDL_NAMESPACE::SDL_Surface;
		std::shared_ptr<ptr_type>	ptr;

		PTR_DELETER( SDL_NAMESPACE::SDL_FreeSurface );

	public:
		PTR_AUTOCAST;
		PTR_STRUCT_DEREF;

		constexpr Surface() noexcept = default;

		// Self deleting
		/* implicit */ inline
		Surface( ptr_type * surf ) noexcept
			: ptr( surf, deleter )
		{}

		// FIXME: should copy. not reference
		/* implicit */ inline
		Surface( const Surface & other ) noexcept
			: ptr( other.ptr )
		{}

		/*
		inline
		Surface( Surface && other ) noexcept
		:	ptr( other.ptr )
		{
			this->ptr = other.ptr;
			other.ptr = nullptr;
		}
		*/

		// TODO: rework so that this uses IMG_Load, so that there is no longer need for IMG::LoadTexture
		explicit inline
		Surface( const char * file ) noexcept
			// why not? : ptr( SDL_NAMESPACE::SDL_LoadBMP_RW( SDL_NAMESPACE::SDL_RWFromFile( file, "rb" ), 1 ), deleter )
		{
			ptr = std::shared_ptr<ptr_type>(
				SDL_NAMESPACE::SDL_LoadBMP_RW( SDL_NAMESPACE::SDL_RWFromFile( file, "rb" ), 1 ),
				deleter );
		}

		inline
		Surface( SDL_NAMESPACE::SDL_RWops * src, const int freesrc ) noexcept
		{
			ptr = std::shared_ptr<ptr_type>(
				SDL_NAMESPACE::SDL_LoadBMP_RW( src, freesrc ),
				deleter );
		}

		inline
		Surface( int width, int height ) noexcept
		{
			ptr = std::shared_ptr<ptr_type>(
				SDL_NAMESPACE::SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_NAMESPACE::SDL_PIXELFORMAT_RGBA32),
				deleter);
		}

		inline
		~Surface() noexcept
		{}

		/*
		inline
		Surface & operator=( const Surface & other ) noexcept
		{
			this->ptr = other.ptr;
			return *this;
		}
		*/

		/*
		auto operator=( Surface && other ) noexcept -> Surface &
		{
			self = other.self;
			other.self = nullptr;
			return *this;
		}
		*/

		static Surface CreateRGB( const int width, const int height, const int depth );

		int SaveBMP( char * file ) noexcept;
		int Blit( const Rect * srcrect, Surface & dst, Rect * dstrect ) noexcept;

		PixelFormat format() const noexcept;
		int w() const noexcept;
		int h() const noexcept;
		int pitch() const noexcept;

		template <typename T = void>
		T * pixels() const noexcept;

		bool MustLock() const noexcept;
		int Lock() noexcept;
		void Unlock() noexcept;

		int SetRLE( int flag ) noexcept;
	};

	/* static */ inline
	Surface
	Surface::CreateRGB( const int width, const int height, const int depth )
	{
		if( depth == 32 )
		{
			Uint32 rmask, gmask, bmask, amask;
			#if SDL_BYTEORDER == SDL_BIG_ENDIAN
				rmask = 0xff000000;
				gmask = 0x00ff0000;
				bmask = 0x0000ff00;
				amask = 0x000000ff;
			#else
				rmask = 0x000000ff;
				gmask = 0x0000ff00;
				bmask = 0x00ff0000;
				amask = 0xff000000;
			#endif

			return Surface( SDL_NAMESPACE::SDL_CreateRGBSurface( 0, width, height, 32, rmask, gmask, bmask, amask ) );
		}
		else
		{
			return Surface( SDL_NAMESPACE::SDL_CreateRGBSurface( 0, width, height, depth, 0, 0, 0, 0 ) );
		}
	}

	inline
	int
	Surface::SaveBMP( char * file ) noexcept
	{
		return SDL_NAMESPACE::SDL_SaveBMP_RW( *this, SDL_NAMESPACE::SDL_RWFromFile( file, "wb" ), 1 );
	}

	inline
	int
	Surface::Blit( const Rect * srcrect, Surface & dst, Rect * dstrect ) noexcept
	{
		return SDL_BlitSurface(
			*this,
			static_cast<const SDL_NAMESPACE::SDL_Rect *>(srcrect),
			dst,
			static_cast<SDL_NAMESPACE::SDL_Rect *>(dstrect) );
	}

	inline
	PixelFormat
	Surface::format() const noexcept
	{
		return ptr->format;
	}

	inline
	int
	Surface::w() const noexcept
	{
		return ptr->w;
	}

	inline
	int
	Surface::h() const noexcept
	{
		return ptr->h;
	}

	inline
	int
	Surface::pitch() const noexcept
	{
		return ptr->pitch;
	}

	template <typename T /* = void */>
	inline
	T *
	Surface::pixels() const noexcept
	{
		return static_cast<T *>( ptr->pixels );
	}

	inline
	bool
	Surface::MustLock() const noexcept
	{
		return SDL_MUSTLOCK( ptr.get() );
	}

	inline
	int
	Surface::Lock() noexcept
	{
		return SDL_NAMESPACE::SDL_LockSurface( ptr.get() );
	}
		
	inline
	void
	Surface::Unlock() noexcept
	{
		SDL_NAMESPACE::SDL_UnlockSurface( ptr.get() );
	}

	inline
	int
	Surface::SetRLE( int flag ) noexcept
	{
		return SDL_NAMESPACE::SDL_SetSurfaceRLE( *this, flag );
	}
}

#endif
