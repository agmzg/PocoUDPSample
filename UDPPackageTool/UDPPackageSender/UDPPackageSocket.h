#ifndef _UDPPACKAGESOCKET_H_
#define _UDPPACKAGESOCKET_H_

#include <stdint.h>

#include <Poco/Net/DatagramSocket.h>

class UDPPackageSocket
{
public:
	UDPPackageSocket();

	virtual ~UDPPackageSocket();

	void SetAddress(const std::string &sAddress);

	void SetPort(uint16_t iPort);

	void Start();

	void SendMessage(const std::string &sMsg);

	void Stop();

	bool Initialized() const;

private:
	std::string					m_sAddress;
	uint16_t					m_iPort;
	Poco::Net::DatagramSocket	m_SendSocket;
	bool						m_bInit;
};

#endif //_UDPPACKAGESOCKET_H_