//
// Created by jinxing on 2026/3/2.
//

#include "ipcMsgQue4UiRcvRes.h"
#include "lvgl/lvgl.h"
#include "handleRcvRes.h"
#include "ipc_response_helpers.h"
#include "play_handle.h"
#include "play_handle_internal.h"
#include "mainpage_event_handle.h"

ROE_S32 handleParseGetMediaFileListMsg(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;

    RspGetMediaFileList_st * result = (RspGetMediaFileList_st *)msgData;
    if(result->result != 0U) {
        LV_LOG_WARN("[MEDIA][RSP] get file list failed result:%u", (unsigned)result->result);
        return ROE_FAILURE;
    }
    MediaFileInfo_st * fileInfo[UI_MAX_MEDIA_FILE_NUM_ONE_PAGE];
    /* 处理获取媒体文件列表结果 */
    /* 解析变长文件列表数据；完整长度和 fileCount 已在接收层校验。 */
    ROE_U8 fileCount = result->fileCount;
    ROE_U8 * fileDataPtr = result->fileData;
    for(ROE_U8 i = 0; i < fileCount; i++) {
        fileInfo[i] = (MediaFileInfo_st *)fileDataPtr;
        fileDataPtr += sizeof(MediaFileInfo_st) + fileInfo[i]->nameLen;
    }
    play_list_display(result, fileInfo);
    return ROE_SUCCESS;
}

ROE_S32 handleParseGetMediaFileListPageMsg(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;

    RspGetMediaFileListPage_st * result = (RspGetMediaFileListPage_st *)msgData;
    /* 处理媒体文件列表翻页结果 */
    if(result->result != 0U) {
        LV_LOG_WARN("[MEDIA][RSP] page list failed result:%u", (unsigned)result->result);
        return ROE_FAILURE;
    }
    /* 3.28 的分页响应与 3.27 的列表响应布局不同，当前 UI 使用
     * 3.27 请求完成页面刷新，因此这里只传播结果，不重复构造列表。 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseDelMediaFileMsg(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;

    RspDelMediaFile_st * result = (RspDelMediaFile_st *)msgData;
    /* 处理媒体文件删除结果 */
    if(result->result == 0U) {
        ReqGetMediaFileList_st getMediaFileList;
        ROE_U32 startIndex = 0;
        if(playlist_state.current_items == 13) {
            if(playlist_state.current_page_index > 1) {
                playlist_state.current_page_index--;
            }
        }
        if(playlist_state.current_page_index > 0) {
            startIndex = (ROE_U32)(playlist_state.current_page_index - 1) * UI_MAX_MEDIA_FILE_NUM_ONE_PAGE;
        }
        play_media_list_request_init(&getMediaFileList, startIndex);
        playlist_state.req_type = 1;
        SendMsg4UiGetMediaFileListReq(global_parameters.sendMsgQueId, &getMediaFileList);
    } else {
        LV_LOG_WARN("[MEDIA][RSP] delete file failed result:%u", (unsigned)result->result);
        return ROE_FAILURE;
    }
    return ROE_SUCCESS;
}

ROE_S32 handleParsePlayMediaFileMsg(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;

    RspPlayMediaFile_st * result = (RspPlayMediaFile_st *)msgData;
    /* 处理媒体文件播放结果 */
    if(result->result == 0U) {
        lv_group_remove_all_objs(keypad_group);
        lv_group_add_obj(keypad_group, ui_PlayBar);
        lv_screen_load(ui_PlayBar);
    }
    else {
        LV_LOG_WARN("[MEDIA][RSP] play file failed result:%u", (unsigned)result->result);
        return ROE_FAILURE;
    }
    return ROE_SUCCESS;
}

ROE_S32 handleParsePlayPriorOrNextMediaFileMsg(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;

    RspPlayPriorOrNextMediaFile_st * result = (RspPlayPriorOrNextMediaFile_st *)msgData;
    /* 处理播放上一个/下一个媒体文件结果 */
    return ipc_response_result(result, result->result, __func__);
}

ROE_S32 handleParseExitMediaPlayStatusMsg(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;

    RspExitMediaPlay_st * result = (RspExitMediaPlay_st *)msgData;
    /* 处理退出媒体文件播放结果 */
    if(result->result == 0U) {
        lv_group_remove_all_objs(keypad_group);
        for(uint32_t i = 0; i < playlist_state.current_items; i++) {
            lv_group_add_obj(keypad_group, ui_PlayList[i]);
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
