/*
* IdanPluginAPI.h
* API for external tools that need to use IDAN
* Author: Binyamin Appelbaum
* Date: 25.03.18
*/

#include "IdanPluginAPI.h"
#include "IdanWrapper.h"
#include "string.h" // strdup

IdanWrapper* IdanCreateObject(const char* confFilePath) {
    return new IdanWrapper(confFilePath);
}

void IdanDeleteObject(IdanWrapper* pObj) {
    delete pObj;
}

void IdanInitCommunication(IdanWrapper* pObj) {
    pObj->InitCommunication();
}

void SendIdanPrimaryData(IdanWrapper* pObj) {
    pObj->SetMsgType(IDAN_PRIMARY);
    pObj->SendData();
}

void SendIdanSecondaryReportData(IdanWrapper* pObj) {
    pObj->SetMsgType(IDAN_SECONDARY_REPORT);
    pObj->SendData();
}

void SendIdanSecondarySensorData(IdanWrapper* pObj) {
    pObj->SetMsgType(IDAN_SECONDARY_SENSOR);
    pObj->SendData();
}

void IdanReceiveData(IdanWrapper* pObj) {
    pObj->ReceiveData();
}

/********************************* HLC Primary *************************************************/
bool HasHLCPShutDownCmd(IdanWrapper* pObj) {
    return pObj->HasHLCPShutDownCmd();
}

bool HasHLCPEmergencyCmd(IdanWrapper* pObj){
    return pObj->HasHLCPEmergencyCmd();
}

float GetHLCPSteerCmd(IdanWrapper* pObj){
    return pObj->GetHLCPSteerCmd();
}

float GetHLCPGasCmd(IdanWrapper* pObj){
    return pObj->GetHLCPGasCmd();
}

/********************************* HLC Secondary *************************************************/
bool HasHLCSShutDownCmd(IdanWrapper* pObj){
    return pObj->HasHLCSShutDownCmd();
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

const char* GetHLCSGear(IdanWrapper* pObj){
    return strdup(pObj->GetHLCSGear().c_str());
}

bool IsHLCSParkingBrakeReleased(IdanWrapper* pObj){
    return pObj->IsHLCSParkingBrakeReleased();
}

bool HasHLCSEmergencyCmd(IdanWrapper* pObj){
    return pObj->HasHLCSEmergencyCmd();
}

bool HasHLCSSacsOnCmd(IdanWrapper* pObj){
    return pObj->HasHLCSSacsOnCmd();
}

/************************************************* IDAN Primary ********************************************/
void SetIdanPrimSteerPos(IdanWrapper* pObj, float steerPose) {
    pObj->SetIdanPrimSteerPos(steerPose);
}

void SetIdanPrimGasPos(IdanWrapper* pObj, float gasPose) {
    pObj->SetIdanPrimGasPos(gasPose);
}

/************************************************* IDAN Secondary Report ********************************************/

void SetIdanSecRepRoadLights(IdanWrapper* pObj, bool roadLights) {
    pObj->SetIdanSecRepRoadLights(roadLights);
}

void SetIdanSecRepHighBeam(IdanWrapper* pObj, bool highBeam) {
    pObj->SetIdanSecRepHighBeam(highBeam);
}

void SetIdanSecRepLightsCutoff(IdanWrapper* pObj, bool lightsCutoff)  {
    pObj->SetIdanSecRepLightsCutoff(lightsCutoff);
}

void SetIdanSecRepKeySwitch(IdanWrapper* pObj, bool keySwitch) {
    pObj->SetIdanSecRepKeySwitch(keySwitch);
}

void SetIdanSecRepMotorStarter(IdanWrapper* pObj, bool motorStarter) {
    pObj->SetIdanSecRepMotorStarter(motorStarter);
}

void SetIdanSecRepHorn(IdanWrapper* pObj, bool horn) {
    pObj->SetIdanSecRepHorn(horn);
}

void SetIdanSecRepLeftTurnSignal(IdanWrapper* pObj, bool leftTurnSignal) {
    pObj->SetIdanSecRepLeftTurnSignal(leftTurnSignal);
}

void SetIdanSecRepRightTurnSignal(IdanWrapper* pObj, bool rightTurnSignal) {
    pObj->SetIdanSecRepRightTurnSignal(rightTurnSignal);
}

void SetIdanSecRepHazards(IdanWrapper* pObj, bool hazards) {
    pObj->SetIdanSecRepHazards(hazards);
}

void SetIdanSecRepRequestedGear(IdanWrapper* pObj, const char* requestedGear) {
    pObj->SetIdanSecRepRequestedGear(requestedGear);
}

void SetIdanSecRepActualGear(IdanWrapper* pObj, const char* actualGear) {
    pObj->SetIdanSecRepActualGear(actualGear);
}

void SetIdanSecRepParkingBrake(IdanWrapper* pObj, const char* parkingBrake) {
    pObj->SetIdanSecRepParkingBrake(parkingBrake);
}

void SetIdanSecRepRpm(IdanWrapper* pObj, float rpm) {
    pObj->SetIdanSecRepRpm(rpm);
}

void SetIdanSecRepVelocity(IdanWrapper* pObj, float velocity) {
    pObj->SetIdanSecRepVelocity(velocity);
}

/************************************************* IDAN Secondary Sensor ********************************************/

void SetIdanSecSenEngineTemp(IdanWrapper* pObj, float engineTemp) {
    pObj->SetIdanSecSenEngineTemp(engineTemp);
}

void SetIdanSecSenOilPress(IdanWrapper* pObj, float oilPress) {
    pObj->SetIdanSecSenOilPress(oilPress);
}

void SetIdanSecSenFuelLevel(IdanWrapper* pObj, float fuelLevel) {
    pObj->SetIdanSecSenFuelLevel(fuelLevel);
}

void SetIdanSecSenAlternatorVoltage(IdanWrapper* pObj, float alternatorVoltage) {
    pObj->SetIdanSecSenAlternatorVoltage(alternatorVoltage);
}

void SetIdanSecSenBackupBattVoltage(IdanWrapper* pObj, float backupBattVoltage) {
    pObj->SetIdanSecSenBackupBattVoltage(backupBattVoltage);
}

void SetIdanSecSenBatterySumUp(IdanWrapper* pObj, int batterySumUp) {
    pObj->SetIdanSecSenBatterySumUp(batterySumUp);
}

void SetIdanSecSenAirPressFront(IdanWrapper* pObj, float airPressFront) {
    pObj->SetIdanSecSenAirPressFront(airPressFront);
}

void SetIdanSecSenAirPressRear(IdanWrapper* pObj, float airPressRear) {
    pObj->SetIdanSecSenAirPressRear(airPressRear);
}