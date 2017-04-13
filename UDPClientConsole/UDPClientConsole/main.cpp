#include <iostream>

#include "Poco/String.h"
#include "Poco/Thread.h"
#include "DatagramSender.h"
#include "InputCmdMonitor.h"

int main(int argc, char *argv[])
{
	DatagramSender sender;
	switch (argc)
	{
		case 2:
		{
			sender.SetAddress(argv[1]);
			break;
		}
		case 3:
		{
			sender.SetAddress(argv[1]);
			sender.SetPort(argv[2]);
			break;
		}
		case 4:
		{
			sender.SetAddress(argv[1]);
			sender.SetPort(argv[2]);
			sender.SetContent(argv[3]);
			break;
		}
		case 5:
		{
			sender.SetAddress(argv[1]);
			sender.SetPort(argv[2]);
			sender.SetContent(argv[3]);
			sender.SetTimes(argv[4]);
			break;
		}
		default:
		break;
	}

	Poco::Thread senderThread;
	senderThread.start(sender);
	
	InputCmdMonitor monitor;
	Poco::Thread monitorThread;
	monitorThread.start(monitor);

	while (!monitor.Stopped() && !senderThread.tryJoin(1000));

	sender.Stop();
	senderThread.join();

	return 0;
}