#include <stdint.h>

#include <QtWidgets/QMessageBox>
#include <QtGui/QClipboard>

#include "UDPPackageReceiver.h"

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

UDPPackageReceiver::UDPPackageReceiver(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	Init();

	connect(&m_UDPPackageReceiver, SIGNAL(ReceivedData(const QString)),
			this, SLOT(OnReceivedData(const QString)));
}

UDPPackageReceiver::~UDPPackageReceiver()
{

}

void UDPPackageReceiver::on_pushButton_StartOrStop_clicked()
{
	if (ui.lineEdit_Port->text().isEmpty())
	{
		ui.lineEdit_Port->setText(ui.lineEdit_Port->placeholderText());
	}
	else if (ui.lineEdit_Port->text().toUInt() <= UINT16_MAX)
	{
	}
	else if (ui.pushButton_StartOrStop->text() == tr("开始"))
	{
		QMessageBox::warning(this, tr("警告"), tr("端口号无效！"));
		return;
	}

	if (ui.pushButton_StartOrStop->text() == tr("开始"))
	{
		StartReceive(ui.lineEdit_Port->text().toUShort());
		ui.pushButton_StartOrStop->setText(tr("停止"));
	}
	else if (ui.pushButton_StartOrStop->text() == tr("停止"))
	{
		StopReceive();
		ui.pushButton_StartOrStop->setText(tr("开始"));
	}
}

void UDPPackageReceiver::on_pushButton_Copy_clicked()
{
	QApplication::clipboard()->setText(ui.textEdit_Content->toPlainText());
}

void UDPPackageReceiver::on_pushButton_Clear_clicked()
{
	ui.textEdit_Content->clear();
}

void UDPPackageReceiver::OnReceivedData(const QString sData)
{
	ui.textEdit_Content->append(sData);
}

void UDPPackageReceiver::Init()
{
	QRegExp rx("[1-9][0-9]{0,4}");
	QValidator *validator = new QRegExpValidator(rx, this);
	ui.lineEdit_Port->setValidator(validator);
	ui.lineEdit_Port->setPlaceholderText("20110");

	//ui.textEdit_Content->setReadOnly(true);
}

void UDPPackageReceiver::StartReceive(ushort iPort)
{
	m_UDPPackageReceiver.SetPort(iPort);
	m_UDPPackageReceiver.Start();
}

void UDPPackageReceiver::StopReceive()
{
	m_UDPPackageReceiver.Stop();
	m_UDPPackageReceiver.Await();
}
