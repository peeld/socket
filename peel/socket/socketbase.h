#ifndef PEEL_UDP_SOCKET_BASE_H
#define PEEL_UDP_SOCKET_BASE_H

#include "defines.h"

namespace peel
{
	namespace socket 
	{

#ifdef _WIN32
		bool Init();
		bool Cleanup();
#endif 

		class SocketBase
		{
		public:

			void    Close();

			void    Bind(unsigned short port);

			void    SetBlocking(bool);

			//! Returns platform error - errno or WSAGetLastError()
			static int GetError();

			bool Connected();

			SOCKET m_socket;
		};

	}
	
}

#endif // PEEL_UDP_SOCKET_BASE_H
