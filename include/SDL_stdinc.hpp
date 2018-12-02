#pragma once
#ifndef _SDL_STDINC_HPP
#define _SDL_STDINC_HPP

#include <cstdarg>
#include <cstddef>
#include <cmath>

#include <algorithm>
#include <chrono>
#include <memory>
#include <string>

#pragma warning (error: 4297)
#pragma warning (error: 4715)

#ifndef __alwaysinline
#if defined(_MSC_VER)
#define __alwaysinline __forceinline
#elif ( (defined(__GNUC__) && (__GNUC__ >= 4)) || defined(__clang__) )
#define __alwaysinline __attribute__((always_inline)) inline
#else
#define __alwaysinline __inline__
#endif
#endif

#define __mayinline __inline__

#ifdef __unused
#elif defined(__GNUC__)
	#define __unused(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
	#define __unused(x) /*@unused@*/ x
#else
	#define __unused(x)
#endif

#ifdef _WIN32
	#include <direct.h>
	#define getcwd _getcwd
#else
	#include <unistd.h>
	//#define GetCurrentDir getcwd
#endif

#ifndef M_TAU
	#define M_TAU (2.0*M_PI)
#endif

// TODO: is this really correct?
template <typename T>
__alwaysinline constexpr
typename std::underlying_type<T>::type
base_cast( T o )
{
	return static_cast<typename std::underlying_type<T>::type>( o );
}

#define membersizeof(s,m) sizeof(((s *)0)->m)
#define structsizewithout(s,m) (sizeof(s)-membersizeof(s,m))

template <typename T, size_t N>
constexpr size_t countof( T const (&)[N] ) noexcept { return N; }

namespace SDL
{
	namespace C
	{
		#include <SDL_stdinc.h>
	}

	using C::Sint8;
	using C::Uint8;
	using C::Sint16;
	using C::Uint16;
	using C::Sint32;
	using C::Uint32;
	using C::Sint64;
	using C::Uint64;

	#define foreach( iter, collection )\
		for(auto iter = begin( collection );\
			iter     != end( collection );\
			++iter )

	#define PTR_DELETER( fkt )\
		static __alwaysinline\
		void\
		deleter( ptr_type * deletee )\
		{\
			fkt( deletee );\
		}\
		static __alwaysinline\
		void\
		not_deleter( ptr_type * __unused( deletee ) )\
		{}

	#define DIRECT_DELETER( fkt )\
		static __alwaysinline\
		void\
		deleter( ptr_type deletee )\
		{\
			fkt( deletee );\
		}\
		static __alwaysinline\
		void\
		not_deleter( ptr_type & __unused( deletee ) )\
		{}

	// Autocast this to the SDL_* Pointer and to bool
	#define PTR_AUTOCAST\
		__alwaysinline\
		operator bool() const noexcept\
		{\
			return static_cast<bool>( this->ptr );\
		}\
		__alwaysinline\
		operator ptr_type * () noexcept\
		{\
			return this->ptr.get();\
		}\
		__alwaysinline\
		operator const ptr_type * () const noexcept\
		{\
			return this->ptr.get();\
		}

	// Access the members of the ptr structure directly
	#define PTR_STRUCT_DEREF\
		__alwaysinline\
		ptr_type *\
		operator -> () noexcept\
		{\
			return this->ptr.get();\
		}\
		__alwaysinline\
		const ptr_type *\
		operator -> () const noexcept\
		{\
			return this->ptr.get();\
		}

	#define ENUM_CLASS_BITWISE( ENUM )\
		constexpr __alwaysinline\
		ENUM\
		operator | ( ENUM lhs, ENUM rhs ) noexcept\
		{\
			return static_cast<ENUM>( base_cast( lhs ) | base_cast( rhs ) );\
		}\
		__alwaysinline\
		ENUM &\
		operator |= ( ENUM & lhs, ENUM rhs )\
		{\
			lhs = static_cast<ENUM>( base_cast( lhs ) | base_cast( rhs ) );\
			return lhs;\
		}\
		constexpr __alwaysinline\
		ENUM\
		operator & ( ENUM lhs, ENUM rhs ) noexcept\
		{\
			return static_cast<ENUM>( base_cast( lhs ) & base_cast( rhs ) );\
		}\
		__alwaysinline\
		ENUM &\
		operator &= ( ENUM & lhs, ENUM rhs )\
		{\
			lhs = static_cast<ENUM>( base_cast( lhs ) & base_cast( rhs ) );\
			return lhs;\
		}\
		constexpr __alwaysinline\
		ENUM\
		operator ^ ( ENUM lhs, ENUM rhs ) noexcept\
		{\
			return static_cast<ENUM>( base_cast( lhs ) ^ base_cast( rhs ) );\
		}\
		__alwaysinline\
		ENUM &\
		operator ^= ( ENUM & lhs, ENUM rhs )\
		{\
			lhs = static_cast<ENUM>( base_cast( lhs ) ^ base_cast( rhs ) );\
			return lhs;\
		}\
		constexpr __alwaysinline\
		ENUM\
		operator ~ ( ENUM rhs )\
		{\
			return static_cast<ENUM>( ~base_cast( rhs ) );\
		}\
		constexpr __alwaysinline\
		bool\
		operator ! ( ENUM rhs )\
		{\
			return !base_cast( rhs );\
		}

	__alwaysinline
	void *
	memset( void * dst, int c, size_t len )
	{
		return C::SDL_memset( dst, c, len );
	}

	template <typename T>
	__alwaysinline
	void *
	zero( T & x )
	{
		return C::SDL_zero( x );
	}

	template <typename T>
	__alwaysinline
	void *
	zerop( T * x )
	{
		return C::SDL_zerop( x );
	}

	template <typename T>
	__alwaysinline
	void
	swap_noexcept( T & lhs, T & rhs ) noexcept
	{
		using std::swap;
		//static_assert( noexcept( swap( lhs, rhs ) ), "swap has to be noexcept" );
		swap( lhs, rhs );
	}

	/**
	write this
					if( contains( dq, needle ) )
	
	instead of that (using find from "algorithm")
					if( find( dq.begin(), dq.end(), needle ) != dq.end() )
	
	or even that
					bool found = false;
					for( auto it = dq.begin(); it != dq.end() && ; ++it ) {
						if( *it == needle ) {
							found = true;
							break;
						}
					}
					if( found )
	
	it would even be better if this would work...
					if( dq.contains( needle ) )
	...but i dont know how to do it
	*/
	template <typename CONT, typename T>
	__alwaysinline
	bool
	contains( const CONT & container, const T & needle )
	{
		//TODO: how can I check if CONT is of type foo<T>: static_assert()
		return find( container.begin(), container.end(), needle ) != container.end();
	}
}

#endif
