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

#ifdef HIDE_ORIGINAL_SDL
#define SDL_NAMESPACE		::SDL::C
#define SDL_NAMESPACE_BEGIN	namespace SDL { namespace C {
#define SDL_NAMESPACE_END	} }
#else
#define SDL_NAMESPACE
#define SDL_NAMESPACE_BEGIN
#define SDL_NAMESPACE_END
#endif

#ifdef unused
#elif __cplusplus >= 201703L
	#define unused( t, v ) [[maybe_unused]] t v
#elif defined(__GNUC__)
	#define unused( t, x ) t UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
	#define unused( t, x ) t /*@unused@*/ x
#else
	#define unused( t, x ) t
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

template <typename Enum>
constexpr inline
std::underlying_type_t<Enum>
to_underlying( Enum e ) noexcept
{
	return static_cast<std::underlying_type_t<Enum>>( e );
}

template <typename Enum>
constexpr inline
std::underlying_type_t<Enum> *
to_underlying_ptr( Enum * e ) noexcept
{
	return reinterpret_cast<std::underlying_type_t<Enum> *>( e );
}

#define membersizeof(s,m) sizeof(((s *)0)->m)
#define structsizewithout(s,m) (sizeof(s)-membersizeof(s,m))

template <typename T, size_t N>
constexpr inline
size_t
countof( T const (&)[N] ) noexcept { return N; }

SDL_NAMESPACE_BEGIN
#include <SDL_stdinc.h>
SDL_NAMESPACE_END

namespace SDL
{
	using SDL_NAMESPACE::Sint8;
	using SDL_NAMESPACE::Uint8;
	using SDL_NAMESPACE::Sint16;
	using SDL_NAMESPACE::Uint16;
	using SDL_NAMESPACE::Sint32;
	using SDL_NAMESPACE::Uint32;
	using SDL_NAMESPACE::Sint64;
	using SDL_NAMESPACE::Uint64;

	// Enum hierarchical inheritence:
	// Since SDL does not define class enums, we kind of want to derive from them, but this is not possible in C++ (nor in C)
	// Therefore the following data-structures and functions prevent us from having to (static/reinterpret)_cast from and to
	//   unrelated types and occasionally getting it wrong ;)
	// Underlying: Is the fundamental type that also defines how many bits of space is available to the enum, e.g. SDL::Uint32
	// Base: Is usually the non-class enum from SDL
	//       OR it might be the same as Underlying when SDL defines no enum and just some constants
	// Derived: Is usually the class enum defined in this wrapper
	//
	// The enums need to be defined by either ENUM_CLASS_DEFAULT, ENUM_CLASS_TYPE, or ENUM_CLASS_BASE
	//   and out-of-class provided with additional info via ENUM_INFO_DEFAULT, ENUM_INFO_TYPE, or ENUM_INFO_BASE

	template <typename Derived> struct enum_info {};
	//template <typename Derived> using  enum_info_b = typename enum_info<Derived>::base;
	//template <typename Derived> using  enum_info_t = typename enum_info<Derived>::underlying;

	#define ENUM_CLASS_DEFAULT( ENUM )\
		enum class ENUM

	#define ENUM_CLASS_TYPE( ENUM, UNDERLYING )\
		enum class ENUM : UNDERLYING

	#define ENUM_CLASS_BASE( ENUM, BASE )\
		enum class ENUM : std::underlying_type_t<BASE>

	#define ENUM_INFO_DEFAULT( ENUM )\
		template <> struct enum_info<enum class ENUM> { using base = std::underlying_type_t<ENUM>; using underlying = std::underlying_type_t<ENUM>; };

	#define ENUM_INFO_TYPE( ENUM, UNDERLYING )\
		template <> struct enum_info<enum class ENUM> { using base = UNDERLYING; using underlying = UNDERLYING; };

	#define ENUM_INFO_BASE( ENUM, BASE )\
		template <> struct enum_info<enum class ENUM> { using base = BASE; using underlying = std::underlying_type_t<base>; };

	template <typename Derived, typename Base = typename enum_info<Derived>::base>
	constexpr inline
	Base
	to_base( const Derived e )
	{
		return static_cast<Base>( e );
	}
	
	/*
	template <typename Enum, typename Base = typename enum_info<Enum>::base>
	constexpr inline
	Base &
	to_base_ref( Enum & e )
	{
		return reinterpret_cast<Base &>( e );
	}

	template <typename Enum, typename Base = typename enum_info<Enum>::base>
	constexpr inline
	const Base &
	to_base_ref( const Enum & e )
	{
		return reinterpret_cast<const Base &>( e );
	}

	template <typename Enum, typename Base = typename enum_info<Enum>::base, typename Type = typename enum_info<Enum>::type>
	constexpr inline
	Base &
	to_base_ref( Type & e )
	{
		return reinterpret_cast<Base &>( e );
	}
	*/

