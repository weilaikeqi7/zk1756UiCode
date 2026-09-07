//
// Created by jinxing on 2026/2/11.
//

#include "ui_ipc_request_sender.h"
#include "ui_ipc_request_internal.h"
#include "lvgl.h"

static void log_dist_req_array(const char * tag, const UiRequestWeaponOperateShootDistance * req)
{
    if(req == NULL) return;

    LV_LOG_USER("[RETICLE][REQ][%s] video=%u weapon=%u distanceIndex=%u distanceValue=%u opType=%u syncMove=%u",
                tag,
                (unsigned) req->videoChannel,
                (unsigned) req->weaponIndex,
                (unsigned) req->distanceIndex,
                (unsigned) req->distanceValue,
                (unsigned) req->opType,
                (unsigned) req->syncMoveReticle);
}

ROE_S32 UiIpcSendSetReticleCommonConfigRequest(ROE_S32 msgQueId, UiRequestSetReticleCommonConfig * setReticleCommonConfig)
{
    if(setReticleCommonConfig == NULL) return ROE_FAILURE;

    LV_LOG_USER("[RETICLE][REQ][3.61 common] save=%d show=%d rotate=%d ballistic=%d",
                (int) setReticleCommonConfig->saveFlag,
                (int) setReticleCommonConfig->showReticle,
                (int) setReticleCommonConfig->rotateReticle,
                (int) setReticleCommonConfig->ballisticSolve);
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_SET_RETICLE_COMMON_CONFIG,
                         setReticleCommonConfig,
                         sizeof(UiRequestSetReticleCommonConfig),
                         ROE_NULL);
}

ROE_S32 UiIpcSendWeaponMarkConfigOperateRequest(ROE_S32 msgQueId, UiRequestWeaponMarkConfigOperate * weaponMarkConfigOperate)
{
    if(weaponMarkConfigOperate == NULL) return ROE_FAILURE;

    LV_LOG_USER("[RETICLE][REQ][3.62 weaponCfg] video=%u weapon=%u opType=%u",
                (unsigned) weaponMarkConfigOperate->videoChannel,
                (unsigned) weaponMarkConfigOperate->weaponIndex,
                (unsigned) weaponMarkConfigOperate->opType);
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_WEAPON_OPERATE_MARK_CONFIG,
                         weaponMarkConfigOperate,
                         sizeof(UiRequestWeaponMarkConfigOperate),
                         ROE_NULL);
}

ROE_S32 UiIpcSendWeaponSetReticleStyleRequest(ROE_S32 msgQueId, UiRequestWeaponSetReticleStyle * weaponSetReticleStyle)
{
    if(weaponSetReticleStyle == NULL) return ROE_FAILURE;

    LV_LOG_USER("[RETICLE][REQ][3.63 style] video=%u weapon=%u style=%u",
                (unsigned) weaponSetReticleStyle->videoChannel,
                (unsigned) weaponSetReticleStyle->weaponIndex,
                (unsigned) weaponSetReticleStyle->reticleTypeIndex);
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_WEAPON_SET_RETICLE_STYLE,
                         weaponSetReticleStyle,
                         sizeof(UiRequestWeaponSetReticleStyle),
                         ROE_NULL);
}

ROE_S32 UiIpcSendWeaponSetReticleColorRequest(ROE_S32 msgQueId, UiRequestWeaponSetReticleColor * weaponSetReticleColor)
{
    if(weaponSetReticleColor == NULL) return ROE_FAILURE;

    LV_LOG_USER("[RETICLE][REQ][3.64 color] video=%u weapon=%u color=%u",
                (unsigned) weaponSetReticleColor->videoChannel,
                (unsigned) weaponSetReticleColor->weaponIndex,
                (unsigned) weaponSetReticleColor->reticleColorIndex);
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_WEAPON_SET_RETICLE_COLOR,
                         weaponSetReticleColor,
                         sizeof(UiRequestWeaponSetReticleColor),
                         ROE_NULL);
}

