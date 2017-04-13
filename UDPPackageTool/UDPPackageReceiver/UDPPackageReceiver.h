#ifndef UDPPACKAGERECEIVER_H
#define UDPPACKAGERECEIVER_H

#include <QtWidgets/QMainWindow>

#include <Poco/Net/DatagramSocket.h>

#include "ui_UDPPackageReceiver.h"
#include "UDPPackageReceiveImpl.h"

class UDPPackageReceiver : public QMainWindow
{
	Q_OBJECT

public:
	UDPPackageReceiver(QWidget *parent = 0);

	~UDPPackageReceiver();

protected slots:
	void on_pushButton_StartOrStop_clicked();

	void on_pushButton_Copy_clicked();

	void on_pushButton_Clear_clicked();

	void OnReceivedData(const QString sData);

private:
	void Init();

	void StartReceive(ushort iPort);

	void StopReceive();

private:
	Ui::UDPPackageReceiverClass ui;

	UDPPackageReceiveImpl m_UDPPackageReceiver;
};

#endif // UDPPACKAGERECEIVER_H
