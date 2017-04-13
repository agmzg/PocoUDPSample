#include "UDPPackageReceiver.h"
#include <QtWidgets/QApplication>
#include <QtCore/QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	UDPPackageReceiver w;
	w.show();
	return a.exec();
}
