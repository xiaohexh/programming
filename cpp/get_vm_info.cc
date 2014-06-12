#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "umessage.h"
#include "udatabase.1000.2000.pb.h"
#include "ucloud.pb.h"
#include "log.h"
#include<memory>
using namespace std;
using namespace ucloud;
struct timeval g_sTimeNow;
int g_iWorkerIndex = 0;
Log g_sLog;

extern "C" {

int SendInternalRequest(uint32_t iParentID, void *pMessage) {
    abort();
    return 0;
}

int SendInternalResponse(void *pMessage, uint32_t iParentID) {
    abort();
    return 0;
}

}


int main(int argc, char **argv)
{
	int clientfd;
	struct sockaddr_in serveraddr;
	struct in_addr  serverip;
	char line[1024]={'\0'};
			
	if(argc<4)
	{
		printf("%s usage: <server ip> <server port> <vmid>\n",argv[0]);
		return -1;
	}
	if((clientfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		printf("create socket fail\n");
		return -1;
	}	
	memset(&serveraddr,0,sizeof	serveraddr);
	memset(&serverip,0,sizeof serverip);
	serveraddr.sin_family = AF_INET;
	if(!inet_aton(argv[1],&serverip))
	{
		printf("input param[%s] is not a ip\n",argv[1]);
		return -1;
	}	
	serveraddr.sin_addr.s_addr = serverip.s_addr; 
	serveraddr.sin_port = htons(atoi(argv[2])); 
	if(connect(clientfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) < 0)
	{
		perror("connect");	
		printf("connect [%s] fail\n",argv[1]);
		return -1;
	}
	printf("connect [%s] success\n",argv[1]);
	printf("witting to [%s] \n",argv[1]);
	
	//初始化协议
	UMessage *pMessage = NULL;
	string sql = "select value from t_vm_instance where id='";
	sql += argv[3];
	sql += "'";
	const char * db = "uvm";
	pMessage = NewMessage(NULL,
                1,
                "test",
                ucloud::udatabase::EXECUTE_SQL_REQUEST,
                0,
                false,
                0,
                0,
                "atoye",
                NULL,
				NULL);
    Body *pBody = pMessage->mutable_body();
    udatabase::ExecuteSqlRequest *pReq = pBody->MutableExtension(ucloud::udatabase::execute_sql_request);
    pReq->set_db(db);
    pReq->set_sql(sql.c_str());

	char *pData = NULL;
	int iMsgSize = EncodeMessage(pMessage, &pData, 0);
    cout << pMessage->DebugString() << endl << "==============================================================" << endl;
	delete pMessage;
    pMessage = NULL;	
	
	//发送消息
	int ret = 0;
	int sendsize = 0;
	ret = send(clientfd, pData, iMsgSize, 0);
	/*
	while((ret = send(clientfd, pData, iMsgSize+sizeof(unsigned), 0))>0)
	{
		sendsize += ret;
	}
	*/
	printf("send %d bytes to %s, msg_size is %d\n", ret, argv[1], iMsgSize);	
	//接收消息	
	delete [] pData;
	pData = NULL;
	ret = 0 ;
	int recvsize = 0;		
	char recvbuf[4096];	
	ret = recv(clientfd, recvbuf ,4096 ,0 );
	/*
	while((ret = recv(clientfd, recvbuf ,1024 ,0 ))>0)
	{
		recvsize +=ret;
	}

	*/
	UMessage *recvmsg = NULL;
	printf("recv %d bytes \n", ret);
	int iMessageSize = IsComplete(recvbuf, ret);
	if(iMessageSize>0)
	{
		int iUsed = DecodeMessage(&recvmsg, recvbuf, ret);		
	}
	if(recvmsg)
	{   	
		cout << recvmsg->DebugString() << endl << "==============================================================" << endl;
	}
	
	auto_ptr<UMessage> pUm((UMessage *)recvmsg);			
	const udatabase::ExecuteSqlResponse &sSqlRes = pUm->body().GetExtension(udatabase::execute_sql_response);
	const udatabase::SqlRow &sRow = sSqlRes.rows(0);
	const string &strValue = sRow.column(0);
	uvm::UVMVmInstance sVi;
	assert(sVi.ParseFromString(strValue));
		cout << sVi.DebugString() << endl << "==============================================================" << endl;
	/*
    sVi.mutable_vm_type()->set_id(7);
    sVi.mutable_vm_type()->set_name("中-2型");
    sVi.mutable_vm_type()->set_cpu_unit(40);
    sVi.mutable_vm_type()->set_memory_unit(8192);
    sVi.mutable_vm_type()->set_nic_unit(1024);
    sVi.mutable_vm_type()->set_disk_io_unit(20);
    sVi.mutable_vm_type()->set_disk_space_unit(160);
    sVi.mutable_vm_type()->set_vcpu_count(4);
    sVi.mutable_vm_type()->set_price(5);
	*/
	close(clientfd);	
	exit(0);
}
