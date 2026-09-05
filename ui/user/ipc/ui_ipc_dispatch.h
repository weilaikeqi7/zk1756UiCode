#ifndef ZKSL_75_6LC_UI_IPC_DISPATCH_H
#define ZKSL_75_6LC_UI_IPC_DISPATCH_H

#include "ui_ipc_message.h"

ROE_S32 UiIpcDispatchNotification(ROE_SL msgType, const UiIpcRawData * rawData);
ROE_S32 UiIpcDispatchResponse(ROE_SL msgType, const UiIpcRawData * rawData);

#endif // ZKSL_75_6LC_UI_IPC_DISPATCH_H
