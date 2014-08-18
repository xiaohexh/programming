#include "job_container.h"

#include <>

namespace jobmang
{

	JobManager::JobMap* JobManager::_jobMap = new JobManager::JobMap();

	JobManager::JobManager()
	{
	}

	JobManager* JobManager::getInstance()
	{
        if (!_instance)
            _instance = new JobManager();
	    return _instance;
	}

	void JobManager::updateJob(const JobDescript& job)
	{
		_jobMap[job.id] = job;
	}

	JobDescript* getJob(uint32_t id) const
	{
		JobMap::iterator iter = _jobMap.find(id);
		return (iter == NULL) ? NULL : &iter->second;
	}
}

