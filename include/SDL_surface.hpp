#pragma once
#ifndef _SDL_SURFACE_HPP
#define _SDL_SURFACE_HPP

#include "SDL_stdinc.hpp"

#include "SDL_rect.hpp"

namespace SDL
{
	namespace C
	{
		#include <SDL_surface.h>
	}

	class Surface
	{
		using ptr_type = C::SDL_Surface;
		std::shared_ptr<ptr_type>	ptr;

		PTR_DELETER( C::SDL_FreeSurface )

	public:
		PTR_AUTOCAST
		PTR_STRUCT_DEREF

		__alwaysinline
		Surface() noexcept
		{}

		// Self deleting
		/* implicit */ __alwaysinline
		Surface( C::SDL_Surface * surf ) noexcept
		:	ptr( surf, deleter )
		{}

		// FIXME: should copy. not reference
		/* implicit */ __alwaysinline
		Surface( const Surface & other ) noexcept
		:	ptr( other.ptr )
		{}

		/*
		__alwaysinline
		Surface( Surface && other ) noexcept
		:	ptr( other.ptr )
		{
			this->ptr = other.ptr;
			other.ptr = nullptr;
		}
		*/

		// TODO: rework so that this uses IMG_Load, so that there is no longer need for IMG::LoadTexture
		explicit __alwaysinline
		Surface( const char * file ) noexcept
			// why not? : ptr( C::SDL_LoadBMP_RW( C::SDL_RWFromFile( file, "rb" ), 1 ), deleter )
		{
			ptr = std::shared_ptr<ptr_type>(
				C::SDL_LoadBMP_RW( C::SDL_RWFromFile( file, "rb" ), 1 ),
				deleter );
		}

		__alwaysinline
		Surface( C::SDL_RWops * src, const int freesrc ) noexcept
		{
			ptr = std::shared_ptr<ptr_type>(
				C::SDL_LoadBMP_RW( src, freesrc ),
				deleter );
		}

		__alwaysinline
		~Surface() noexcept
		{}

		/*
		__alwaysinline
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

		static __alwaysinline
		Surface
		CreateRGB( const int width, const int height, const int depth )
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

				return Surface( C::SDL_CreateRGBSurface( 0, width, height, 32, rmask, gmask, bmask, amask ) );
			}
			else
				return Surface( C::SDL_CreateRGBSurface( 0, width, height, depth, 0, 0, 0, 0 ) );
		}

		__alwaysinline
		int
		SaveBMP( char * file ) noexcept
		{
			return C::SDL_SaveBMP_RW( *this, C::SDL_RWFromFile( file, "wb" ), 1 );
		}

		__alwaysinline
		int
		Blit( const Rect * srcrect, Surface & dst, Rect * dstrect ) noexcept
		{
			return SDL_BlitSurface(
				*this,
				static_cast<const C::SDL_Rect *>(srcrect),
				dst,
				static_cast<C::SDL_Rect *>(dstrect) );
		}

		__alwaysinline
		int
		pitch() const noexcept
		{
			return ptr->pitch;
		}

		__alwaysinline
		int
		w() const noexcept
		{
			return ptr->w;
		}

		__alwaysinline
		int
		h() const noexcept
		{
			return ptr->h;
		}

		__alwaysinline
		bool
		MustLock() const noexcept
		{
			return SDL_MUSTLOCK( ptr.get() );
		}

		__alwaysinline
		int
		Lock() noexcept
		{
			return C::SDL_LockSurface( ptr.get() );
		}
		
		__alwaysinline
		void
		Unlock() noexcept
		{
			C::SDL_UnlockSurface( ptr.get() );
		}

		template <typename T>
		__alwaysinline
		T *
		pixels() const noexcept
		{
			return static_cast<T *>( ptr->pixels );
		}

		__alwaysinline
		PixelFormat
		format() const noexcept
		{
			return ptr->format;
		}

		__alwaysinline
		int
		SetRLE( int flag ) noexcept
		{
			return C::SDL_SetSurfaceRLE( *this, flag );
		}
	};
}

#endif
