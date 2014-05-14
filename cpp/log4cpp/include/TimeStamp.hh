#ifndef _LOG4CPP_TIMESTAMP_HH
#define _LOG4CPP_TIMESTAMP_HH

namespace log4cpp
{
	class TimeStamp
	{
	public:
		/**
		 constructs a timestamp represent now
		 **/
		TimeStamp(); 

		TimeStamp(unsigned int seconds, unsigned int microSeconds = 0);

		inline int getSeconds() const { return m_seconds; }
		inline int getMilliSeconds() const { return m_microSeconds / 1000; }
		inline int getMicroSeconds() const { return m_microSeconds; }

		static inline const TimeStamp& getStartTime() { return m_startStamp; }

	protected:
		static TimeStamp m_startStamp;

		int m_seconds;
		int m_microSeconds;
	};
}

#endif // _LOG4CPP_TIMESTAMP_HH
