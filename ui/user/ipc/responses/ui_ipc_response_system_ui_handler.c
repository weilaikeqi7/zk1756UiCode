//
// Created by jinxing on 2026/3/2.
//

#include "ui_ipc_response_types.h"
#include "ui_ipc_response_handler.h"
#include "ui_ipc_response_helpers.h"

ROE_S32 UiIpcHandleResponseShutdown(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseShutdown);
}

ROE_S32 UiIpcHandleResponseExitDialogBox(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseExitDialogBox);
}

ROE_S32 UiIpcHandleResponseSaveLanguageConfig(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseSaveLanguageConfig);
}

