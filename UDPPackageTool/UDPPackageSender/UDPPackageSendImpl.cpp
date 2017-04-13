#include "UDPPackageSendImpl.h"

UDPPackageSendImpl::UDPPackageSendImpl()
: Poco::Runnable()
, m_bStop(true)
{
}

UDPPackageSendImpl::~UDPPackageSendImpl()
{
}

void UDPPackageSendImpl::Init(const std::string sAddress, const uint16_t iPort)
{
	m_SendSocket.SetAddress(sAddress);
	m_SendSocket.SetPort(iPort);
	m_SendSocket.Start();
}

void UDPPackageSendImpl::ManualSendMessage(const std::string &sMsg)
{
	m_SendSocket.SendMessage(sMsg);
}

void UDPPackageSendImpl::AutoSendMessage(
	std::size_t iTimes,
	std::size_t iFrequency,
	const std::string &sMsg)
{
	if (m_bStop)
	{
		m_bStop = false;
		m_iTimes = iTimes;
		m_iFrequency = iFrequency;
		m_sContent = sMsg;
		m_SendThread.start(*this);
	}
}

void UDPPackageSendImpl::StopAutoSendMessage()
{
	m_bStop = true;
}

void UDPPackageSendImpl::Close()
{
	StopAutoSendMessage();
	Await();
	m_SendSocket.Stop();
}

void UDPPackageSendImpl::Await()
{
	if (m_SendThread.isRunning())
	{
		m_SendThread.join();
	}
}

bool UDPPackageSendImpl::Initialized() const
{
	return m_SendSocket.Initialized();
}

void UDPPackageSendImpl::run()
{
	std::size_t iTimesCounter = 0;
	while (!m_bStop && iTimesCounter++ < m_iTimes)
	{
		m_SendSocket.SendMessage(m_sContent);
		Poco::Thread::sleep(m_iFrequency);
	}
}
