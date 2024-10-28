#include "tcp.h"
#include "socketbase.h"
#include "defines.h"
#include "error.h"

#include <sstream>

using namespace peel::net;

Tcp::Tcp()
{
	m_socket = SOCKET_NULL;
}

void Tcp::Listen(int port)
{
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET) {
		throw Error("Could not create socket", GetError());
	}

	SocketBase::Bind(port);

	// Listen for incoming connections
	if (listen(m_socket, 5) == -1) {  // 5 is the maximum backlog (queue of incoming connections)
		closesocket(m_socket);
		throw Error("Could not listen", GetError());
	}
}

bool Tcp::Accept(SOCKET & client_socket)
{

	fd_set read_fds;
	FD_ZERO(&read_fds);
	FD_SET(m_socket, &read_fds);

	timeval tv;
	tv.tv_usec = 0;
	tv.tv_sec = 0;

	int activity = select(m_socket + 1, &read_fds, nullptr, nullptr, &tv);

	if (activity < 0) {
		throw Error("Could not select", GetError());
	}

	if (FD_ISSET(m_socket, &read_fds))
	{
		// Accept incoming connection
		sockaddr_in client_address;
		socklen_t client_size = sizeof(client_address);
		client_socket = accept(m_socket, (sockaddr*)&client_address, &client_size);

		if (client_socket == -1) {
			closesocket(m_socket);
			throw Error("Could not accpet", GetError());
		}

		return true;

	}

	return false;	
}

void Tcp::Connect(const char* host, unsigned short port)
{
	m_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET) {
		throw Error("Could not create socket", GetError());
	}

	struct sockaddr_in server;
	server.sin_addr.s_addr = inet_addr(host);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if (connect(m_socket, (struct sockaddr*)&server, sizeof(server)) < 0) {
		throw Error("Could not connect", GetError());
	}
}

size_t Tcp::Read(char *buf, size_t bufsz)
{
	int ret = recv(m_socket, buf, bufsz - 1, 0);
	if (ret == -1)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK) { return 0; }
		Close();
		throw Error("Error reading", GetError());
	}
	buf[ret] = '\0';
	return static_cast<size_t>(ret);
}

void Tcp::Write(const char* buf, size_t bufsz)
{
	size_t ret = send(m_socket, buf, bufsz, 0);
	if (WSAGetLastError() == WSAEWOULDBLOCK) {
		return;
	}
	if (ret == (size_t)-1) {
		Close();
		throw Error("Error reading", GetError());
	}

	return;
}


void Tcp::WriteLn(const char* buf)
{
	std::ostringstream oss;
	oss << buf << "\n";
	std::string value = oss.str();
	Write(value.c_str(), value.size());
}


bool Tcp::ReadLn(std::string& line)
{
	// Read some data
	char temp_buffer[1024];
	temp_buffer[0] = 0;
	size_t sz = Read(temp_buffer, 1024);

	if (sz == 0)
	{
		return false;
	}

	if (!leftover.empty()) {
		line = leftover;
		leftover.clear();
	}

	line += temp_buffer;

	size_t newline_pos = line.find('\n');
	if (newline_pos == std::string::npos) {
		leftover = line;
		line.clear();
		return false;
	}
	else {
		leftover = line.substr(newline_pos + 1);
		line = line.substr(0, newline_pos);
		return true;
	}
}