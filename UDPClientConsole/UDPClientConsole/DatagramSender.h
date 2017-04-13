#ifndef _DATAGRAMSENDER_H_
#define _DATAGRAMSENDER_H_

#include <Poco/Net/DatagramSocket.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Runnable.h>

class DatagramSender : public Poco::Runnable
{
public:
	DatagramSender(
		std::string sAddress = "localhost",
		std::string sPort = "20110",
		std::string sContent = "Hello world",
		std::size_t iTimes = 30
		);

	virtual ~DatagramSender();

	void SetAddress(const std::string &sAddress);

	void SetPort(const std::string &sPort);

	void SetContent(const std::string &sContent);

	void SetTimes(const std::string &sTimes);

	void SetTimes(const std::size_t iTimes);

	void Stop();

protected:
	void run();

private:
	bool m_bStop;
	std::string m_sAddress;
	std::string m_sPort;
	std::string m_sContent;
	std::size_t m_iTimes;
};

#endif //_DATAGRAMSENDER_H_