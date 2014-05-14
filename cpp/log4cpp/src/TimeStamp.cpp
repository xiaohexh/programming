#include "TimeStamp.hh"

#include <cstring>

#ifdef LOG4CPP_HAVE_GETTIMEOFDAY
#include <sys/time.h>
#else
#ifdef LOG4CPP_HAVE_FTIME
#include <sys/timeb.h>
#else
#include <time.h>
#endif // LOG4CPP_HAVE_FTIME
#endif // LOG4CPP_HAVE_GETTIMEOFDAY

namespace log4cpp
{
	TimeStamp TimeStamp::m_startStamp;

	TimeStamp::TimeStamp()
	{
#ifdef LOG4CPP_HAVE_GETTIMEOFDAY
		struct timeval tv;
		::gettimeofday(&tv, NULL);
		m_seconds = tv.tv_sec;
		m_microSeconds = tv.tv_usec;	
#else
#ifdef LOG4CPP_HAVE_FTIME
		struct timeb tb;
		::ftime(&tb);
		m_seconds = tb.time;
		m_microSeconds = tb.millitm * 1000;
#else
		m_seconds = ::time(NULL);
		m_microSeconds = 0;
#endif
#endif
	}

	TimeStamp::TimeStamp(unsigned int seconds, unsigned int microSeconds)
		: m_seconds(seconds)
		, m_microSeconds(microSeconds)
	{
	}
}
