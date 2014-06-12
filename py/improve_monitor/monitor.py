#!/usr/bin/python

# import lib
import os
import time
import MySQLdb
import libvirt
from ctypes import *
from multiprocessing import Process,Lock

STR_LEN = 40

# define type
CHARARRAY40 = c_char * STR_LEN

# dirctory of vm instance(uuid as key)
g_vminstance_dir = {}

# list of host
# TODO:config the ip address in conf file
g_HostIP = ['192.168.8.78']

# define struct VmInstanceInfo
class VmInstanceInfo(Structure):
	_fields_ = [
	("accountId", c_int),
	("state", c_int),
	("uuid", CHARARRAY40),
	("hostName", CHARARRAY40),
	("pubIp", CHARARRAY40),
	("priIp", CHARARRAY40)
	]


# brief: get user email by account_id from uaccount db
# param: user's account_id
def FetchUsrEmail(account_id):
    conn=MySQLdb.connect(host='192.168.8.167',user='root',passwd='',port=3306, charset='utf8')
    cur=conn.cursor()
      
    conn.select_db('uaccount')
          
    sql = 'select * from t_member where user_id = %d' % account_id
    count = cur.execute(sql)
    print 'there has %s rows record' % count
              
    if count != 0:
        result = cur.fetchone()
        print 'user information:', result
        print 'user email:', result[4] # fetch third column of record (column index start with 0)

    cur.close()
    conn.close()


# brief: get vm instance through C++ interface
# param: None
def GetVmInstance():
    ll = cdll.LoadLibrary
    libObj = ll('./ListVmInstance.so')
    libObj.GetAllVmInstance()
    ret = libObj.TotalInstance()
    print 'python ret:%d' % ret 

    GetVmInstanceInfo = libObj.GetVmInstance;
    i = 0
    while i < ret:
        vmInstance = VmInstanceInfo()
        GetVmInstanceInfo(i, byref(vmInstance))

        instanceInfo = []
        # check information
        print "account id:", vmInstance.accountId
        # account id - index:0
        instanceInfo.append(vmInstance.accountId)
        print "state:", vmInstance.state
        # state - index:1
        instanceInfo.append(vmInstance.state)
        print "uuid:", vmInstance.uuid
        # uuid - index:2
        instanceInfo.append(vmInstance.uuid)
        print "hostName:", vmInstance.hostName
        # host name - index:3
        instanceInfo.append(vmInstance.hostName)
        print "priIp:", vmInstance.priIp
        # private ip - index:4
        instanceInfo.append(vmInstance.priIp)
        print "pubIp:", vmInstance.pubIp
        # public ip - index:5
        instanceInfo.append(vmInstance.pubIp)
        i = i + 1
        g_vminstance_dir[vmInstance.uuid] = instanceInfo
        print '*' * 20


# brief: check domain network state
# param: dom object
def CheckDomainNetworkStat(dom):
    uuid = dom.name()
    if uuid == 'vnat-master' or uuid == 'vnat-slave':
        return
    vmInstance = g_vminstance_dir[uuid]
    cmd = 'ping -c 2 ' + vmInstance[4] # ping private ip
    status = os.system(cmd)
    if status == 0:
        return 0
    else:
        return -1


# brief: check domain cpu state
# param: dom object
def CheckDomainCPUStat(dom):
    # cpu usage state
    cpu_time_bef = dom.info()[4]
    print 'Domain cpu time:%d' % dom.info()[4]
    interval_time = 3
    time.sleep(interval_time)
    cpu_time_aft = dom.info()[4]
    print 'Domain cpu time:%d' % dom.info()[4]

    cpu_use_per = 100 * (cpu_time_aft - cpu_time_bef) / (interval_time * 2 * 1e9)
    print 'Domain CPU usage percent:%d%%' % float('%.2f' % cpu_use_per)
    return 0


# brief: check domain memory state
# param: dom object 
def CheckDomainMemStat(dom):
    print 'Domain max memory:%sM' % (dom.info()[1]/1024)
    print 'Domain used memory:%sM' % (dom.info()[2] / 1024)
    # memory usage state
    print 'Domain memory used percent:%s%%' % int((float(dom.info()[2])/(dom.info()[1])) * 100)
    print 'Domain vcpu number:%d' % dom.info()[3]
    return 0


# brief: check component state of host and vm machine,
#        including network/cpu/memory
# param: host machine ip
def CheckComponetState(host_ip):
    server = 'qemu+ssh://root@' + host_ip + '/system'
    print server
    conn = libvirt.open(server)

    # Node information
    print 'Host Name:%s' % conn.getHostname()
    print 'Node info:', conn.getInfo()

    # getInfo()[1] return total memory sizes in MB
    total_mem = conn.getInfo()[1]
    print 'Node memory:%dG' % (total_mem / 1024)
    # getFreeMemory return memory sizes in bytes
    free_mem = conn.getFreeMemory() / 1024 / 1024 # unit: M
    print 'Node free memory:%sM' % (free_mem)

    used_mem = total_mem - free_mem
    print 'used_mem:%d' % used_mem
    print 'Memory used percent:%s%%' % int(float(used_mem) / (total_mem) * 100)

    print 'Node cpus number:%d' % conn.getInfo()[2]
    print 'Node cpu frequency:%dHz' % conn.getInfo()[3]
    print 'Node cpu core:%s' % (conn.getInfo()[6])
    print 'Number of defined all domains:%d' % (conn.numOfDefinedDomains() + conn.numOfDomains())
    #print 'CPU state:', conn.getCPUStats(cpuNum, flag)

    # Active domains information
    print 'Active domains as follows:'
    for i in conn.listDomainsID(): # get active domains ids
        dom = conn.lookupByID(i)

        print 'Domain uuid:%s' % dom.name()
        print 'Domain Id:%d' % dom.ID()
        print 'Domain state:', dom.info()[0]

        if CheckDomainNetworkStat(dom) < 0:
            SendWarnEmail()
        elif CheckDomainMemStat(dom) < 0:
            SendWarnEmail()
        elif CheckDomainCPUStat(dom) < 0:
            SendWarnEmail()
    conn.close()


# brief: process worker
# param: host machine start and end index
def MonitorMachine(start, end):
    index = start
    while index <= end:
        CheckComponetState(g_HostIP[index])
        index += 1


if __name__ == '__main__':

    GetVmInstance()

    process_list = []
    worker = Process(target = MonitorMachine, args = (0, 0))
    worker.start()
    process_list.append(worker)

    for worker in process_list:
      worker.join()
