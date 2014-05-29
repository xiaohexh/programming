#ifndef _LOG4CPP_LAYOUT_HH
#define _LOG4CPP_LAYOUT_HH

#include "LoggingEvent.hh"

namespace log4cpp
{
	class Layout
	{
	public:
		virtual ~Layout() {}

		virtual std::string format(const LoggingEvent& event) = 0;
	};
}

#endif // _LOG4CPP_LAYOUT_HH
