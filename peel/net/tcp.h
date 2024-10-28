#ifndef PEEL_TCP_SOCKET_H
#define PEEL_TCP_SOCKET_H

#include "defines.h"
#include "socketbase.h"
#include "address.h"
#include <string>

namespace peel
{
	namespace net {

		class Tcp : public SocketBase
		{
		public:
			Tcp();

			void Listen(int);

			bool Accept(SOCKET& s);

			void Connect(const char* host, unsigned short port);

			size_t Read(char* buf, size_t bufsz);

			void Write(const char* buf, size_t bufsz);
			void WriteLn(const char* buf);

			bool ReadLn(std::string& line);

			std::string leftover;
		};
	} // socket
} // peel


#endif