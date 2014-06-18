#!/usr/bin/python
# -*- coding: utf-8 -*-

g_NetworkUnavaliable = ['1', '2', '3', '4', '5']
g_CPUOutOfThreshold = ['1', '2', '3', '4', '5']
g_MemOutOfThreshold = ['1', '2', '3', '4', '5']

CPU_USAGE_THRESHOLD = 95
MEM_USAGE_THRESHOLD = 95

g_vminstance_dir = {'1':'192.168.8.78',
	'2':'192.168.8.78',
	'3':'192.168.8.78',
	'4':'192.168.8.78',
	'5':'192.168.8.78'
}

# after all process handle finish
network_ip_str = ''
cpu_ip_str = ''
mem_ip_str = ''

for uuid in g_NetworkUnavaliable:
	network_ip_str += g_vminstance_dir[uuid] + '\n'
for uuid in g_CPUOutOfThreshold:
	cpu_ip_str += g_vminstance_dir[uuid] + '\n'
for uuid in g_MemOutOfThreshold:
	mem_ip_str += g_vminstance_dir[uuid] + '\n'

if len(network_ip_str) != 0:
	msg = "'以下虚拟机网络连接状态出现故障:\n'"
	msg += network_ip_str
	print msg

