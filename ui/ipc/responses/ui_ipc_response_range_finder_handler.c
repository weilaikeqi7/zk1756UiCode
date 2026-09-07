//
// Created by jinxing on 2026/3/2.
//

#include "ui_ipc_response_types.h"
#include "ui_ipc_response_handler.h"
#include "ui_ipc_response_helpers.h"

ROE_S32 UiIpcHandleResponseRangeFinderOperate(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseRangeFinderOperate);
}

ROE_S32 UiIpcHandleResponseAdjustRangeFrequency(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustRangeFrequency);
}

ROE_S32 UiIpcHandleResponseAdjustRangeDuration(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustRangeDuration);
}

