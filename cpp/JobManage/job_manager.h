#ifndef _JOB_CONTAINER_H
#define _JOB_CONTAINER_H

#include <map>
#include <string>

namespace jobmang
{

typedef struct
{
    uint32_t id;                    // 任务ID
    std::string name;               // 名称
}JobDescript;

class JobManager
{
public:
    static JobManager* getInstance();

    void updateJob(const JobDescript& job);
	JobDescript* getJob(uint32_t id);

	typedef std::map<uint32_t, JobDescript> JobMap;
	JobMap& getAllJobs();

private:

	static JobMap* _jobMap;
	static JobManager* _instance;

private:
    JobManager();
    JobManager(const JobManager&);   // remove
    JobManager& operator = (const JobManager&);   // remove
};

} // namespace jobmang

#endif // _JOB_CONTAINER_H
