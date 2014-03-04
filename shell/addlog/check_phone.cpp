#include "check_phone.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <memory>
#include <sstream>

#include "uaccount.h"
#include "machine_pool.h"
#include "machine_factory.h"
#include "id_generator.h"

static const int MYID = uaccount::CHECK_PHONE_REQUEST;

FACTORY_IMPLEMENT(CheckPhoneMachine, MYID);

DEFAULT_IMPLEMENT(MYID, INIT_STATE, CheckPhoneMachine, Entry_Init);
DEFAULT_IMPLEMENT(MYID, GET_USER_INFO_STATE, CheckPhoneMachine, Entry_GetUserInfo);

CheckPhoneMachine::CheckPhoneMachine() {
}

CheckPhoneMachine::~CheckPhoneMachine() {
}

void CheckPhoneMachine::Dump(int iFD) {
}

int CheckPhoneMachine::Timeout(bool bMachineTimeout) {
    return 100;
}

int CheckPhoneMachine::StateMachineType() {
    return MYID;
}

int CheckPhoneMachine::Entry_Init(InternalHead_t *pHead, void *pMessage) {
    assert(pHead && pMessage);
    auto_ptr<UMessage> pRequest((UMessage*)pMessage);
    assert(pRequest->head().message_type() == MYID);
    assert(pRequest->body().HasExtension(uaccount::check_phone_request));
    m_sInternalHead = *pHead;
    m_sReq = pRequest->body().GetExtension(uaccount::check_phone_request);

    MakeResponse(pRequest.get(), uaccount::CHECK_PHONE_RESPONSE, &m_sResponse);
    m_pRes = m_sResponse.mutable_body()->MutableExtension(uaccount::check_phone_response);

    return GetUserInfo();
}

int CheckPhoneMachine::GetUserInfo() {
    UMessage sReqMsg;
    NewMessage(&sReqMsg, Flowno(), m_sResponse.head().session_no(), uaccount::GET_USER_INFO_NEW_REQUEST, g_iWorkerIndex, m_sResponse.head().tint_flag(), 
            m_iID, 0, "check phone", NULL, NULL);
    uaccount::GetUserInfoNewRequest &sReq = *sReqMsg.mutable_body()->MutableExtension(uaccount::get_user_info_new_request);
    sReq.set_user_phone(m_sReq.user_phone());
    SendInternalRequest(sReqMsg);

    m_iState = GET_USER_INFO_STATE;
    return SM_CONTINUE;
}

int CheckPhoneMachine::Entry_GetUserInfo(InternalHead_t *pHead, void *pMessage) {
    auto_ptr<UMessage> pRequest((UMessage*)pMessage);
    if(pRequest->head().message_type() != uaccount::GET_USER_INFO_NEW_RESPONSE) {
        ERROR("message type error %d", pRequest->head().message_type());
        return SM_CONTINUE;
    };
    assert(pRequest->body().HasExtension(uaccount::get_user_info_new_response));
    const uaccount::GetUserInfoNewResponse &sRes = pRequest->body().GetExtension(uaccount::get_user_info_new_response);

    if (sRes.rc().retcode() != 0) {
        *m_pRes->mutable_rc() = sRes.rc();
        SendResponse(m_sResponse);
        return SM_FINISH;
    }

    if(sRes.user_info_size() <= 0) {
        m_pRes->mutable_rc()->set_retcode(0);
    }
    else {
        m_pRes->mutable_rc()->set_retcode(-uaccount::EC_ACCOUNT_PHONE_EXIST);
        m_pRes->mutable_rc()->set_error_message("phone exists");
    }

    SendResponse(m_sResponse);
    return SM_FINISH;
}

