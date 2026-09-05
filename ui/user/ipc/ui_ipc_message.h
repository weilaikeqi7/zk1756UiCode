//
// Created by jinxing on 2026/2/10.
//

#ifndef ZKSL_75_6LC_UI_IPC_MESSAGE_H
#define ZKSL_75_6LC_UI_IPC_MESSAGE_H

#include "user/core/roeTypes.h"

#define MAX_ROE_IPC_DATA_LENGTH 512U
#define MAX_ROE_IPC_MSG_LENGTH  (MAX_ROE_IPC_DATA_LENGTH + sizeof(ROE_S32))

/* 消息缓冲区定义 */
typedef struct
{
    ROE_SL msgType;  /* 消息类型 > 0 */
    ROE_U8 msgData[MAX_ROE_IPC_MSG_LENGTH];
} UiIpcMessageBuffer;

/* 原始数据定义 */
typedef struct
{
    ROE_S32 dataLength;  /* 数据长度 */
    ROE_U8  data[MAX_ROE_IPC_DATA_LENGTH];
} UiIpcRawData;

void ui_ipc_process_pending_events(void);
#endif //ZKSL_75_6LC_UI_IPC_MESSAGE_H
