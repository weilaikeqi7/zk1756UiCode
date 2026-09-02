#include "ipcMsgQue4UiSndRequest.h"
#include "ipcMsgQue4UiSndInternal.h"
#include <limits.h>

static ROE_S32 send_empty_request(ROE_S32 msgQueId, ROE_S32 msgType)
{
    return SendMsg4UiReq(msgQueId, msgType, ROE_NULL, 0, ROE_NULL);
}

#define DEFINE_EMPTY_REQUEST(functionName, messageType) \
    ROE_S32 functionName(ROE_S32 msgQueId) \
    { \
        return send_empty_request(msgQueId, messageType); \
    }

DEFINE_EMPTY_REQUEST(SendMsg4UiGetVideoOutputParaReq, MSG_4_REQ_RES_GET_VIDEO_OUTPUT_PARA)
DEFINE_EMPTY_REQUEST(SendMsg4UiGetVideoInputParaReq, MSG_4_REQ_RES_GET_VIDEO_INPUT_PARA)
DEFINE_EMPTY_REQUEST(SendMsg4UiGetVideoInputCameraParaReq, MSG_4_REQ_RES_GET_VIDEO_INPUT_CAMERA_PARA)
DEFINE_EMPTY_REQUEST(SendMsg4UiGetVideoInputLowLightParaReq, MSG_4_REQ_RES_GET_VIDEO_INPUT_LOW_LIGHT_PARA)
DEFINE_EMPTY_REQUEST(SendMsg4UiGetVideoInputInfraredParaReq, MSG_4_REQ_RES_GET_VIDEO_INPUT_INFRARED_PARA)
DEFINE_EMPTY_REQUEST(SendMsg4UiGetVideoInputRemoteParaReq, MSG_4_REQ_RES_GET_VIDEO_INPUT_REMOTE_PARA)
DEFINE_EMPTY_REQUEST(SendMsg4UiGetAudioParaReq, MSG_4_REQ_RES_GET_AUDIO_PARA)
DEFINE_EMPTY_REQUEST(SendMsg4UiCaptureMediaFileReq, MSG_4_REQ_RES_CAPTURE_MEDIA_FILE)
DEFINE_EMPTY_REQUEST(SendMsg4UiGetPeripheralUsbParaReq, MSG_4_REQ_RES_GET_PERIPHERAL_USB_PARA)
DEFINE_EMPTY_REQUEST(SendMsg4UiGetPeripheralNetworkParaReq, MSG_4_REQ_RES_GET_PERIPHERAL_NETWORK_PARA)
DEFINE_EMPTY_REQUEST(SendMsg4UiGetPeripheralCameraModuleParaReq,
                     MSG_4_REQ_RES_GET_PERIPHERAL_CAMERA_MODULE_PARA)
DEFINE_EMPTY_REQUEST(SendMsg4UiGetPeripheralLowLightModuleParaReq,
                     MSG_4_REQ_RES_GET_PERIPHERAL_LOW_LIGHT_MODULE_PARA)
DEFINE_EMPTY_REQUEST(SendMsg4UiGetPeripheralInfraredModuleParaReq,
                     MSG_4_REQ_RES_GET_PERIPHERAL_INFRARED_MODULE_PARA)
DEFINE_EMPTY_REQUEST(SendMsg4UiGetPeripheralRemotedVideoModuleParaReq,
                     MSG_4_REQ_RES_GET_PERIPHERAL_REMOTED_VIDEO_MODULE_PARA)
DEFINE_EMPTY_REQUEST(SendMsg4UiGetPeripheralCompassParaReq, MSG_4_REQ_RES_GET_PERIPHERAL_COMPASS_PARA)
DEFINE_EMPTY_REQUEST(SendMsg4UiGetPeripheralGnssParaReq, MSG_4_REQ_RES_GET_PERIPHERAL_GNSS_PARA)
DEFINE_EMPTY_REQUEST(SendMsg4UiGetPeripheralRangeFinderParaReq,
                     MSG_4_REQ_RES_GET_PERIPHERAL_RANGE_FINDER_PARA)
DEFINE_EMPTY_REQUEST(SendMsg4UiGetPeripheralPanTiltParaReq, MSG_4_REQ_RES_GET_PERIPHERAL_PANTILT_PARA)

#undef DEFINE_EMPTY_REQUEST

ROE_S32 SendMsg4UiCameraExposureReq(ROE_S32 msgQueId, ReqAdjustCameraExposure_st * cameraExposure)
{
    if(!cameraExposure || cameraExposure->exposureType > 1 ||
       (cameraExposure->manualIspDigitalGain > 100 && cameraExposure->manualIspDigitalGain != UCHAR_MAX) ||
       (cameraExposure->manualSensorDigitalGain > 100 && cameraExposure->manualSensorDigitalGain != UCHAR_MAX) ||
       (cameraExposure->manualSensorAnalogGain > 100 && cameraExposure->manualSensorAnalogGain != UCHAR_MAX)) {
        return ROE_FAILURE;
    }

    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_CAMERA_EXPOSURE_ADJUST,
                         cameraExposure,
                         sizeof(*cameraExposure),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiRecordMediaFileReq(ROE_S32 msgQueId, ReqRecordMediaFile_st * recordMediaFile)
{
    if(!recordMediaFile || recordMediaFile->recordSwitch > 1) return ROE_FAILURE;

    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_RECORD_MEDIA_FILE,
                         recordMediaFile,
                         sizeof(*recordMediaFile),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiInfraredManualRemoveBadPixelReq(
    ROE_S32 msgQueId,
    ReqInfraredManualRemoveBadPixel_st * manualRemoveBadPixel)
{
    if(!manualRemoveBadPixel || manualRemoveBadPixel->operationType < 1 ||
       manualRemoveBadPixel->operationType > 3 || manualRemoveBadPixel->functionOperation > 1 ||
       manualRemoveBadPixel->cursorOperation > 4 || manualRemoveBadPixel->badPixelOperation > 1) {
        return ROE_FAILURE;
    }

    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_INFRARED_MANUAL_REMOVE_BAD_PIXEL,
                         manualRemoveBadPixel,
                         sizeof(*manualRemoveBadPixel),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiInfraredSdNucReq(ROE_S32 msgQueId, ReqInfraredSdNuc_st * infraredSdNuc)
{
    if(!infraredSdNuc || infraredSdNuc->operationType > 3) return ROE_FAILURE;

    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_INFRARED_SD_NUC,
                         infraredSdNuc,
                         sizeof(*infraredSdNuc),
                         ROE_NULL);
}
