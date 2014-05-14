#include "Appender.h"

namespace log4cpp
{
	Appender::AppenderMap* Appender::_allAppenders = 0;
	threading::Mutex Appender::_appenderMapMutex;

	Appender::AppenderMap& Appender::_getAllAppenders()
	{
		if (!_allAppenders)
			_allAppenders = new Appender::AppenderMap();
		return *_allAppenders;
	}

	Appender* Appender::getAppender(const std::string& name)
	{
		threading::ScopedLock lock(_appenderMapMutex);
		AppenderMap& allAppenders = Appender::_getAllAppenders();
		AppenderMap::iterator i = allAppenders.find(name);
		return (allAppenders.end() == i) ? NULL : (i->second);
	}

	void Appender::_addAppender(Appender* appender)
	{
		threading::ScopedLock lock(_appenderMapMutex);
		_getAllAppenders()[appender->getName()] = appender;
	}

	void Appender::_removeAppender(Appender* appender)
	{
		threading::ScopedLock(_appenderMapMutex);
		_getAllAppenders().erase(appender->getName());
		if (_getAllAppender().empty())
		{
			delete _allAppenders;
			_allAppenders = 0;
		}
	}

	bool Appender::reopenAll()
	{
		threading::ScopedLock lock(_appenderMapMutex);
		bool result = true;
		AppenderMap& allAppenders = Appender::_getAllAppenders();
		for (AppenderMap::iterator i = allAppenders.begin();
				i != allAppenders.end();
				++ i)
		{
			result = result && (i->second->reopen());
		}

		return result;
	}

	void Appender::closeAll()
	{
		threading::ScopedLock lock(_appenderMapMutex);
		AppenderMap& allAppenders = _getAllAppenders();
		for (AppenderMap::iterator i = allAppenders.begin();
				i = allAppender.end();
				++ i)
		{
			i->second->close();
		}
	}

	void Appender::_deleteAllAppenders()
	{
		threading::ScopedLock lock(_appenderMapMutex);
		AppenderMap& allAppenders = _getAllAppenders();
		for (AppenderMap::iterator i = allAppenders.begin();
				i = allAppender.end();)
		{
			Appender* app = i->second;
			++ i;
			delete app;
		}
	}

	Appender::Appender(const std::string& name)
		: _name(name)
	{
		_addAppender(this);
	}

	Appender::~Appender()
	{
		_removeAppender(this);
	}
}
