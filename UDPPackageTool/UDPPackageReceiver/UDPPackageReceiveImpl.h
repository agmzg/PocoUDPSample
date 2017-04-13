#ifndef _UDPPACKAGERECEIVEIMPL_H_
#define _UDPPACKAGERECEIVEIMPL_H_

#include <QtCore/QObject>

#include <Poco/Runnable.h>
#include <Poco/Thread.h>
#include <Poco/Net/DatagramSocket.h>

class UDPPackageReceiveImpl
	: public QObject
	, public Poco::Runnable
{
	Q_OBJECT

public:
	UDPPackageReceiveImpl();

	virtual ~UDPPackageReceiveImpl();

	void Start();

	void Stop();

	void Await();

	void SetPort(const ushort iPort);

	bool IsRunning() const;

signals:
	void ReceivedData(const QString sData);

protected:
	void run();

private:
	bool						m_bStop;
	ushort						m_iPort;
	Poco::Thread				m_ReceiveThread;
	Poco::Net::DatagramSocket	m_ReceiveSocket;
};

#endif //_UDPPACKAGERECEIVEIMPL_H_