//
// Created by jinxing on 2026/3/2.
//

#include "ipcMsgQue4UiRcvRes.h"
#include "handleRcvRes.h"
#include "play_handle.h"
#include "mainpage_event_handle.h"

ROE_S32 handleParseGetMediaFileListMsg(ROE_U8 * msgData)
{
    RspGetMediaFileList_st * result = (RspGetMediaFileList_st *)msgData;
    MediaFileInfo_st * fileInfo[UI_MAX_MEDIA_FILE_NUM_ONE_PAGE];
    /* 处理获取媒体文件列表结果 */
    if(result->result == 0) {
        /* 解析变长文件列表数据 */
        ROE_U8 fileCount = result->fileCount;
        ROE_U8 * fileDataPtr = result->fileData;

        /* 遍历解析每个 MediaFileInfo_st */
        for(ROE_U8 i = 0; i < fileCount; i++) {
            fileInfo[i] = (MediaFileInfo_st *)fileDataPtr;
            /* 处理文件信息：type, size, duration, createTime, name */
            fileDataPtr += sizeof(MediaFileInfo_st) + fileInfo[i]->nameLen;
        }
        play_list_display(result, fileInfo);
    }
    return ROE_SUCCESS;
}

ROE_S32 handleParseGetMediaFileListPageMsg(ROE_U8 * msgData)
{
    RspGetMediaFileListPage_st * result = (RspGetMediaFileListPage_st *)msgData;
    /* 处理媒体文件列表翻页结果 */
    if(result->result == 0) {
        ROE_U8 fileCount = result->fileCount;
        ROE_U8 * fileDataPtr = result->fileData;

        for(ROE_U8 i = 0; i < fileCount; i++) {
            MediaFileInfo_st * fileInfo = (MediaFileInfo_st *)fileDataPtr;
            /* 处理文件信息 */
            fileDataPtr += sizeof(MediaFileInfo_st) + fileInfo->nameLen;
        }
    }
    return ROE_SUCCESS;
}

ROE_S32 handleParseDelMediaFileMsg(ROE_U8 * msgData)
{
    RspDelMediaFile_st * result = (RspDelMediaFile_st *)msgData;
    /* 处理媒体文件删除结果 */
    if(result->result == 0) {
        ReqGetMediaFileList_st getMediaFileList;
        getMediaFileList.reqFileType = -1;
        if(playlist_state.find_type == 1) {
            getMediaFileList.year = 2024;
            getMediaFileList.month = 0;
            getMediaFileList.day = 0;
            getMediaFileList.hour = -1;
            getMediaFileList.minute = -1;
            getMediaFileList.second = -1;
            if(findDateTime.year == 2024) {
            } else if(findDateTime.month == 0) {
                getMediaFileList.year = findDateTime.year;
            } else if(findDateTime.day == 0) {
                getMediaFileList.year = findDateTime.year;
                getMediaFileList.month = findDateTime.month;
            } else if(findDateTime.hour == -1) {
                getMediaFileList.year = findDateTime.year;
                getMediaFileList.month = findDateTime.month;
                getMediaFileList.day = findDateTime.day;
            } else if(findDateTime.minute == -1) {
                getMediaFileList.year = findDateTime.year;
                getMediaFileList.month = findDateTime.month;
                getMediaFileList.day = findDateTime.day;
                getMediaFileList.hour = findDateTime.hour;
            } else {
                getMediaFileList.year = findDateTime.year;
                getMediaFileList.month = findDateTime.month;
                getMediaFileList.day = findDateTime.day;
                getMediaFileList.hour = findDateTime.hour;
                getMediaFileList.minute = findDateTime.minute;
            }
        } else if(playlist_state.find_type == 2) {
            getMediaFileList.year = 2024;
            getMediaFileList.month = 0;
            getMediaFileList.day = 0;
            getMediaFileList.hour = -1;
            getMediaFileList.minute = -1;
            getMediaFileList.second = -1;
        }
        if(playlist_state.current_items == 13) {
            getMediaFileList.startIndex = (playlist_state.current_page_index - 1) * UI_MAX_MEDIA_FILE_NUM_ONE_PAGE -
                                          UI_MAX_MEDIA_FILE_NUM_ONE_PAGE;
            playlist_state.current_page_index--;
        } else {
            getMediaFileList.startIndex = (playlist_state.current_page_index - 1) * UI_MAX_MEDIA_FILE_NUM_ONE_PAGE;
        }
        getMediaFileList.reqCount = 10;
        playlist_state.req_type = 1;
        SendMsg4UiGetMediaFileListReq(global_parameters.sendMsgQueId, &getMediaFileList);
    }
    return ROE_SUCCESS;
}

ROE_S32 handleParsePlayMediaFileMsg(ROE_U8 * msgData)
{
    RspPlayMediaFile_st * result = (RspPlayMediaFile_st *)msgData;
    /* 处理媒体文件播放结果 */
    if(result->result == 0) {
        lv_group_remove_all_objs(keypad_group);
        lv_group_add_obj(keypad_group, ui_PlayBar);
        lv_screen_load(ui_PlayBar);
    }
    return ROE_SUCCESS;
}

ROE_S32 handleParsePlayPriorOrNextMediaFileMsg(ROE_U8 * msgData)
{
    RspPlayPriorOrNextMediaFile_st * result = (RspPlayPriorOrNextMediaFile_st *)msgData;
    /* 处理播放上一个/下一个媒体文件结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseExitMediaPlayStatusMsg(ROE_U8 * msgData)
{
    RspExitMediaPlay_st * result = (RspExitMediaPlay_st *)msgData;
    /* 处理退出媒体文件播放结果 */
    if(result->result == 0) {
        lv_group_remove_all_objs(keypad_group);
        for(uint32_t i = 0; i < playlist_state.current_items; i++) {
            lv_group_add_obj(keypad_group, ui_PlayList[i]);
        }
        lv_group_focus_obj(ui_PlayList[playlist_state.current_index]);
        lv_screen_load(ui_ScrFileMgr);
    }
    return ROE_SUCCESS;
}
