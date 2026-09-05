//
// Created by jinxing on 2026/3/2.
//

#include "ui_ipc_response_types.h"
#include "ui_ipc_response_handler.h"
#include "ui_ipc_response_helpers.h"

ROE_S32 UiIpcHandleResponseAdjustCompassSwitch(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustCompassSwitch);
}

ROE_S32 UiIpcHandleResponseStartCompassCalibration(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseStartCompassCalibration);
}

ROE_S32 UiIpcHandleResponseStopCompassCalibration(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseStopCompassCalibration);
}

ROE_S32 UiIpcHandleResponseSetCompassDeclination(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseSetCompassDeclination);
}

ROE_S32 UiIpcHandleResponseSaveCompassConfig(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseSaveCompassConfig);
}

ROE_S32 UiIpcHandleResponseAdjustGnssSwitch(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustGnssSwitch);
}

ROE_S32 UiIpcHandleResponseAdjustGnssSystem(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustGnssSystem);
}

ROE_S32 UiIpcHandleResponseAdjustCoordinateSystem(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustCoordinateSystem);
}

