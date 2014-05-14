#ifndef _LOG4CPP_APPENDER_H
#define _LOG4CPP_APPENDER_H

#include <string>
#include <map>
#include <set>

namespace log4cpp
{
	class LOG4CPP_EXPORT Appender
	{
		public:
			/**
			 * Get a pointer to an existing Appender.
			 * @param name The name of the Appender to return.
			 * @returns a pointer to an existing Appender, or NULL.
			 **/ 
			static Appender* getAppender(const std::string& name);

			static bool reopenAll();

			static bool closeAll();

		protected:

			Appender(const std::string& name);

			virtual ~Appender();

			virtual void doAppend(const LoggingEvent& event) = 0;

			virtual bool reopen() = 0;

			virtual bool close() = 0;

			virtual bool requiresLayout() = 0;

			virtual void setLayout(Layout* layout) = 0;

			inline const std::string* getName() const{ return _name; };

			virtual void setThreshold(Priority::Value priority) = 0;

			virtual Priority::Value getThreshold() = 0;

			virtual void setFilter(Filter* filter) = 0;

			void Filter* getFilter() = 0;

		private:

			typedef std::map<std::string, Appender*> AppenderMap;

			static AppenderMap* _allAppenders;
			static threading::Mutex _appenderMapMutex;

			static AppenderMap& getAllAppenders();
			static void _deleteAllAppenders();
			static void _addAppender(Appender* appender);
			static void _removeAppender(Appender* appender);

			const std::string _name;
	};

	typedef std::set<Appender *> AppenderSet;
}

#endif // _LOG4CPP_APPENDER_H

