#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <vector>
#include <assert.h>
#include "list_vm_instance.h"

#define IP_ADDR "127.0.0.1"
#define PORT_NUM 8000

#ifdef __cplusplus
extern "C"
{
#endif

int SendInternalRequest(uint32_t iParentID, void *pMessage) {
    abort();
    return 0;
}

int SendInternalResponse(void *pMessage, uint32_t iParentID) {
    abort();
    return 0;
}

#ifdef __cplusplus
}
#endif

int main(int argc, char** argv)
{
    // initialize protocol
    ucloud::UMessage *pMessage = NewMessage(NULL, 1, MyUuid::NewUuid(), uvm::LIST_VM_INSTANCE_REQUEST, 999999, false, 0, 0, "ListVmInstance", NULL, NULL);
    ucloud::Body *pBody = pMessage->mutable_body();
    uvm::ListVmInstanceRequest &sReq = *pBody->MutableExtension(uvm::list_vm_instance_request);
    sReq.set_max_count(10);
    sReq.set_offset(0);

    char *pData = NULL;
    int iMsgSize = EncodeMessage(pMessage, &pData, 0);
    cout << pMessage->DebugString() << endl << "==============================================================" << endl;
    delete pMessage;
    pMessage = NULL;

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, IP_ADDR, &servaddr.sin_addr);
    servaddr.sin_port = htons(PORT_NUMBER);

    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(clientfd >= 0);

    socklen_t addr_len = sizeof(servaddr);
    int ret = connect(clientfd, (struct sockaddr*)&servadd, addr_len);
    if (ret < 0)
    {
        printf("connect to server failed\n");
        return -1;
    }

    //发送消息
    int sendsize = 0;
    ret = send(clientfd, pData, iMsgSize, 0);
    printf("send %d bytes data to server", ret);

    //接收消息
    delete [] pData;
    pData = NULL;
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
    const uvm::ListVmInstanceResponse &sRes = pUm->body().GetExtension(uvm::list_vm_instance_response);

    // 处理请求包返回
    if(sRes.rc().retcode() != 0) {
		printf("list vm instance response failed\n");
		return -1;
    }

	std::vector<uvm::UVMVmInstance> vmInstance;
    for(int i = 0; i < sRes.instance_size(); ++i)
	{
		vmInstance.push_back(sRes.instance(i));
    }
    //const string &strValue = sRow.column(0);
    //uvm::UVMVmInstance sVi;
    //assert(sVi.ParseFromString(strValue));
    //cout << sVi.DebugString() << endl << "==============================================================" << endl;

    close(clientfd);
    return 0;
}
