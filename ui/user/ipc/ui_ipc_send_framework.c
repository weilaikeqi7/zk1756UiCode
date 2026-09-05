#include "ui_ipc_request_sender.h"
#include "ui_ipc_request_internal.h"
#include <limits.h>

static ROE_S32 send_empty_request(ROE_S32 msgQueId, ROE_S32 msgType)
{
    return UiIpcSendRequest(msgQueId, msgType, ROE_NULL, 0, ROE_NULL);
}

#define DEFINE_EMPTY_REQUEST(functionName, messageType) \
    ROE_S32 functionName(ROE_S32 msgQueId) \
    { \
        return send_empty_request(msgQueId, messageType); \
    }

DEFINE_EMPTY_REQUEST(UiIpcSendGetVideoOutputParametersRequest, MSG_4_REQ_RES_GET_VIDEO_OUTPUT_PARA)
DEFINE_EMPTY_REQUEST(UiIpcSendGetVideoInputParametersRequest, MSG_4_REQ_RES_GET_VIDEO_INPUT_PARA)
DEFINE_EMPTY_REQUEST(UiIpcSendGetVideoInputCameraParametersRequest, MSG_4_REQ_RES_GET_VIDEO_INPUT_CAMERA_PARA)
DEFINE_EMPTY_REQUEST(UiIpcSendGetVideoInputLowLightParametersRequest, MSG_4_REQ_RES_GET_VIDEO_INPUT_LOW_LIGHT_PARA)
DEFINE_EMPTY_REQUEST(UiIpcSendGetVideoInputInfraredParametersRequest, MSG_4_REQ_RES_GET_VIDEO_INPUT_INFRARED_PARA)
DEFINE_EMPTY_REQUEST(UiIpcSendGetVideoInputRemoteParametersRequest, MSG_4_REQ_RES_GET_VIDEO_INPUT_REMOTE_PARA)
DEFINE_EMPTY_REQUEST(UiIpcSendGetAudioParametersRequest, MSG_4_REQ_RES_GET_AUDIO_PARA)
DEFINE_EMPTY_REQUEST(UiIpcSendCaptureMediaFileRequest, MSG_4_REQ_RES_CAPTURE_MEDIA_FILE)
DEFINE_EMPTY_REQUEST(UiIpcSendGetPeripheralUsbParametersRequest, MSG_4_REQ_RES_GET_PERIPHERAL_USB_PARA)
DEFINE_EMPTY_REQUEST(UiIpcSendGetPeripheralNetworkParametersRequest, MSG_4_REQ_RES_GET_PERIPHERAL_NETWORK_PARA)
DEFINE_EMPTY_REQUEST(UiIpcSendGetPeripheralCameraModuleParametersRequest,
                     MSG_4_REQ_RES_GET_PERIPHERAL_CAMERA_MODULE_PARA)
DEFINE_EMPTY_REQUEST(UiIpcSendGetPeripheralLowLightModuleParametersRequest,
                     MSG_4_REQ_RES_GET_PERIPHERAL_LOW_LIGHT_MODULE_PARA)
DEFINE_EMPTY_REQUEST(UiIpcSendGetPeripheralInfraredModuleParametersRequest,
                     MSG_4_REQ_RES_GET_PERIPHERAL_INFRARED_MODULE_PARA)
DEFINE_EMPTY_REQUEST(UiIpcSendGetPeripheralRemoteVideoModuleParametersRequest,
                     MSG_4_REQ_RES_GET_PERIPHERAL_REMOTE_VIDEO_MODULE_PARA)
DEFINE_EMPTY_REQUEST(UiIpcSendGetPeripheralCompassParametersRequest, MSG_4_REQ_RES_GET_PERIPHERAL_COMPASS_PARA)
DEFINE_EMPTY_REQUEST(UiIpcSendGetPeripheralGnssParametersRequest, MSG_4_REQ_RES_GET_PERIPHERAL_GNSS_PARA)
DEFINE_EMPTY_REQUEST(UiIpcSendGetPeripheralRangeFinderParametersRequest,
                     MSG_4_REQ_RES_GET_PERIPHERAL_RANGE_FINDER_PARA)
DEFINE_EMPTY_REQUEST(UiIpcSendGetPeripheralPanTiltParametersRequest, MSG_4_REQ_RES_GET_PERIPHERAL_PANTILT_PARA)

#undef DEFINE_EMPTY_REQUEST

ROE_S32 UiIpcSendCameraExposureRequest(ROE_S32 msgQueId, UiRequestAdjustCameraExposure * cameraExposure)
{
    if(!cameraExposure || cameraExposure->exposureType > 1 ||
       (cameraExposure->manualIspDigitalGain > 100 && cameraExposure->manualIspDigitalGain != UCHAR_MAX) ||
       (cameraExposure->manualSensorDigitalGain > 100 && cameraExposure->manualSensorDigitalGain != UCHAR_MAX) ||
       (cameraExposure->manualSensorAnalogGain > 100 && cameraExposure->manualSensorAnalogGain != UCHAR_MAX)) {
        return ROE_FAILURE;
    }

    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_CAMERA_EXPOSURE_ADJUST,
                         cameraExposure,
                         sizeof(*cameraExposure),
                         ROE_NULL);
}

ROE_S32 UiIpcSendRecordMediaFileRequest(ROE_S32 msgQueId, UiRequestRecordMediaFile * recordMediaFile)
{
    if(!recordMediaFile || recordMediaFile->recordSwitch > 1) return ROE_FAILURE;

    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_RECORD_MEDIA_FILE,
                         recordMediaFile,
                         sizeof(*recordMediaFile),
                         ROE_NULL);
}

ROE_S32 UiIpcSendInfraredManualRemoveBadPixelRequest(
    ROE_S32 msgQueId,
    UiRequestInfraredManualRemoveBadPixel * manualRemoveBadPixel)
{
    if(!manualRemoveBadPixel || manualRemoveBadPixel->operationType < 1 ||
       manualRemoveBadPixel->operationType > 3 || manualRemoveBadPixel->functionOperation > 1 ||
       manualRemoveBadPixel->cursorOperation > 4 || manualRemoveBadPixel->badPixelOperation > 1) {
        return ROE_FAILURE;
    }

    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_INFRARED_MANUAL_REMOVE_BAD_PIXEL,
                         manualRemoveBadPixel,
                         sizeof(*manualRemoveBadPixel),
                         ROE_NULL);
}

ROE_S32 UiIpcSendInfraredSdNucRequest(ROE_S32 msgQueId, UiRequestInfraredSdNuc * infraredSdNuc)
{
    if(!infraredSdNuc || infraredSdNuc->operationType > 3) return ROE_FAILURE;

    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_INFRARED_SD_NUC,
                         infraredSdNuc,
                         sizeof(*infraredSdNuc),
                         ROE_NULL);
}
