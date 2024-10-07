#ifndef PEEL_UDP_SOCKET_ERROR_H
#define PEEL_UDP_SOCKET_ERROR_H

#include "defines.h"
#include <string>

namespace peel
{
	namespace socket {
		
		//! Thrown by Socket
		class Error
		{
		public:
			//! Create a socket error without an error code from std::string message
			Error(std::string s);

			//! Create a socket error without an error code from char* message
			Error(const char* s);

			//! Create a socket error object with error code
			Error(std::string s, int err);

			//! Create a socket error object including host and port data
			Error(std::string s, int err, std::string host, int port);

			//! Destory
			inline ~Error() {};

			//! Return the error as a string
			std::string str();

			//! Return m_str
			std::string msg();

			//! return m_err
			int error();



		private:
			std::string m_str; //!< The error string
			int m_err; //!< The error code
		};
			
	} // socket
	
} // peel


#endif // PEEL_UDP_SOCKET_H