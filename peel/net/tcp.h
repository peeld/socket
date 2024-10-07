#ifndef PEEL_TCP_SOCKET_H
#define PEEL_TCP_SOCKET_H

#include "defines.h"
#include "socketbase.h"
#include "address.h"
#include <string>

namespace peel
{
	namespace socket {

		class Tcp : public SocketBase
		{
		public:
			Tcp();

			void Connect(const char* host, unsigned short port);

			size_t Read(char* buf, size_t bufsz);

			void Write(char* buf, size_t bufsz);
		};
	} // socket
} // peel


#endif