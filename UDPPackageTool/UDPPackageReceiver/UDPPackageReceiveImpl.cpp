#include <Poco/Net/SocketAddress.h>

#include "UDPPackageReceiveImpl.h"

UDPPackageReceiveImpl::UDPPackageReceiveImpl()
: Poco::Runnable()
, m_bStop(true)
{
}

UDPPackageReceiveImpl::~UDPPackageReceiveImpl()
{
}

void UDPPackageReceiveImpl::Start()
{
	if (m_bStop)
	{
		m_bStop = false;
		m_ReceiveThread.start(*this);
	}
}

void UDPPackageReceiveImpl::Stop()
{
	m_bStop = true;
	m_ReceiveSocket.close();
}

void UDPPackageReceiveImpl::Await()
{
	if (m_ReceiveThread.isRunning())
	{
		m_ReceiveThread.join();
	}
}

void UDPPackageReceiveImpl::SetPort(const ushort iPort)
{
	m_iPort = iPort;
}

bool UDPPackageReceiveImpl::IsRunning() const
{
	return m_ReceiveThread.isRunning();
}

void UDPPackageReceiveImpl::run()
{
	try
	{
		Poco::Net::SocketAddress sa(Poco::Net::IPAddress(), m_iPort);
		m_ReceiveSocket.bind(sa);
		char buffer[1024];
		while (!m_bStop) 
		{
			Poco::Net::SocketAddress sender;
			int n = m_ReceiveSocket.receiveFrom(buffer, sizeof(buffer)-1, sender);
			buffer[n] = '\0';
			QString sData(buffer);
			emit ReceivedData(sData);
		}
	}
	catch (const std::exception &e)
	{
		printf("%s\n", e.what());
	}
	catch (...)
	{
		printf("Unknown exception!\n");
	}
}
