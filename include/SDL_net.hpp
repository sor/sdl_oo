#pragma once
#ifndef _SDL_NET_HPP
#define _SDL_NET_HPP

#include "SDL_stdinc.hpp"

#include "SDL_error.hpp"

#define THROW_NET_ERROR( code )\
	throw SDL::Exception( code, SDL::NET::Error(), __FILE__, __LINE__ )

SDL_NAMESPACE_BEGIN
#include <SDL_net.h>
SDL_NAMESPACE_END

namespace SDL
{
	namespace NET
	{
		static inline
		const char *
		Error() noexcept
		{
			return SDL_NAMESPACE::SDLNet_GetError();
		}

		class Init
		{
		public:
			inline
			Init()
			{
				const int code = SDL_NAMESPACE::SDLNet_Init();
				if( code < 0 )
					THROW_NET_ERROR( code );
			}

			inline
			~Init() noexcept
			{
				SDL_NAMESPACE::SDLNet_Quit();
			}
		};

		struct IPaddress
			: public SDL_NAMESPACE::IPaddress
		{
			ENUM_CLASS_TYPE( InAddress, SDL_NAMESPACE::Uint32 )
			{
				Any       = INADDR_ANY,
				None      = INADDR_NONE,
				Loopback  = INADDR_LOOPBACK,
				Broadcast = INADDR_BROADCAST
			};

			inline
			IPaddress() noexcept
			{}

			inline
			IPaddress( const Uint32 host, const Uint16 port ) noexcept
			{
				this->host = host;
				this->port = port;
			}

			inline
			const char *
			ResolveIP()
			{
				const char * ret = SDL_NAMESPACE::SDLNet_ResolveIP( this );
				if( ret == nullptr )
					THROW_NET_ERROR( 0 );
				return ret;
			}
			
			/* server, resolving himself */
			static inline
			IPaddress
			ResolveHost( const Uint16 port )
			{
				IPaddress ret;
				int code = SDL_NAMESPACE::SDLNet_ResolveHost( &ret, nullptr, port );
				if( code != 0 )
					THROW_NET_ERROR( code );
				return ret;
			}

			/* client, resolving the server */
			static inline
			IPaddress
			ResolveHost( const char * host, const Uint16 port )
			{
				IPaddress ret;
				int code = SDL_NAMESPACE::SDLNet_ResolveHost( &ret, host, port );
				if( code != 0 )
					THROW_NET_ERROR( code );
				return ret;
			}
		};


		class TCPsocket
		{
			using ptr_type = SDL_NAMESPACE::_TCPsocket;
			std::shared_ptr<ptr_type>	ptr;

			PTR_DELETER( SDL_NAMESPACE::SDLNet_TCP_Close )

		public:
			PTR_AUTOCAST

			inline
			TCPsocket() noexcept
				: ptr()
			{}

			/* implicit */ inline
			TCPsocket( SDL_NAMESPACE::_TCPsocket * sock ) noexcept
				: ptr( sock, deleter )
			{}

			explicit inline
			TCPsocket( IPaddress & ip )
				: ptr( SDL_NAMESPACE::SDLNet_TCP_Open( &ip ), deleter )
			{
				if( !*this )
					THROW_NET_ERROR( -1 );
			}

			inline
			~TCPsocket() noexcept
			{}

			/* only for servers listening socket */
			inline
			TCPsocket
			Accept()
			{
				auto ret = SDL_NAMESPACE::SDLNet_TCP_Accept( *this );
				return (ret == nullptr)
					? TCPsocket()
					: TCPsocket(ret);
			}

			inline
			int
			Send( const void * data, const int len )
			{
				return SDL_NAMESPACE::SDLNet_TCP_Send( *this, data, len );
			}

			inline
			int
			Recv( void * data, const int maxlen )
			{
				return SDL_NAMESPACE::SDLNet_TCP_Recv( *this, data, maxlen );
			}
		};
	}

	ENUM_INFO_TYPE( NET::IPaddress::InAddress, SDL_NAMESPACE::Uint32 );
}
#endif
