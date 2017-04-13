#ifndef _INPUTCMDMONITOR_H_
#define _INPUTCMDMONITOR_H_

#include "Poco/Runnable.h"
#include "Poco/Thread.h"

class InputCmdMonitor : public Poco::Runnable
{
public:
	InputCmdMonitor();

	virtual ~InputCmdMonitor();

	bool Stopped() const;

protected:
	void run();

private:
	bool m_bStop;
};

#endif //_INPUTCMDMONITOR_H_