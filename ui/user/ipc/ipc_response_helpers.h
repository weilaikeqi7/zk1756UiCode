#ifndef ZKSL_75_6LC_IPC_RESPONSE_HELPERS_H
#define ZKSL_75_6LC_IPC_RESPONSE_HELPERS_H

#include "lvgl/lvgl.h"
#include "user/core/roeTypes.h"

static inline ROE_S32 ipc_response_result(const void * msgData,
                                          ROE_U8 result,
                                          const char * handlerName)
{
    if(msgData == NULL) {
        LV_LOG_ERROR("[IPC][RESPONSE][DROP] null payload handler:%s", handlerName);
        return ROE_FAILURE;
    }

    if(result != 0U) {
        LV_LOG_WARN("[IPC][RESPONSE][FAIL] handler:%s result:%u", handlerName, (unsigned)result);
        return ROE_FAILURE;
    }

    return ROE_SUCCESS;
}

#define IPC_RETURN_RESPONSE(msgData, responseType) \
    do { \
        if((msgData) == NULL) { \
            return ipc_response_result(NULL, 0U, __func__); \
        } \
        const responseType * response = (const responseType *)(msgData); \
        return ipc_response_result(response, response->result, __func__); \
    } while(0)

#endif
