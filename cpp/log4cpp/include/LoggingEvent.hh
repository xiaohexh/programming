#ifndef _LOG4CPP_LOGGINGEVENT_HH
#define _LOG4CPP_LOGGINGEVENT_HH

#include <string>
#include "Priority.hh"

namespace log4cpp
{
	class LoggingEvent
	{
	public:
		LoggingEvent(const std::string& category,
				const std::string& message,
				const std::string& ndc,
				Priority::Value priority);

	private:

		const std::string categoryName;
		const std::string message;
		const std::string ndc;
		Priority::Value priority;
		const std::string threadName;
	};
}

#endif // _LOG4CPP_LOGGINGEVENT_HH
