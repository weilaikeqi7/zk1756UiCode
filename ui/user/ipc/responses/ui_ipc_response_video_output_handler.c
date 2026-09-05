//
// Created by jinxing on 2026/3/2.
//

#include "ui_ipc_response_types.h"
#include "ui_ipc_response_handler.h"
#include "ui_ipc_response_helpers.h"

ROE_S32 UiIpcHandleResponseAdjustPipSwitch(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustPipSwitch);
}

ROE_S32 UiIpcHandleResponseAdjustExtendDisplaySwitch(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustExtendDisplaySwitch);
}

ROE_S32 UiIpcHandleResponseAdjustMainDisplayBrightness(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustMainDisplayBrightness);
}

ROE_S32 UiIpcHandleResponseAdjustMainDisplayContrast(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustMainDisplayContrast);
}

ROE_S32 UiIpcHandleResponseAdjustVideoZoom(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustVideoZoom);
}

ROE_S32 UiIpcHandleResponseFreezeVideoInput(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseFreezeVideoInput);
}

