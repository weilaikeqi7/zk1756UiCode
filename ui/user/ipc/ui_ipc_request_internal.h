#ifndef ZKSL_75_6LC_UI_IPC_REQUEST_INTERNAL_H
#define ZKSL_75_6LC_UI_IPC_REQUEST_INTERNAL_H

#include "ui_ipc_request_types.h"

#define UI_MAX(x, y) ((x) > (y) ? (x) : (y))
#define UI_MAX_EXTEND_STRING_NUM UI_MAX(UI_MAX_MEDIA_FILE_NUM_ONE_PAGE, UI_RETICLE_NUM)

/* Host-only descriptors. Their pointers are used while building a message
 * and are never copied to the wire. */
typedef struct {
    ROE_U8 stringNum;
    const ROE_S8 * pStringList[UI_MAX_EXTEND_STRING_NUM];
} UiIpcStringList;

typedef struct {
    ROE_U8 version;
    ROE_U8 concreteType;
    const void * pFormatParam;
    ROE_S32 formatParamSize;
    UiIpcStringList strData;
} UiIpcRequestBuildParams;



ROE_S32 UiIpcSendRequest(ROE_S32 msgQueId,
                      ROE_S32 msgType,
                      const void * arg,
                      ROE_S32 argSize,
                      const UiIpcStringList * pStrData);

#endif // ZKSL_75_6LC_UI_IPC_REQUEST_INTERNAL_H
