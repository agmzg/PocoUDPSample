#include <stdint.h>

#include <QtWidgets/QMessageBox>

#include <Poco/Net/SocketAddress.h>

#include "UDPPackageSender.h"

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

UDPPackageSender::UDPPackageSender(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	Init();

	connect(ui.checkBox_AutoSend, SIGNAL(stateChanged(int)),
		this, SLOT(OnCheckBoxClicked(int)));
}

UDPPackageSender::~UDPPackageSender()
{

}

void UDPPackageSender::Init()
{
	QRegExp aRx("[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}");
	QValidator *addressValidator = new QRegExpValidator(aRx, this);
	ui.lineEdit_Address->setValidator(addressValidator);
	ui.lineEdit_Address->setText(Poco::Net::IPAddress().toString().c_str());
	//ui.lineEdit_Address->setInputMask("000.000.000.000;");

	QRegExp pRx("[1-9][0-9]{0,4}");
	QValidator *portValidator = new QRegExpValidator(pRx, this);
	ui.lineEdit_Port->setValidator(portValidator);
	ui.lineEdit_Port->setText("20110");

	ui.checkBox_AutoSend->setEnabled(false);
	ui.pushButton_ManualSend->setEnabled(false);
}

void UDPPackageSender::on_pushButton_ConOrDiscon_clicked()
{
	if (Validate())
	{
		if (ui.pushButton_ConOrDiscon->text() == QString("建立UDP"))
		{
			m_Sender.Init(ui.lineEdit_Address->text().toStdString(),
				ui.lineEdit_Port->text().toUShort());
			ui.pushButton_ConOrDiscon->setText(tr("断开UDP"));

			ui.lineEdit_Address->setEnabled(false);
			ui.lineEdit_Port->setEnabled(false);
			ui.checkBox_AutoSend->setEnabled(true);
			ui.checkBox_AutoSend->setCheckState(Qt::Unchecked);
			ui.pushButton_ManualSend->setEnabled(true);
		}
		else if (ui.pushButton_ConOrDiscon->text() == QString("断开UDP"))
		{
			m_Sender.Close();
			ui.pushButton_ConOrDiscon->setText(tr("建立UDP"));

			ui.lineEdit_Address->setEnabled(true);
			ui.lineEdit_Port->setEnabled(true);
			ui.checkBox_AutoSend->setEnabled(false);
			ui.pushButton_ManualSend->setEnabled(false);
		}
	}
	else
	{
		QMessageBox::warning(this, tr("警告"), tr("IP或端口号参数错误!"));
	}
}

void UDPPackageSender::on_pushButton_ManualSend_clicked()
{
	if (m_Sender.Initialized())
	{
		m_Sender.ManualSendMessage(ui.textEdit->toPlainText().toStdString());
	}
}

void UDPPackageSender::OnCheckBoxClicked(int state)
{
	if (ui.checkBox_AutoSend->isChecked())
	{
		m_Sender.AutoSendMessage(
			ui.spinBox_Times->value(),
			ui.spinBox_Frequency->value(),
			ui.textEdit->toPlainText().toStdString());
	}
	else
	{
		m_Sender.StopAutoSendMessage();
		m_Sender.Await();
	}
}

bool UDPPackageSender::Validate()
{
	bool bValid = true;
	do 
	{
		if (ui.lineEdit_Address->text().isEmpty() ||
			ui.lineEdit_Port->text().isEmpty())
		{
			bValid = false;
			break;
		}

		try
		{
			Poco::Net::IPAddress::parse(
				ui.lineEdit_Address->text().toStdString());
		}
		catch (const std::exception &e)
		{
			printf("%s\n", e.what());
			bValid = false;
			break;
		}
		catch (...)
		{
			bValid = false;
			break;
		}

		if (ui.lineEdit_Port->text().toUInt() > UINT16_MAX)
		{
			bValid = false;
		}
	}
	while (false);

	return bValid;
}
