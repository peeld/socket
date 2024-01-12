#ifndef PEEL_UDP_SOCKET_BASE_H
#define PEEL_UDP_SOCKET_BASE_H

#include "defines.h"

namespace peel
{
	namespace net 
	{

#ifdef _WIN32
		bool Init();
		bool Cleanup();
#endif 

		class SocketBase
		{
		public:

			virtual bool Create() = 0;

			void    Close();

			void    Bind(unsigned short port);

			void    SetBlocking(bool);

			//! Returns platform error - errno or WSAGetLastError()
			static int GetError();

			SOCKET m_socket;
		};

	}
	
}

#endif // PEEL_UDP_SOCKET_BASE_H
