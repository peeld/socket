#ifndef PEEL_SOCKET_ADDRESS_H
#define PEEL_SOCKET_ADDRESS_H

#include "defines.h"
#include <string>

namespace peel
{
	namespace net
	{
		class Address
		{
		public:
			Address();
			Address(SOCKET s);
			Address(struct sockaddr_in);

			void   Clear();
			void   Set(unsigned long addr, unsigned short port);
			std::string GetName();

			struct sockaddr_in m_address;

			operator sockaddr* () { return (sockaddr*)&m_address; }
		};
	}
}

#endif // PEEL_SOCKET_ADDRESS_H