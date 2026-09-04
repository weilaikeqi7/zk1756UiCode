#ifndef ZKSL_75_6LC_IPC_MESSAGE_VALIDATE_H
#define ZKSL_75_6LC_IPC_MESSAGE_VALIDATE_H

#include "user/ipc/msg.h"

/* Validate the complete SysV message body returned by msgrcv(). */
ROE_S32 ipc_validate_message(ROE_SL msgType,
                             const RoeIpcMsgQueRawData_st * rawData,
                             ROE_SIZE receivedBytes);

#endif // ZKSL_75_6LC_IPC_MESSAGE_VALIDATE_H
