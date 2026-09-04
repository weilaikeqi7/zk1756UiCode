#include "ipc/ipcMsgQue4UiSndInternal.h"

ROE_S32 SendMsg4UiReq(ROE_S32 msgQueId,
                       ROE_S32 msgType,
                       const void * arg,
                       ROE_S32 argSize,
                       const StringData_st * pStrData)
{
    (void)msgQueId;
    (void)msgType;
    (void)arg;
    (void)argSize;
    (void)pStrData;
    return ROE_SUCCESS;
}