ROE_S32 UiIpcSendWeaponSetReticleBrightnessRequest(ROE_S32 msgQueId,
                                                   UiRequestWeaponSetReticleBrightness * weaponSetBrightness)
{
    if(weaponSetBrightness == NULL) return ROE_FAILURE;

    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_WEAPON_SET_RETICLE_LUMA,
                         weaponSetBrightness,
                         sizeof(UiRequestWeaponSetReticleBrightness),
                         ROE_NULL);
}

ROE_S32 UiIpcSendWeaponSetDefaultShootDistanceRequest(ROE_S32 msgQueId,
                                              UiRequestWeaponSetDefaultShootDistance * weaponSetDefaultShootDistance)
{
    if(weaponSetDefaultShootDistance == NULL) return ROE_FAILURE;

    LV_LOG_USER("[RETICLE][REQ][3.65 defaultDistance] video=%u weapon=%u distanceIndex=%u",
                (unsigned) weaponSetDefaultShootDistance->videoChannel,
                (unsigned) weaponSetDefaultShootDistance->weaponIndex,
                (unsigned) weaponSetDefaultShootDistance->defaultDistanceIndex);
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_WEAPON_SET_DEFAULT_SHOOT_DISTANCE,
                         weaponSetDefaultShootDistance,
                         sizeof(UiRequestWeaponSetDefaultShootDistance),
                         ROE_NULL);
}

ROE_S32 UiIpcSendWeaponOperateShootDistanceRequest(ROE_S32 msgQueId, UiRequestWeaponOperateShootDistance * weaponSetShootDistance)
{
    if(weaponSetShootDistance == NULL) return ROE_FAILURE;

    log_dist_req_array("3.66 distOp", weaponSetShootDistance);
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_WEAPON_OPERATE_SHOOT_DISTANCE,
                         weaponSetShootDistance,
                         sizeof(UiRequestWeaponOperateShootDistance),
                         ROE_NULL);
}

ROE_S32 UiIpcSendWeaponSetShootPositionRequest(ROE_S32 msgQueId, UiRequestWeaponSetShootPosition * weaponSetShootPosition)
{
    if(weaponSetShootPosition == NULL) return ROE_FAILURE;

    LV_LOG_USER("[RETICLE][REQ][3.67 shootPos] video=%u weapon=%u distanceIndex=%u moveDir=%u",
                (unsigned) weaponSetShootPosition->videoChannel,
                (unsigned) weaponSetShootPosition->weaponIndex,
                (unsigned) weaponSetShootPosition->distanceIndex,
                (unsigned) weaponSetShootPosition->moveDir);
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_WEAPON_SET_SHOOT_POSITION,
                         weaponSetShootPosition,
                         sizeof(UiRequestWeaponSetShootPosition),
                         ROE_NULL);
}

ROE_S32 UiIpcSendWeaponSetShootZeroRequest(ROE_S32 msgQueId, UiRequestWeaponSetShootZero * weaponSetShootZero)
{
    if(weaponSetShootZero == NULL) return ROE_FAILURE;

    LV_LOG_USER("[RETICLE][REQ][3.68 zero] video=%u weapon=%u distanceIndex=%u zeroType=%u",
                (unsigned) weaponSetShootZero->videoChannel,
                (unsigned) weaponSetShootZero->weaponIndex,
                (unsigned) weaponSetShootZero->distanceIndex,
                (unsigned) weaponSetShootZero->zeroType);
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_WEAPON_SET_SHOOT_ZERO,
                         weaponSetShootZero,
                         sizeof(UiRequestWeaponSetShootZero),
                         ROE_NULL);
}

ROE_S32 UiIpcSendWeaponSaveConfigRequest(ROE_S32 msgQueId)
{
    LV_LOG_USER("[RETICLE][REQ][3.69 save] send");
    return UiIpcSendRequest(msgQueId, MSG_4_REQ_RES_WEAPON_SAVE_CONFIG, ROE_NULL, 0, ROE_NULL);
}
