#ifndef IDANPLUGINAPI_H
#define IDANPLUGINAPI_H

/*
* IdanPluginAPI.h
* API for external tools that need to use IDAN
* Author: Binyamin Appelbaum
* Date: 25.03.18
*/

#include "IdanWrapper.h"

// Functions that can be used by the plugin
extern "C" {
    IdanWrapper* CreateIdanObject(const char* confFilePath);

    void DeleteIdanObject(IdanWrapper* pObj);

    void RunIdan(IdanWrapper* pObj);

    void GetIdanData(IdanWrapper* pObj);

    /********************************* HLC Primary *************************************************/
    unsigned char GetHLCPShutDownCmd(IdanWrapper* pObj);

    unsigned char GetHLCPEmergencyCmd(IdanWrapper* pObj);

    unsigned char GetHLCPSteerCmdMsb(IdanWrapper* pObj);

    unsigned char GetHLCPSteerCmdLsb(IdanWrapper* pObj);

    unsigned char GetHLCPGasCmdMsb(IdanWrapper* pObj);

    unsigned char GetHLCPGasCmdLsb(IdanWrapper* pObj);

    /********************************* HLC Secondary *************************************************/
    unsigned char GetHLCSShutDownCmd(IdanWrapper* pObj);
    
    bool IsHLCSRoadLightsApplied(IdanWrapper* pObj);

    bool IsHLCSHighBeamApplied(IdanWrapper* pObj);

    bool IsHLCSLightsCutoffApplied(IdanWrapper* pObj);

    bool IsHLCSParkingLightApplied(IdanWrapper* pObj);

    bool IsHLCSKeySwitchApplied(IdanWrapper* pObj);

    bool IsHLCSMotorStarterApplied(IdanWrapper* pObj);

    bool IsHLCSHornApplied(IdanWrapper* pObj);

    bool IsHLCSLeftTurnSignalApplied(IdanWrapper* pObj);

    bool IsHLCSRightTurnSignalApplied(IdanWrapper* pObj);

    bool IsHLCSHazardsApplied(IdanWrapper* pObj);

    unsigned char GetHLCSGear(IdanWrapper* pObj);

    unsigned char GetHLCSParkingBrake(IdanWrapper* pObj);

    unsigned char GetHLCSEmergencyCmd(IdanWrapper* pObj);

    unsigned char GetHLCSSacsOnCmd(IdanWrapper* pObj);
}

#endif // IDANPLUGINAPI_H