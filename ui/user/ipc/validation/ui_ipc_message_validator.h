#ifndef ZKSL_75_6LC_UI_IPC_MESSAGE_VALIDATOR_H
#define ZKSL_75_6LC_UI_IPC_MESSAGE_VALIDATOR_H

#include "user/ipc/protocol/ui_ipc_message.h"

/* Validate the complete SysV message body returned by msgrcv(). */
ROE_S32 ui_ipc_validate_message(ROE_SL msgType,
                             const UiIpcRawData * rawData,
                             ROE_SIZE receivedBytes);

#endif // ZKSL_75_6LC_UI_IPC_MESSAGE_VALIDATOR_H
