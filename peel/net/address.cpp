#include "address.h"

using namespace peel::net;

Address::Address()
{
	memset(&m_address, 0, sizeof(m_address));
}

Address::Address(SOCKET s)
{
	memset(&m_address, 0, sizeof(m_address));

	int l = sizeof(sockaddr_in);
#ifdef _WIN32
	getsockname(s, (sockaddr*)&m_address, &l);
#else
	getsockname(s, (sockaddr*)&m_address, (socklen_t*)&l);
#endif
}


Address::Address(struct sockaddr_in val)
	: m_address(val)
{}

void Address::Set(unsigned long addr, unsigned short port)
{
	m_address.sin_family = AF_INET;
	m_address.sin_addr.s_addr = addr;
	m_address.sin_port = htons(port);
}

void Address::Clear()
{
	memset(&m_address, 0, sizeof(m_address));
}

std::string Address::GetName()
{
#if defined(_WIN32) && defined(_UNICODE)
	wchar_t wcbuf[255];
	char buf[255];
	inet_ntop(AF_INET, (void*)&(m_address.sin_addr), buf, 255);
	MultiByteToWideChar(CP_ACP, NULL, buf, -1, wcbuf, 255);
	return STRING(wcbuf);
	/*
	wchar_t wcbuf[255];
	sockaddr_in name;
	char *buf = inet_ntoa(name.sin_addr);
	MultiByteToWideChar(CP_ACP, NULL, buf, -1, wcbuf, 255);
	return STRING(wcbuf);
	*/
#else
	char buf[255];
	inet_ntop(AF_INET, (void*)&(m_address.sin_addr), buf, 255);
	return std::string(buf);
#endif


}