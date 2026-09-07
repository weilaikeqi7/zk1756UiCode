#ifndef ZKSL_75_6LC_UI_IPC_DISPATCH_INTERNAL_H
#define ZKSL_75_6LC_UI_IPC_DISPATCH_INTERNAL_H

#include "ui/foundation/roeTypes.h"

typedef ROE_S32 (*UiIpcMessageHandler)(ROE_U8 * msgData);

typedef struct {
    ROE_SL firstType;
    ROE_SL endType;
    const UiIpcMessageHandler * handlers;
} UiIpcHandlerRange;

static inline ROE_S32 ui_ipc_dispatch_message(ROE_SL msgType,
                                           ROE_U8 * msgData,
                                           const UiIpcHandlerRange * ranges,
                                           ROE_SIZE rangeCount)
{
    if(!msgData || !ranges) return ROE_FAILURE;

    for(ROE_SIZE i = 0; i < rangeCount; i++) {
        const UiIpcHandlerRange * range = &ranges[i];
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

#endif // ZKSL_75_6LC_UI_IPC_DISPATCH_INTERNAL_H
