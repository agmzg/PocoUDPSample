#include <Poco/Thread.h>
#include <Poco/NumberParser.h>

#include "DatagramSender.h"

DatagramSender::DatagramSender(
	std::string sAddress/* = "localhost"*/,
	std::string sPort/* = "20110"*/,
	std::string sContent/* = "Hello world"*/,
	std::size_t iTimes/* = 30*/)
	: Poco::Runnable()
	, m_sAddress(sAddress)
	, m_sPort(sPort)
	, m_sContent(sContent)
	, m_iTimes(iTimes)
	, m_bStop(false)
{
}

DatagramSender::~DatagramSender()
{
}

void DatagramSender::SetAddress(const std::string &sAddress)
{
	Poco::Net::IPAddress as;
	if (Poco::Net::IPAddress::tryParse(sAddress, as))
	{
		m_sAddress = sAddress;
	}
	else
	{
		printf("Use default address£º%s\n", m_sAddress.c_str());
	}
}

void DatagramSender::SetPort(const std::string &sPort)
{
	unsigned nPort = 0;
	if (Poco::NumberParser::tryParseUnsigned(sPort, nPort))
	{
		m_sPort = sPort;
	}
	else
	{
		printf("Use default port£º%s\n", m_sPort.c_str());
	}
}

void DatagramSender::SetContent(const std::string &sContent)
{
	m_sContent = sContent;
}

void DatagramSender::SetTimes(const std::string &sTimes)
{
	std::size_t iTimes = 0;
	if (Poco::NumberParser::tryParseUnsigned(sTimes, iTimes))
	{
		m_iTimes = iTimes;
	}
	else
	{
		printf("Use default times£º%d\n", m_iTimes);
	}
}

void DatagramSender::SetTimes(const std::size_t iTimes)
{
	m_iTimes = iTimes;
}

void DatagramSender::Stop()
{
	m_bStop = true;
}

void DatagramSender::run()
{
	try
	{
		Poco::Net::SocketAddress sa(m_sAddress, m_sPort);
		Poco::Net::DatagramSocket dgs;
		dgs.connect(sa);
		std::size_t nCounter = 0;
		do
		{
			dgs.sendBytes(m_sContent.data(), m_sContent.size());
			Poco::Thread::sleep(1000);
		}
		while (!m_bStop && nCounter++ < m_iTimes);
		dgs.close();
	}
	catch (const std::exception &e)
	{
		printf("%s\n", e.what());
	}
	catch (...)
	{
		printf("Unknow exception!\n");
	}
}
