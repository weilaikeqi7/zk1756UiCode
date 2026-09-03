#ifndef ZKSL_75_6LC_IPC_MESSAGE_DISPATCH_H
#define ZKSL_75_6LC_IPC_MESSAGE_DISPATCH_H

#include "roeTypes.h"

typedef ROE_S32 (*IpcMessageHandler)(ROE_U8 * msgData);

typedef struct {
    ROE_SL firstType;
    ROE_SL endType;
    const IpcMessageHandler * handlers;
} IpcMessageHandlerRange_st;

static inline ROE_S32 ipc_dispatch_message(ROE_SL msgType,
                                           ROE_U8 * msgData,
                                           const IpcMessageHandlerRange_st * ranges,
                                           ROE_SIZE rangeCount)
{
    if(!msgData || !ranges) return ROE_FAILURE;

    for(ROE_SIZE i = 0; i < rangeCount; i++) {
        const IpcMessageHandlerRange_st * range = &ranges[i];
        if(msgType < range->firstType || msgType >= range->endType) continue;
        if(!range->handlers) return ROE_FAILURE;

        ROE_SL handlerIndex = msgType - range->firstType;
        ROE_SL handlerCount = range->endType - range->firstType;
        if(handlerIndex < 0 || handlerIndex >= handlerCount || !range->handlers[handlerIndex]) {
            return ROE_FAILURE;
        }
        return range->handlers[handlerIndex](msgData);
    }

    return ROE_FAILURE;
}

#endif // ZKSL_75_6LC_IPC_MESSAGE_DISPATCH_H
