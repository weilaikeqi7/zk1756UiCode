#ifndef ZKSL_75_6LC_IPCMSGQUE4UISND_INTERNAL_H
#define ZKSL_75_6LC_IPCMSGQUE4UISND_INTERNAL_H

#include "ipcMsgQue4UiSndRequest.h"

ROE_S32 SendMsg4UiReq(ROE_S32 msgQueId, ROE_S32 msgType, void * arg, ROE_S32 argSize, StringData_st * pStrData);

#endif
