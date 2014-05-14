#include "job_container.h"

#include <>

namespace jobmang
{

	JobContainer::JobMap* JobContainer::_jobMap = new JobContainer::JobMap();

	JobContainer::JobContainer()
	{
	}

	JobContainer* JobContainer::getInstance()
	{
        if (!_instance)
            _instance = new JobContainer();
	    return _instance;
	}

	void JobContainer::updateJob(const JobDescript& job)
	{
		_jobMap[job.id] = job;
	}

	JobDescript* getJob(uint32_t id) const
	{
		JobMap::iterator iter = _jobMap.find(id);
		return (iter == NULL) ? NULL : &iter->second;
	}
}

