//
// Created by jinxing on 2026/3/2.
//

#include "ui_ipc_response_types.h"
#include "ui_ipc_response_handler.h"
#include "ui_ipc_response_helpers.h"

ROE_S32 UiIpcHandleResponseInfraredSetBadPixelThreshold(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseInfraredSetBadPixelThreshold);
}

ROE_S32 UiIpcHandleResponseInfraredBadPixelOperate(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseInfraredBadPixelOperate);
}

ROE_S32 UiIpcHandleResponseInfraredHotPixelRepair(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseInfraredHotPixelRepair);
}

ROE_S32 UiIpcHandleResponseInfraredHotspotTrackingSwitch(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseInfraredHotspotTrackingSwitch);
}

ROE_S32 UiIpcHandleResponseInfraredScenarioMode(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseInfraredScenarioMode);
}

ROE_S32 UiIpcHandleResponseInfraredEnhanceImage(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseInfraredEnhanceImage);
}

