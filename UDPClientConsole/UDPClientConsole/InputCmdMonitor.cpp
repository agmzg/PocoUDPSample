#include <iostream>

#include "Poco/String.h"
#include "InputCmdMonitor.h"

InputCmdMonitor::InputCmdMonitor()
: m_bStop(false)
{
}

InputCmdMonitor::~InputCmdMonitor()
{
}

void InputCmdMonitor::run()
{
	try
	{
		do 
		{
			std::string sCmd;
			std::cin >> sCmd;
			if (Poco::toLower<std::string>(sCmd) == "close")
			{
				m_bStop = true;
			}
		}
		while (!m_bStop);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknow exception!" << std::endl;
	}
}

bool InputCmdMonitor::Stopped() const
{
	return m_bStop;
}
