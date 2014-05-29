#include "threading/Threading.hh"
#include <stdio.h>
#include <string>

#if defined(LOG4CPP_HAVE_THREADING)&&defined(LOG4CPP_USE_PTHREADS)

namespace log4cpp
{
	namespace threading
	{
		std::string getThreadId()
		{
			char buffer[16];
			::sprintf(buffer, "%lu", pthread_self());
			return std::string(buffer);
		}
	}
}

#endif
