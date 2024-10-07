#ifndef PEEL_UDP_SOCKET_H
#define PEEL_UDP_SOCKET_H

#include "defines.h"
#include "socketbase.h"
#include "address.h"
#include <string>

namespace peel
{
	namespace socket {

		class Udp : public SocketBase
		{
		public:
			Udp();
			virtual bool Create();
			size_t GetDatagram(char* msg, int maxLen, Address& m_from);
		};
	} // socket
} // peel


#endif