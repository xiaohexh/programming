#ifndef _LOG4CPP_PRIORITY_HH
#define _LOG4CPP_PRIORITY_HH

#include <string>
#include <stdexcept>

namespace log4cpp
{
	class Priority
	{
	public:
		static const int MESSAGE_SIZE; // = 8;

		typedef enum
		{
			EMERG = 0,
			FATAL = 0,
			ALERT = 100,
			CRIT  = 200,
			ERROR = 300,
			WARN  = 400,
			NOTICE = 500,
			INFO  = 600,
			DEBUG = 700,
			NOTSET = 800
		}PriorityLevel;

		// the type of Priority Values
		typedef int Value;

		static const std::string& getPriorityName(int priority) throw();

		static Value getPriorityValue(const std::string& priorityName)
			throw(std::invalid_argument);
	};
}
#endif // _LOG4CPP_PRIORITY_HH
