#pragma once
#ifndef _SDL_RECT_HPP
#define _SDL_RECT_HPP

#include "SDL_stdinc.hpp"
#include "SDL_pixels.hpp"

namespace SDL
{
	namespace C
	{
		#include <SDL_rect.h>
	}

	struct Point
		: public C::SDL_Point
	{
		__alwaysinline
		Point() noexcept
		{}

		__alwaysinline
		Point( int x, int y ) noexcept
		{
			this->x = x;
			this->y = y;
		}

		/*__alwaysinline
		bool
		In(const Rect & rect) const
		{
			return C::SDL_PointInRect(this, static_cast<const C::SDL_Rect*>(&rect));
		}*/

		__alwaysinline
		Point
		operator+( const Point & other ) const
		{
			return Point( x + other.x, y + other.y );
		}

		__alwaysinline
		Point &
		operator+=( const Point & other )
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		__alwaysinline
		Point
		operator-( const Point & other ) const
		{
			return Point( x - other.x, y - other.y );
		}

		__alwaysinline
		Point &
		operator-=( const Point & other )
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		
		__alwaysinline
		Point
		operator*( const int scale ) const
		{
			return Point( x * scale, y * scale );
		}

		__alwaysinline
		Point
		operator*( const float scale ) const
		{
			return Point(
				static_cast<int>( x * scale ),
				static_cast<int>( y * scale ) );
		}

		__alwaysinline
		Point
		operator/( const int scale ) const
		{
			return Point( x / scale, y / scale );
		}

		__alwaysinline
		Point
		operator/( const float scale ) const
		{
			return Point(
				static_cast<int>( x / scale ),
				static_cast<int>( y / scale ) );
		}

		__alwaysinline
		bool
		operator==( const Point & other ) const
		{
			return x == other.x
				&& y == other.y;
		}
		
		__alwaysinline
		bool
		operator!=( const Point & other ) const
		{
			return x != other.x
				|| y != other.y;
		}
	};

	__alwaysinline
	std::ostream &
	operator<<( std::ostream & os, const Point p )
	{
		os << "(" << p.x << "," << p.y << ")";
		return os;
	}


	struct Rect
		: public C::SDL_Rect
	{
		__alwaysinline
		Rect() noexcept
		{}

		__alwaysinline
		explicit Rect( const int wh ) noexcept
		{
			this->x = 0;
			this->y = 0;
			this->w = wh;
			this->h = wh;
		}

		__alwaysinline
		Rect( const int w, const int h ) noexcept
		{
			this->x = 0;
			this->y = 0;
			this->w = w;
			this->h = h;
		}

		__alwaysinline
		Rect( const int x, const int y, const int w, const int h ) noexcept
		{
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}

		__alwaysinline
		bool
		Contains(const Point & pos) const
		{
			return C::SDL_PointInRect(&pos, this) == Bool::TRUE;
		}

		__alwaysinline
		Rect
		operator+(const Point & pos) const
		{
			return Rect(x + pos.x, y + pos.y, w, h);
		}

		__alwaysinline
		Rect&
		operator+=(const Point & pos)
		{
			x += pos.x;
			y += pos.y;
			return *this;
		}
	};
}

#endif
