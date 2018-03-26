/*
* IdanPluginAPI.h
* API for external tools that need to use IDAN
* Author: Binyamin Appelbaum
* Date: 25.03.18
*/

#include "IdanPluginAPI.h"

IdanWrapper* CreateIdanObject(const char* confFilePath) {
    return new IdanWrapper(confFilePath);
}

void DeleteIdanObject(IdanWrapper* pObj) {delete pObj;}

void RunIdan(IdanWrapper* pObj) { pObj->Run(); }

void GetIdanData(IdanWrapper* pObj) {
    pObj->GetData();
}

/********************************* HLC Primary *************************************************/
unsigned char GetHLCPShutDownCmd(IdanWrapper* pObj) {
    return pObj->GetHLCPShutDownCmd();
}

unsigned char GetHLCPEmergencyCmd(IdanWrapper* pObj){
    return pObj->GetHLCPEmergencyCmd();
}

unsigned char GetHLCPSteerCmdMsb(IdanWrapper* pObj){
    return pObj->GetHLCPSteerCmdMsb();
}

unsigned char GetHLCPSteerCmdLsb(IdanWrapper* pObj){
    return pObj->GetHLCPSteerCmdLsb();
}

unsigned char GetHLCPGasCmdMsb(IdanWrapper* pObj){
    return pObj->GetHLCPGasCmdMsb();
}

unsigned char GetHLCPGasCmdLsb(IdanWrapper* pObj){
    return pObj->GetHLCPGasCmdLsb();
}

/********************************* HLC Secondary *************************************************/
unsigned char GetHLCSShutDownCmd(IdanWrapper* pObj){
    return pObj->GetHLCSShutDownCmd();
}

bool IsHLCSRoadLightsApplied(IdanWrapper* pObj){
    return pObj->IsHLCSRoadLightsApplied();
}

bool IsHLCSHighBeamApplied(IdanWrapper* pObj){
    return pObj->IsHLCSHighBeamApplied();
}

bool IsHLCSLightsCutoffApplied(IdanWrapper* pObj){
    return pObj->IsHLCSLightsCutoffApplied();
}

bool IsHLCSParkingLightApplied(IdanWrapper* pObj){
    return pObj->IsHLCSParkingLightApplied();
}

bool IsHLCSKeySwitchApplied(IdanWrapper* pObj){
    return pObj->IsHLCSKeySwitchApplied();
}

bool IsHLCSMotorStarterApplied(IdanWrapper* pObj){
    return pObj->IsHLCSMotorStarterApplied();
}

bool IsHLCSHornApplied(IdanWrapper* pObj){
    return pObj->IsHLCSHornApplied();
}

bool IsHLCSLeftTurnSignalApplied(IdanWrapper* pObj){
    return pObj->IsHLCSLeftTurnSignalApplied();
}

bool IsHLCSRightTurnSignalApplied(IdanWrapper* pObj){
    return pObj->IsHLCSRightTurnSignalApplied();
}

bool IsHLCSHazardsApplied(IdanWrapper* pObj){
    return pObj->IsHLCSHazardsApplied();
}

unsigned char GetHLCSGear(IdanWrapper* pObj){
    return pObj->GetHLCSGear();
}

unsigned char GetHLCSParkingBrake(IdanWrapper* pObj){
    return pObj->GetHLCSParkingBrake();
}

unsigned char GetHLCSEmergencyCmd(IdanWrapper* pObj){
    return pObj->GetHLCSEmergencyCmd();
}

unsigned char GetHLCSSacsOnCmd(IdanWrapper* pObj){
    return pObj->GetHLCSSacsOnCmd();
}