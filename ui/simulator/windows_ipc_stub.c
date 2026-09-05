#include "user/ipc/ui_ipc_request_internal.h"

ROE_S32 UiIpcSendRequest(ROE_S32 msgQueId,
                       ROE_S32 msgType,
                       const void * arg,
                       ROE_S32 argSize,
                       const UiIpcStringList * pStrData)
{
    (void)msgQueId;
    (void)msgType;
    (void)arg;
    (void)argSize;
    (void)pStrData;
    return ROE_SUCCESS;
}
