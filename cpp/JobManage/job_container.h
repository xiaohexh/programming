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
    uint32_t frequency;             // 采集频率
    std::string path;               // 该Job对应的脚本执行路径
    uint32_t second_flag;           // 是否有第二个脚本
    std::string second_path;        // 第二个执行脚本的路径
    uint32_t stats_period;          // 两脚本统计间隔
    std::string args;               // 脚本参数
}JobDescript;

class JobContainer
{
public:
    static JobContainer* getInstance();

    void updateJob(const JobDescript& job);
	JobDescript* getJob(uint32_t id);

	typedef std::map<uint32_t, JobDescript> JobMap;
	JobMap& getAllJobs();

private:

	static JobMap* _jobMap;
	static JobContainer* _instance;

private:
    JobContainer();
    JobContainer(const JobContainer&);   // remove
    JobContainer& operator = (const JobContainer&);   // remove
};

} // namespace jobmang

#endif // _JOB_CONTAINER_H
