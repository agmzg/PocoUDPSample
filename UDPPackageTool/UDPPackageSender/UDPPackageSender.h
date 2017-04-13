#ifndef UDPPACKAGESENDER_H
#define UDPPACKAGESENDER_H

#include <QtWidgets/QMainWindow>
#include "ui_UDPPackageSender.h"
#include "UDPPackageSendImpl.h"

class UDPPackageSender : public QMainWindow
{
	Q_OBJECT

public:
	UDPPackageSender(QWidget *parent = 0);
	~UDPPackageSender();

	void Init();

protected slots:
	void on_pushButton_ConOrDiscon_clicked();

	void on_pushButton_ManualSend_clicked();

	void OnCheckBoxClicked(int state);

private:
	bool Validate();

private:
	Ui::UDPPackageSenderClass	ui;

	std::string					m_sCurrentAddress;
	ushort						m_iCurrentPort;
	UDPPackageSendImpl			m_Sender;
};

#endif // UDPPACKAGESENDER_H
