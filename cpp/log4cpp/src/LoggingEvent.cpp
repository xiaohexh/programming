#include "LoggingEvent.hh"

#include "threading/Threading.hh"

namespace log4cpp
{
	LoggingEvent::LoggingEvent(const std::string& category,
			const std::string& message,
			const std::string& ndc,
			Priority::Value priority)
		: categoryName(category)
		, message(message)
		, ndc(ndc)
		, priority(priority)
		, threadName(threading::getThreadId())
	{
	}
}
