#pragma once
#ifndef _SDL_RECT_HPP
#define _SDL_RECT_HPP

#include "SDL_stdinc.hpp"

#include "SDL_pixels.hpp"

SDL_NAMESPACE_BEGIN
#include <SDL_rect.h>
SDL_NAMESPACE_END

namespace SDL
{
	struct Rect;

	struct Point
		: public SDL_NAMESPACE::SDL_Point
	{
		constexpr inline
		Point() noexcept
			: SDL_NAMESPACE::SDL_Point{}
		{}

		constexpr inline
		Point( const int _x, const int _y ) noexcept
			: SDL_NAMESPACE::SDL_Point{ x = _x, y = _y }
		{}

		bool InRect( const Rect & rect ) const noexcept;

		constexpr inline
		Point
		operator + ( const Point & other ) const noexcept
		{
			return Point( x + other.x, y + other.y );
		}

		constexpr inline
		Point &
		operator += ( const Point & other )
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		constexpr inline
		Point
		operator - ( const Point & other ) const
		{
			return Point( x - other.x, y - other.y );
		}

		constexpr inline
		Point &
		operator -= ( const Point & other )
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		
		constexpr inline
		Point
		operator * ( const int scale ) const
		{
			return Point( x * scale, y * scale );
		}

		constexpr inline
		Point
		operator * ( const float scale ) const
		{
			return Point(
				static_cast<int>( x * scale ),
				static_cast<int>( y * scale ) );
		}

		constexpr inline
		Point
		operator / ( const int scale ) const
		{
			return Point( x / scale, y / scale );
		}

		constexpr inline
		Point
		operator / ( const float scale ) const
		{
			return Point(
				static_cast<int>( x / scale ),
				static_cast<int>( y / scale ) );
		}

		constexpr inline
		bool
		operator == ( const Point & other ) const
		{
			return x == other.x
				&& y == other.y;
		}
		
		constexpr inline
		bool
		operator != ( const Point & other ) const
		{
			return x != other.x
				|| y != other.y;
		}
	};

	inline
	std::ostream &
	operator<<( std::ostream & os, const Point p )
	{
		os << "(" << p.x << "," << p.y << ")";
		return os;
	}


	struct Rect
		: public SDL_NAMESPACE::SDL_Rect
	{
		constexpr inline
		Rect() noexcept
			: SDL_NAMESPACE::SDL_Rect{}
		{}

		explicit constexpr inline
		Rect( const int wh ) noexcept
			: SDL_NAMESPACE::SDL_Rect{ x = 0, y = 0, w = wh, h = wh }
		{}

		constexpr inline
		Rect( const int _w, const int _h ) noexcept
			: SDL_NAMESPACE::SDL_Rect{ x = 0, y = 0, w = _w, h = _h }
		{}

		constexpr inline
		Rect( const int _x, const int _y, const int _w, const int _h ) noexcept
			: SDL_NAMESPACE::SDL_Rect{ x = _x, y = _y, w = _w, h = _h }
		{}

		inline
		bool
		ContainsPoint( const Point & pos ) const noexcept
		{
			return pos.InRect( *this );
		}

		inline
		bool
		CollidesWith( const Rect & pos ) const noexcept
		{
			return SDL_NAMESPACE::SDL_HasIntersection( this, &pos ) == SDL_NAMESPACE::SDL_TRUE;
		}

		constexpr inline
		Rect
		operator + ( const Point & pos ) const noexcept
		{
			return Rect( x + pos.x, y + pos.y, w, h );
		}

		constexpr inline
		Rect&
		operator += ( const Point & pos ) noexcept
		{
			x += pos.x;
			y += pos.y;
			return *this;
		}
	};

	inline
	bool
	Point::InRect( const Rect & rect ) const noexcept
	{
		return SDL_NAMESPACE::SDL_PointInRect( this, &rect ) == SDL_NAMESPACE::SDL_TRUE;
	}
}

#endif
