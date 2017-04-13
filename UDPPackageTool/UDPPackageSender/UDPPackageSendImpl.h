#ifndef _UDPPACKAGESENDIMPL_H_
#define _UDPPACKAGESENDIMPL_H_

#include <stdint.h>

#include <Poco/Runnable.h>
#include <Poco/Thread.h>

#include "UDPPackageSocket.h"

class UDPPackageSendImpl : public Poco::Runnable
{
public:
	UDPPackageSendImpl();

	virtual ~UDPPackageSendImpl();

	void Init(const std::string sAddress, const uint16_t iPort);

	void ManualSendMessage(const std::string &sMsg);

	void AutoSendMessage(
		std::size_t iTimes,
		std::size_t iFrequency,
		const std::string &sMsg);

	void StopAutoSendMessage();

	void Close();

	void Await();

	bool Initialized() const;

protected:
	void run();

private:
	bool				m_bStop;
	std::string			m_sContent;
	std::size_t			m_iTimes;
	std::size_t			m_iFrequency;
	Poco::Thread		m_SendThread;
	UDPPackageSocket	m_SendSocket;
};

#endif //_UDPPACKAGESENDIMPL_H_