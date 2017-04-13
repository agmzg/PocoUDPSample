#include <Poco/Net/SocketAddress.h>

#include "UDPPackageSocket.h"

UDPPackageSocket::UDPPackageSocket()
: m_bInit(false)
{
}

UDPPackageSocket::~UDPPackageSocket()
{
}

void UDPPackageSocket::SetAddress(const std::string &sAddress)
{
	m_sAddress = sAddress;
}

void UDPPackageSocket::SetPort(uint16_t iPort)
{
	m_iPort = iPort;
}

void UDPPackageSocket::Start()
{
	try
	{
		Poco::Net::SocketAddress sa(m_sAddress, m_iPort);
		m_SendSocket.connect(sa);
	}
	catch (const std::exception &e)
	{
		printf("%s\n", e.what());
		return;
	}
	catch (...)
	{
		printf("Unknown exception!");
		return;
	}
	m_bInit = true;
}

void UDPPackageSocket::SendMessage(const std::string &sMsg)
{
	try
	{
		m_SendSocket.sendBytes(sMsg.data(), sMsg.length());
	}
	catch (const std::exception &e)
	{
		printf("%s\n", e.what());
	}
	catch (...)
	{
		printf("Unknown exception!");
	}
}

void UDPPackageSocket::Stop()
{
	try
	{
		m_SendSocket.close();
	}
	catch (const std::exception &e)
	{
		printf("%s\n", e.what());
		return;
	}
	catch (...)
	{
		printf("Unknown exception!");
		return;
	}
	m_bInit = false;
}

bool UDPPackageSocket::Initialized() const
{
	return m_bInit;
}
