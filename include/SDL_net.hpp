#pragma once
#ifndef _SDL_NET_HPP
#define _SDL_NET_HPP

#include "SDL_stdinc.hpp"

#include "SDL_error.hpp"

#define THROW_NET_ERROR( code )\
	throw SDL::Exception( code, SDL::NET::Error(), __FILE__, __LINE__ )

namespace SDL
{
	namespace C
	{
		#include <SDL_net.h>
	}

	namespace NET
	{
		static __alwaysinline
		const char *
		Error() noexcept
		{
			return C::SDLNet_GetError();
		}

		class Init
		{
		public:
			__alwaysinline
			void
			initialize() const
			{
				const int code = C::SDLNet_Init();
				if( code < 0 )
					THROW_NET_ERROR( code );
			}

			__alwaysinline
			~Init() noexcept
			{
				C::SDLNet_Quit();
			}
		};

		struct IPaddress
			: public C::IPaddress
		{
			enum InAddress
				: Uint32
			{
				ANY       = INADDR_ANY,
				NONE      = INADDR_NONE,
				LOOPBACK  = INADDR_LOOPBACK,
				BROADCAST = INADDR_BROADCAST
			};

			__alwaysinline
			IPaddress() noexcept
			{}

			__alwaysinline
			IPaddress( const Uint32 host, const Uint16 port ) noexcept
			{
				this->host = host;
				this->port = port;
			}

			__alwaysinline
			const char *
			ResolveIP()
			{
				const char * ret = C::SDLNet_ResolveIP( this );
				if( ret == nullptr )
					THROW_NET_ERROR( 0 );
				return ret;
			}
			
			/* server, resolving himself */
			static __alwaysinline
			IPaddress
			ResolveHost( const Uint16 port )
			{
				IPaddress ret;
				int code = C::SDLNet_ResolveHost( &ret, nullptr, port );
				if( code != 0 )
					THROW_NET_ERROR( code );
				return ret;
			}

			/* client, resolving the server */
			static __alwaysinline
			IPaddress
			ResolveHost( const char * host, const Uint16 port )
			{
				IPaddress ret;
				int code = C::SDLNet_ResolveHost( &ret, host, port );
				if( code != 0 )
					THROW_NET_ERROR( code );
				return ret;
			}
		};

		class TCPsocket
		{
			using ptr_type = C::_TCPsocket;
			std::shared_ptr<ptr_type>	ptr;

			PTR_DELETER( C::SDLNet_TCP_Close )

		public:
			PTR_AUTOCAST

			__alwaysinline
			TCPsocket() noexcept
				: ptr()
			{}

			/* implicit */ __alwaysinline
			TCPsocket( C::_TCPsocket * sock ) noexcept
				: ptr( sock, deleter )
			{}

			explicit __alwaysinline
			TCPsocket( IPaddress & ip )
				: ptr( C::SDLNet_TCP_Open( &ip ), deleter )
			{
				if( !*this )
					THROW_NET_ERROR( -1 );
			}

			__alwaysinline
			~TCPsocket() noexcept
			{}

			/* only for servers listening socket */
			__alwaysinline
			TCPsocket
			Accept()
			{
				auto ret = C::SDLNet_TCP_Accept( *this );
				return (ret == nullptr)
					? TCPsocket()
					: TCPsocket(ret);
			}

			__alwaysinline
			int
			Send( const void * data, const int len )
			{
				return C::SDLNet_TCP_Send( *this, data, len );
			}

			__alwaysinline
			int
			Recv( void * data, const int maxlen )
			{
				return C::SDLNet_TCP_Recv( *this, data, maxlen );
			}
		};
	}
}
#endif
