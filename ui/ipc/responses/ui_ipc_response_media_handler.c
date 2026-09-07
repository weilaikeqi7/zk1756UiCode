//
// Created by jinxing on 2026/3/2.
//

#include "ui_ipc_response_types.h"
#include "lvgl/lvgl.h"
#include "ui_ipc_response_handler.h"
#include "ui_ipc_response_helpers.h"
#include "playback_internal.h"
#include "menu_event_registry.h"
#include "ui_focus_manager.h"

ROE_S32 UiIpcHandleResponseExitPlaybackList(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseExitPlaybackList);
}

ROE_S32 UiIpcHandleResponseGetMediaFileList(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;

    UiResponseGetMediaFileList * result = (UiResponseGetMediaFileList *)msgData;
    if(result->result != 0U) {
        LV_LOG_WARN("[MEDIA][RSP] get file list failed result:%u", (unsigned)result->result);
        return ROE_FAILURE;
    }
    UiMediaFileInfo * fileInfo[UI_MAX_MEDIA_FILE_NUM_ONE_PAGE];
    /* 处理获取媒体文件列表结果 */
    /* 解析变长文件列表数据；完整长度和 fileCount 已在接收层校验。 */
    ROE_U8 fileCount = result->fileCount;
    ROE_U8 * fileDataPtr = result->fileData;
    for(ROE_U8 i = 0; i < fileCount; i++) {
        fileInfo[i] = (UiMediaFileInfo *)fileDataPtr;
        fileDataPtr += sizeof(UiMediaFileInfo) + fileInfo[i]->nameLength;
    }
    play_list_display(result, fileInfo);
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleResponseDeleteMediaFile(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;

    UiResponseDeleteMediaFile * result = (UiResponseDeleteMediaFile *)msgData;
    /* 处理媒体文件删除结果 */
    if(result->result == 0U) {
        UiRequestGetMediaFileList getMediaFileList;
        ROE_U32 startIndex = 0;
        if(playlist_state.current_items == PLAYLIST_MEDIA_FIRST_INDEX + PLAYLIST_ACTION_ITEM_COUNT) {
            if(playlist_state.current_page_index > 1) {
                playlist_state.current_page_index--;
            }
        }
        if(playlist_state.current_page_index > 0) {
            startIndex = (ROE_U32)(playlist_state.current_page_index - 1) * UI_MAX_MEDIA_FILE_NUM_ONE_PAGE;
        }
        play_media_list_request_init(&getMediaFileList, startIndex);
        playlist_state.req_type = 1;
        UiIpcSendGetMediaFileListRequest(global_parameters.sendMsgQueId, &getMediaFileList);
    } else {
        LV_LOG_WARN("[MEDIA][RSP] delete file failed result:%u", (unsigned)result->result);
        return ROE_FAILURE;
    }
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleResponsePlayMediaFile(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;

    UiResponsePlayMediaFile * result = (UiResponsePlayMediaFile *)msgData;
    /* 处理媒体文件播放结果 */
    if(result->result == 0U) {
        if(keypad_group == NULL || ui_PlayBar == NULL) {
            LV_LOG_ERROR("[MEDIA][UI][DROP] playback controls are not initialized");
            return ROE_FAILURE;
        }
        ui_focus_group_clear();
        ui_focus_group_add(ui_PlayBar);
        lv_screen_load(ui_PlayBar);
    }
    else {
        LV_LOG_WARN("[MEDIA][RSP] play file failed result:%u", (unsigned)result->result);
        return ROE_FAILURE;
    }
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleResponsePlayAdjacentMediaFile(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;

    UiResponsePlayAdjacentMediaFile * result = (UiResponsePlayAdjacentMediaFile *)msgData;
    /* 处理播放上一个/下一个媒体文件结果 */
    return ui_ipc_response_result(result, result->result, __func__);
}

ROE_S32 UiIpcHandleResponseStopMediaFilePlay(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;

    UiResponseStopMediaFilePlay * result = (UiResponseStopMediaFilePlay *)msgData;
    /* 处理退出媒体文件播放结果 */
    if(result->result == 0U) {
        if(keypad_group == NULL || ui_ScrFileMgr == NULL) {
            LV_LOG_ERROR("[MEDIA][UI][DROP] file-manager controls are not initialized");
            return ROE_FAILURE;
        }
        ui_focus_group_clear();
        for(uint32_t i = 0; i < playlist_state.current_items; i++) {
            ui_focus_group_add(ui_PlayList[i]);
        }
        play_list_focus_index(playlist_state.current_index);
        lv_screen_load(ui_ScrFileMgr);
    }
    else {
        LV_LOG_WARN("[MEDIA][RSP] exit media play failed result:%u", (unsigned)result->result);
        return ROE_FAILURE;
    }
    return ROE_SUCCESS;
}
