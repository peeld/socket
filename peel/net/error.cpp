#include "error.h"
#include <sstream>

using namespace peel::net;

Error::Error(std::string s) : m_str(s), m_err(0)
{};

Error::Error(const char* s) : m_str(s), m_err(0)
{};

Error::Error(std::string s, int err) : m_str(s), m_err(err)
{};

Error::Error(std::string s, int err, std::string host, int port)
{
	std::ostringstream ss;
	ss << s << " host: " << host << ":" << port;
	m_str = ss.str();
	m_err = err;
};

std::string Error::str()
{
	std::ostringstream ss;
	ss << m_str;

	if (m_err != 0)
	{
#ifdef _WIN32	
		char buf[1024];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, m_err, 0, buf, 1024, 0);
		ss << " - " << buf;
#else
		ss << " - " << strerror(m_err);
#endif
	}
	return ss.str();
}

std::string Error::msg()
{
	return m_str;
}

int Error::error()
{
	return m_err;
}

