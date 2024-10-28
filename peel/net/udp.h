#ifndef PEEL_UDP_SOCKET_H
#define PEEL_UDP_SOCKET_H

#include "defines.h"
#include "socketbase.h"
#include "address.h"
#include <string>

namespace peel
{
	namespace net {

		class Udp : public SocketBase
		{
		public:
			Udp();
			virtual bool Create();
			size_t GetDatagram(char* msg, int maxLen, Address& m_from);
			void   SendDatagram(const char* msg, int len, const Address& to);
		};
	} // socket
} // peel


#endif