	template <typename Derived, typename Base = typename enum_info<Derived>::base, typename Underlying = typename enum_info<Derived>::underlying>
	constexpr inline
	const Derived &
	to_derived( const Underlying & e )
	{
		// FIXME: is this portable? may need -fno-strict-aliasing to work?!
		return reinterpret_cast<const Derived &>( e );
	}

	template <typename Derived, typename Base = typename enum_info<Derived>::base>
	constexpr inline
	Base *
	to_base_ptr( Derived * e )
	{
		return reinterpret_cast<Base *>( e );
	}

	template <typename Derived, typename Base = typename enum_info<Derived>::base>
	constexpr inline
	const Base *
	to_base_ptr( const Derived * e )
	{
		return reinterpret_cast<const Base *>( e );
	}

	#define PTR_DELETER( fkt )\
		static inline\
		void\
		deleter( ptr_type * deletee )\
		{\
			fkt( deletee );\
		}\
		static inline\
		void\
		not_deleter( unused( ptr_type *, deletee ) )\
		{}

	#define DIRECT_DELETER( fkt )\
		static inline\
		void\
		deleter( ptr_type & deletee )\
		{\
			fkt( deletee );\
		}\
		static inline\
		void\
		not_deleter( unused( ptr_type &, deletee ) )\
		{}

	// Autocast this to the SDL_* Pointer and to bool
	#define PTR_AUTOCAST\
		inline\
		operator bool() const noexcept\
		{\
			return static_cast<bool>( this->ptr );\
		}\
		inline\
		operator ptr_type * () noexcept\
		{\
			return this->ptr.get();\
		}\
		inline\
		operator const ptr_type * () const noexcept\
		{\
			return this->ptr.get();\
		}

	// Access the members of the ptr structure directly
	#define PTR_STRUCT_DEREF\
		inline\
		ptr_type *\
		operator -> () noexcept\
		{\
			return this->ptr.get();\
		}\
		inline\
		const ptr_type *\
		operator -> () const noexcept\
		{\
			return this->ptr.get();\
		}

	#define ENUM_BITWISE( ENUM )\
		constexpr inline\
		ENUM\
		operator | ( ENUM lhs, ENUM rhs ) noexcept\
		{\
			return static_cast<ENUM>( to_underlying( lhs ) | to_underlying( rhs ) );\
		}\
		inline\
		ENUM &\
		operator |= ( ENUM & lhs, ENUM rhs )\
		{\
			lhs = static_cast<ENUM>( to_underlying( lhs ) | to_underlying( rhs ) );\
			return lhs;\
		}\
		constexpr inline\
		ENUM\
		operator & ( ENUM lhs, ENUM rhs ) noexcept\
		{\
			return static_cast<ENUM>( to_underlying( lhs ) & to_underlying( rhs ) );\
		}\
		inline\
		ENUM &\
		operator &= ( ENUM & lhs, ENUM rhs )\
		{\
			lhs = static_cast<ENUM>( to_underlying( lhs ) & to_underlying( rhs ) );\
			return lhs;\
		}\
		constexpr inline\
		ENUM\
		operator ^ ( ENUM lhs, ENUM rhs ) noexcept\
		{\
			return static_cast<ENUM>( to_underlying( lhs ) ^ to_underlying( rhs ) );\
		}\
		inline\
		ENUM &\
		operator ^= ( ENUM & lhs, ENUM rhs )\
		{\
			lhs = static_cast<ENUM>( to_underlying( lhs ) ^ to_underlying( rhs ) );\
			return lhs;\
		}\
		constexpr inline\
		ENUM\
		operator ~ ( ENUM rhs )\
		{\
			return static_cast<ENUM>( ~to_underlying( rhs ) );\
		}\
		constexpr inline\
		bool\
		operator ! ( ENUM rhs )\
		{\
			return !to_underlying( rhs );\
		}

	inline
	void *
	memset( void * dst, int c, size_t len )
	{
		return SDL_NAMESPACE::SDL_memset( dst, c, len );
	}

	template <typename T>
	inline
	void *
	zero( T & x )
	{
		return SDL_NAMESPACE::SDL_zero( x );
	}

	template <typename T>
	inline
	void *
	zerop( T * x )
	{
		return SDL_NAMESPACE::SDL_zerop( x );
	}

	template <typename T>
	inline
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
	inline
	bool
	contains( const CONT & container, const T & needle )
	{
		//TODO: how can I check if CONT is of type foo<T>: static_assert()
		return find( container.begin(), container.end(), needle ) != container.end();
	}
}

#endif
