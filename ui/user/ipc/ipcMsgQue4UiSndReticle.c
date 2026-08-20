//
// Created by jinxing on 2026/2/11.
//

#include "ipcMsgQue4UiSndRequest.h"
#include "ipcMsgQue4UiSndInternal.h"
#include "lvgl.h"

static void log_dist_req_array(const char * tag, const ReqWeaponOperateShootDist_st * req)
{
    LV_LOG_USER("[RETICLE][REQ][%s] video=%u weapon=%u distIndex=%u distValue=%u opType=%u syncMove=%u",
                tag,
                (unsigned) req->videoChannel,
                (unsigned) req->weaponIndex,
                (unsigned) req->distIndex,
                (unsigned) req->distValue,
                (unsigned) req->opType,
                (unsigned) req->syncMoveReticle);
}

ROE_S32 SendMsg4UiSetReticuleCommonConfigReq(ROE_S32 msgQueId, ReqSetReticleCommonConfig_st * setReticleCommonConfig)
{
    LV_LOG_USER("[RETICLE][REQ][3.61 common] save=%d show=%d rotate=%d ballistic=%d",
                (int) setReticleCommonConfig->saveFlag,
                (int) setReticleCommonConfig->showReticle,
                (int) setReticleCommonConfig->rotateReticle,
                (int) setReticleCommonConfig->ballisticSolve);
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_SET_RETICLE_COMMON_CONFIG,
                         setReticleCommonConfig,
                         sizeof(ReqSetReticleCommonConfig_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiWeaponMarkConfigOperateReq(ROE_S32 msgQueId, ReqWeaponMarkConfigOperate_st * weaponMarkConfigOperate)
{
    LV_LOG_USER("[RETICLE][REQ][3.62 weaponCfg] video=%u weapon=%u opType=%u",
                (unsigned) weaponMarkConfigOperate->videoChannel,
                (unsigned) weaponMarkConfigOperate->weaponIndex,
                (unsigned) weaponMarkConfigOperate->opType);
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_WEAPON_OPERATE_MARK_CONFIG,
                         weaponMarkConfigOperate,
                         sizeof(ReqWeaponMarkConfigOperate_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiWeaponSetReticleStyleReq(ROE_S32 msgQueId, ReqWeaponSetReticleStyle_st * weaponSetReticleStyle)
{
    LV_LOG_USER("[RETICLE][REQ][3.63 style] video=%u weapon=%u style=%u",
                (unsigned) weaponSetReticleStyle->videoChannel,
                (unsigned) weaponSetReticleStyle->weaponIndex,
                (unsigned) weaponSetReticleStyle->reticleTypeIndex);
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_WEAPON_SET_RETICLE_STYLE,
                         weaponSetReticleStyle,
                         sizeof(ReqWeaponSetReticleStyle_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiWeaponSetReticleColorReq(ROE_S32 msgQueId, ReqWeaponSetReticleColor_st * weaponSetReticleColor)
{
    LV_LOG_USER("[RETICLE][REQ][3.64 color] video=%u weapon=%u color=%u",
                (unsigned) weaponSetReticleColor->videoChannel,
                (unsigned) weaponSetReticleColor->weaponIndex,
                (unsigned) weaponSetReticleColor->reticleColorIndex);
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_WEAPON_SET_RETICLE_COLOR,
                         weaponSetReticleColor,
                         sizeof(ReqWeaponSetReticleColor_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiWeaponSetDefaltShootDistReq(ROE_S32 msgQueId,
                                              ReqWeaponSetDefaultShootDist_st * weaponSetDefaltShootDist)
{
    LV_LOG_USER("[RETICLE][REQ][3.65 defaultDist] video=%u weapon=%u distIndex=%u",
                (unsigned) weaponSetDefaltShootDist->videoChannel,
                (unsigned) weaponSetDefaltShootDist->weaponIndex,
                (unsigned) weaponSetDefaltShootDist->defaultDistIndex);
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_WEAPON_SET_DEFAULT_SHOOT_DISTANCE,
                         weaponSetDefaltShootDist,
                         sizeof(ReqWeaponSetDefaultShootDist_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiWeaponOperateShootDistReq(ROE_S32 msgQueId, ReqWeaponOperateShootDist_st * weaponSetShootDist)
{
    log_dist_req_array("3.66 distOp", weaponSetShootDist);
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_WEAPON_OPERATE_SHOOT_DISTANCE,
                         weaponSetShootDist,
                         sizeof(ReqWeaponOperateShootDist_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiWeaponSetShootPositionReq(ROE_S32 msgQueId, ReqWeaponSetShootPosition_st * weaponSetShootPosition)
{
    LV_LOG_USER("[RETICLE][REQ][3.67 shootPos] video=%u weapon=%u distIndex=%u moveDir=%u",
                (unsigned) weaponSetShootPosition->videoChannel,
                (unsigned) weaponSetShootPosition->weaponIndex,
                (unsigned) weaponSetShootPosition->distIndex,
                (unsigned) weaponSetShootPosition->moveDir);
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_WEAPON_SET_SHOOT_POSITION,
                         weaponSetShootPosition,
                         sizeof(ReqWeaponSetShootPosition_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiWeaponSetShootZeroReq(ROE_S32 msgQueId, ReqWeaponSetShootZero_st * weaponSetShootZero)
{
    LV_LOG_USER("[RETICLE][REQ][3.68 zero] video=%u weapon=%u distIndex=%u zeroType=%u",
                (unsigned) weaponSetShootZero->videoChannel,
                (unsigned) weaponSetShootZero->weaponIndex,
                (unsigned) weaponSetShootZero->distIndex,
                (unsigned) weaponSetShootZero->zeroType);
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_WEAPON_SET_SHOOT_ZERO,
                         weaponSetShootZero,
                         sizeof(ReqWeaponSetShootZero_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiWeaponSaveConfigReq(ROE_S32 msgQueId)
{
    LV_LOG_USER("[RETICLE][REQ][3.69 save] send");
    return SendMsg4UiReq(msgQueId, MSG_4_REQ_RES_WEAPON_SAVE_CONFIG, ROE_NULL, 0, ROE_NULL);
}