#include "UDPPackageSender.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	UDPPackageSender w;
	w.show();
	return a.exec();
}
