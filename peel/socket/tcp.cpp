#include "tcp.h"
#include "socketbase.h"
#include "defines.h"
#include "error.h"

using namespace peel::socket;

Tcp::Tcp()
{
	m_socket = SOCKET_NULL;
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
	socklen_t l = sizeof(struct sockaddr_in);
	size_t ret = recv(m_socket, buf, bufsz, 0);
	if (WSAGetLastError() == WSAEWOULDBLOCK) {
		return 0;
	}
	if (ret == (size_t)-1)
	{
		Close();
		throw Error("Error reading", GetError());
	}
	buf[ret] = '\0';
	return ret;
}

void Tcp::Write(char* buf, size_t bufsz)
{
	socklen_t l = sizeof(struct sockaddr_in);
	size_t ret = send(m_socket, buf, bufsz, 0);
	if (WSAGetLastError() == WSAEWOULDBLOCK) {
		return;
	}
	if (ret == (size_t)-1) {
		Close();
		throw Error("Error reading", GetError());
	}
	buf[ret] = '\0';
	return;
}


