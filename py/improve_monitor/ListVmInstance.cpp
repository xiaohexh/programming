#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <memory>
#include <vector>
#include <assert.h>
#include "my_uuid.h"
#include "umessage.h"
#include "ucloud.pb.h"
#include "uvm.8000.10000.pb.h"

using namespace ucloud;

#define IP_ADDR "192.168.8.80"
#define PORT_NUM 8000
#define STR_LEN 40
#define UUID_LEN 36
#define IP_LEN 15
#define HOSTNAME_LEN 64
#define BUFF_LEN 128

#ifdef __cplusplus
extern "C"
{
#endif

static std::vector<uvm::UVMVmInstance> g_vecVmInstance;

struct VmInstanceInfo
{
    int accountId;
    int state;
    char uuid[STR_LEN];
    char hostName[STR_LEN];
    char pubIp[STR_LEN];
    char priIp[STR_LEN];
}; 

int SendInternalRequest(uint32_t iParentID, void *pMessage)
{
    abort();
    return 0;
}

int SendInternalResponse(void *pMessage, uint32_t iParentID)
{
    abort();
    return 0;
}

int TotalInstance()
{
    return g_vecVmInstance.size();
}

void GetVmInstance(int index, struct VmInstanceInfo* pStruct)
{
    // account id
    pStruct->accountId = g_vecVmInstance[index].account_id();
    // vm state
    pStruct->state = g_vecVmInstance[index].state();
    // uuid
    strcpy(pStruct->uuid, g_vecVmInstance[index].id().c_str());
    // host name
    strcpy(pStruct->hostName, g_vecVmInstance[index].hostname().c_str());
    // public ip
    int public_ip_size = g_vecVmInstance[index].public_ipinfo_size();
    if (0 != public_ip_size)
        strcpy(pStruct->pubIp, g_vecVmInstance[index].public_ipinfo(0).public_ip().c_str());
    // private ip
    int private_ip_size = g_vecVmInstance[index].private_ip_size();
    if (0 != private_ip_size)
        strcpy(pStruct->priIp, g_vecVmInstance[index].private_ip(0).c_str());
}

int GetAllVmInstance()
{
    // initialize protocol
    UMessage *pMessage = NewMessage(NULL, 1, MyUuid::NewUuid(), uvm::LIST_VM_INSTANCE_REQUEST, 999999, false, 0, 0, "ListVmInstance", NULL, NULL);
    Body *pBody = pMessage->mutable_body();
    uvm::ListVmInstanceRequest &sReq = *pBody->MutableExtension(uvm::list_vm_instance_request);
    sReq.set_max_count(10);
    sReq.set_offset(0);

    char *pData = NULL;
    int iMsgSize = EncodeMessage(pMessage, &pData, 0);
    std::cout << pMessage->DebugString() << std::endl;
    std::cout << "===============================================" << endl;
    delete pMessage;
    pMessage = NULL;

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, IP_ADDR, &servaddr.sin_addr);
    servaddr.sin_port = htons(PORT_NUM);

    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(clientfd >= 0);

    socklen_t addr_len = sizeof(servaddr);
    int ret = connect(clientfd, (struct sockaddr*)&servaddr, addr_len);
    if (ret < 0)
    {
        printf("connect to server failed\n");
        close(clientfd);
        return -1;
    }

    //发送消息
    ret = send(clientfd, pData, iMsgSize, 0);
    printf("send %d bytes data to server\n", ret);
    delete [] pData;
    pData = NULL;

    //接收消息
    char recvbuf[4096];
    memset(recvbuf, '\0', 4096);
    //TODO: receive date many times until receive finished
    ret = recv(clientfd, recvbuf, 4096 - 1, 0);

    UMessage *recvmsg = NULL;
    printf("recv %d bytes \n", ret);
    int iMessageSize = IsComplete(recvbuf, ret);
    if (iMessageSize > 0)
    {
        DecodeMessage(&recvmsg, recvbuf, ret);
    }
    if (recvmsg)
    {
        std::cout << recvmsg->DebugString() << std::endl;
        std::cout << "===============================================" << std::endl;
    }

    std::auto_ptr<UMessage> pUm((UMessage *)recvmsg);
    const uvm::ListVmInstanceResponse &sRes = pUm->body().GetExtension(uvm::list_vm_instance_response);

    // 处理请求包返回
    if(sRes.rc().retcode() != 0) {
		printf("list vm instance response failed\n");
        close(clientfd);
		return -1;
    }

    for(int i = 0; i < sRes.instance_size(); ++i)
	{
		g_vecVmInstance.push_back(sRes.instance(i));
    }

    close(clientfd);
    return 0;
}

/*
int main(int argc, char** argv)
{
    char* id = "c4fc4b78-a409-4ea5-81b7-35b4e71dcec0";
    GetVmInstance();
    std::cout << strlen(id) << std::endl;
    return 0;
}
*/

#ifdef __cplusplus
}
#endif

