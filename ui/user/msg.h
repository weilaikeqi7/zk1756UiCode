//
// Created by jinxing on 2026/2/10.
//

#ifndef ZKSL_75_6LC_MSG_H
#define ZKSL_75_6LC_MSG_H

#include "roeTypes.h"

#define MAX_ROE_IPC_MSG_LENGTH  (512+4)
#define MAX_ROE_IPC_DATA_LENGTH (MAX_ROE_IPC_MSG_LENGTH - sizeof(ROE_S32))

/* 消息缓冲区定义 */
typedef struct
{
    ROE_SL msgType;  /* 消息类型 > 0 */
    ROE_U8 msgData[MAX_ROE_IPC_MSG_LENGTH];
} RoeIpcMsgQueBuff_st;

/* 原始数据定义 */
typedef struct
{
    ROE_S32 dataLength;  /* 数据长度 */
    ROE_U8  data[MAX_ROE_IPC_MSG_LENGTH-4];
} RoeIpcMsgQueRawData_st;

void* message_recv_thread(void* arg);
void process_pending_ipc_events(void);
#endif //ZKSL_75_6LC_MSG_H
