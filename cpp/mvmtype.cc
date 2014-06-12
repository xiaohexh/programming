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
    //uvm::UVMVmInstance NewsVi;
    //NewsVi = sVi;
    //NewsVi.clear_disks();
    //uvm::UVMVmDisk *disk = NewsVi.add_disks();
    //*disk = sVi.disks(0);
	/*
	switch( sVi.vm_type().id() ) 
	{
		case 1:
    		sVi.mutable_vm_type()->set_vcpu_count(1);
			break;
		case 2:
    		sVi.mutable_vm_type()->set_vcpu_count(2);
			break;
		case 3:
    		sVi.mutable_vm_type()->set_vcpu_count(4);
			break;
		case 4:
    		sVi.mutable_vm_type()->set_vcpu_count(8);
			break;
		case 5:
    		sVi.mutable_vm_type()->set_vcpu_count(16);
			break;
	}
	
	*/
    //sVi.set_private_ip(0,"10.0.0.1");
    //sVi.set_image_id("dfd288f3-9b60-4bff-87c5-866df0c056b0");
    //sVi.mutable_disks(0)->set_source_file("/opt/data/limg/dfd288f3-9b60-4bff-87c5-866df0c056b0.img");
    //sVi.mutable_disks(1)->set_size(50);
    //sVi.set_type(2);
    //sVi.mutable_vm_type()->set_id(2);
    //sVi.mutable_vm_type()->set_cpu_unit(80);
    //sVi.mutable_vm_type()->set_memory_unit(4096);
    //sVi.mutable_vm_type()->set_nic_unit(1024);
    //sVi.mutable_vm_type()->set_disk_io_unit(20);
    //sVi.mutable_vm_type()->set_vcpu_count(8);
    //sVi.mutable_vm_type()->set_name("Ucloud自定义机型");
    //sVi.mutable_vm_type()->set_price(40);
    //sVi.mutable_vm_type()->set_blkiotune_weight(800);
    //sVi.mutable_vm_type()->clear_permission();
	//sVi.set_blkiotune_weight(800);
    //sVi.mutable_disks(1)->set_size(160);
    //sVi.mutable_vm_type()->set_disk_space_unit(90);
	////sVi.set_state(uvm::RUNNING);

	//sVi.set_state(uvm::SHUT_OFF);
	//sVi.set_image_id("cfeb115d-886f-4163-966d-f2528856e875");
    //sVi.mutable_disks(0)->set_source_file("/opt/data/limg/cfeb115d-886f-4163-966d-f2528856e875.img");
    //sVi.mutable_vm_type()->set_cpu_unit(80);
    //sVi.mutable_vm_type()->set_vcpu_count(8);
    //sVi.mutable_vm_type()->set_memory_unit(12288);
    //sVi.mutable_private_mac_addr(0)->set_private_mac_addr("52:54:00:C4:0E:72");

    sVi.set_private_mac_addr(0,"52:54:00:C4:0E:72");

    string strRealValue = sVi.SerializeAsString();

	sql = "update t_vm_instance set value=?,modify_time=unix_timestamp(current_timestamp)";
	sql +=" where id='";
	sql += argv[3];
	sql += "'";
	pMessage = NewMessage(NULL,
                1,
                "test",
                ucloud::udatabase::REPLACE_BLOB_REQUEST,
                0,
                false,
                0,
                0,
                "atoye",
                NULL,
				NULL);
    pBody = pMessage->mutable_body();
    udatabase::ReplaceBlobRequest *pbReq = pBody->MutableExtension(ucloud::udatabase::replace_blob_request);
    pbReq = pBody->MutableExtension(ucloud::udatabase::replace_blob_request);
    pbReq->set_db(db);
    pbReq->set_sql(sql.c_str());
    pbReq->set_blob(strRealValue);

    pData = NULL;
    iMsgSize = EncodeMessage(pMessage, &pData, 0);
    cout << pMessage->DebugString() << endl << "==============================================================" << endl;
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
	recvsize = 0;		
	recvbuf[4096];	
	ret = recv(clientfd, recvbuf ,4096 ,0 );
	recvmsg = NULL;
	printf("recv %d bytes \n", ret);
	iMessageSize = IsComplete(recvbuf, ret);
	if(iMessageSize>0)
	{
		int iUsed = DecodeMessage(&recvmsg, recvbuf, ret);		
	}
	if(recvmsg)
	{   	
		cout << recvmsg->DebugString() << endl << "==============================================================" << endl;
	}
	
	close(clientfd);	
	exit(0);
}
