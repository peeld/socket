#ifdef _WIN32

#include "socketbase.h"
#include "error.h"

using namespace peel::net;

WSADATA gWsaData;

bool Init()
{
	int i = WSAStartup(MAKEWORD(2, 2), &gWsaData);
	return i == 0;
}

bool Cleanup()
{
	return WSACleanup() == 0;
}
#endif

void SocketBase::Close()
{
	if (m_socket == SOCKET_NULL)     
		return;
	if (m_socket == INVALID_SOCKET)  throw Error("Attempting to close invalid socket");
	if (SOCKET_CLOSE(m_socket) != 0)  throw Error("Could not close socket", GetError());
	m_socket = SOCKET_NULL;
}

void SocketBase::Bind(unsigned short port)
{
	if (m_socket != SOCKET_NULL) {
		Close();
	}
	
	Create();

	struct sockaddr_in service;
	memset(&service, 0, sizeof(sockaddr_in));
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = INADDR_ANY;
	service.sin_port = htons(port);

	// bind the socket to the port
	if (bind(m_socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		throw Error("Bind to port failed.", GetError(), "inaddr_any", port);
	}
}

void SocketBase::SetBlocking(bool block)
{
#ifdef _WIN32
	u_long arg;
	if (block)
		arg = 0;
	else
		arg = 1;
	ioctlsocket(m_socket, FIONBIO, &arg);
#else
	int x;
	x = fcntl(m_socket, F_GETFL, 0);
	if (block)
		fcntl(m_socket, F_SETFL, x &= ~O_NONBLOCK);
	else
		fcntl(m_socket, F_SETFL, x | O_NONBLOCK);
#endif
}


int SocketBase::GetError()
{
#ifdef _WIN32
	return WSAGetLastError();
#else
	return errno;
#endif
}