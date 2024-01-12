#include "udp.h"
#include "socketbase.h"
#include "defines.h"
#include "error.h"

using namespace peel::net;

Udp::Udp()
{
	m_socket = SOCKET_NULL;
}

bool Udp::Create()
{
	m_socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	return m_socket != INVALID_SOCKET;
}

size_t Udp::GetDatagram(char* buf, int len, Address& m_from)
{
	socklen_t l = sizeof(struct sockaddr_in);
	int ret = recvfrom(m_socket, buf, len, 0, m_from, &l);
	if (WSAGetLastError() == WSAEWOULDBLOCK)
		return 0;
	if (ret == (size_t)-1) throw Error("Error getting datagram", GetError());
	buf[ret] = '\0';
	return ret;
}

void Udp::SendDatagram(const char* buf, int len, const Address& to)
{
	int ret = sendto(m_socket, buf, len, 0, (sockaddr*)(&to.m_address), sizeof(sockaddr));
	if (WSAGetLastError() == WSAEWOULDBLOCK) {
		return;
	}

	if (ret == SOCKET_ERROR) {
		throw Error("Error sending datagram", GetError());
	}

}