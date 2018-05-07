/*
* IdanPluginAPI.h
* API for external tools that need to use IDAN
* Author: Binyamin Appelbaum
* Date: 25.03.18
*/

#include "IdanPluginAPI.h"
#include "string.h" // strdup

IdanWrapper* CreateIdanObject(const char* confFilePath) {
    return new IdanWrapper(confFilePath);
}

void DeleteIdanObject(IdanWrapper* obj) {delete obj;}

void RunIdan(IdanWrapper* obj) { obj->Run(); }

void SendIdanData(IdanWrapper* obj) { obj->SetData(); }

void GetIdanData(IdanWrapper* obj) {
    obj->GetData();
}

/********************************* HLC Primary *************************************************/
bool HasHLCPShutDownCmd(IdanWrapper* obj) {
    return obj->HasHLCPShutDownCmd();
}

bool HasHLCPEmergencyCmd(IdanWrapper* obj){
    return obj->HasHLCPEmergencyCmd();
}

float GetHLCPSteerCmd(IdanWrapper* obj){
    return obj->GetHLCPSteerCmd();
}

float GetHLCPGasCmd(IdanWrapper* obj){
    return obj->GetHLCPGasCmd();
}

/********************************* HLC Secondary *************************************************/
bool HasHLCSShutDownCmd(IdanWrapper* obj){
    return obj->HasHLCSShutDownCmd();
}

bool IsHLCSRoadLightsApplied(IdanWrapper* obj){
    return obj->IsHLCSRoadLightsApplied();
}

bool IsHLCSHighBeamApplied(IdanWrapper* obj){
    return obj->IsHLCSHighBeamApplied();
}

bool IsHLCSLightsCutoffApplied(IdanWrapper* obj){
    return obj->IsHLCSLightsCutoffApplied();
}

bool IsHLCSParkingLightApplied(IdanWrapper* obj){
    return obj->IsHLCSParkingLightApplied();
}

bool IsHLCSKeySwitchApplied(IdanWrapper* obj){
    return obj->IsHLCSKeySwitchApplied();
}

bool IsHLCSMotorStarterApplied(IdanWrapper* obj){
    return obj->IsHLCSMotorStarterApplied();
}

bool IsHLCSHornApplied(IdanWrapper* obj){
    return obj->IsHLCSHornApplied();
}

bool IsHLCSLeftTurnSignalApplied(IdanWrapper* obj){
    return obj->IsHLCSLeftTurnSignalApplied();
}

bool IsHLCSRightTurnSignalApplied(IdanWrapper* obj){
    return obj->IsHLCSRightTurnSignalApplied();
}

bool IsHLCSHazardsApplied(IdanWrapper* obj){
    return obj->IsHLCSHazardsApplied();
}

const char* GetHLCSGear(IdanWrapper* obj){
    return strdup(obj->GetHLCSGear().c_str());
}

bool IsHLCSParkingBrakeReleased(IdanWrapper* obj){
    return obj->IsHLCSParkingBrakeReleased();
}

bool HasHLCSEmergencyCmd(IdanWrapper* obj){
    return obj->HasHLCSEmergencyCmd();
}

bool HasHLCSSacsOnCmd(IdanWrapper* obj){
    return obj->HasHLCSSacsOnCmd();
}

/************************************************* IDAN Primary ********************************************/
void SetIdanPrimSteerPos(IdanWrapper* obj, float steerPose) {
    obj->SetIdanPrimSteerPos(steerPose);
}

void SetIdanPrimGasPos(IdanWrapper* obj, float gasPose) {
    obj->SetIdanPrimGasPos(gasPose);
}

/************************************************* IDAN Secondary Report ********************************************/

void SetIdanSecRepRoadLights(IdanWrapper* obj, bool roadLights) {
    obj->SetIdanSecRepRoadLights(roadLights);
}

void SetIdanSecRepHighBeam(IdanWrapper* obj, bool highBeam) {
    obj->SetIdanSecRepHighBeam(highBeam);
}

void SetIdanSecRepLightsCutoff(IdanWrapper* obj, bool lightsCutoff)  {
    obj->SetIdanSecRepLightsCutoff(lightsCutoff);
}

void SetIdanSecRepKeySwitch(IdanWrapper* obj, bool keySwitch) {
    obj->SetIdanSecRepKeySwitch(keySwitch);
}

void SetIdanSecRepMotorStarter(IdanWrapper* obj, bool motorStarter) {
    obj->SetIdanSecRepMotorStarter(motorStarter);
}

void SetIdanSecRepHorn(IdanWrapper* obj, bool horn) {
    obj->SetIdanSecRepHorn(horn);
}

void SetIdanSecRepLeftTurnSignal(IdanWrapper* obj, bool leftTurnSignal) {
    obj->SetIdanSecRepLeftTurnSignal(leftTurnSignal);
}

void SetIdanSecRepRightTurnSignal(IdanWrapper* obj, bool rightTurnSignal) {
    obj->SetIdanSecRepRightTurnSignal(rightTurnSignal);
}

void SetIdanSecRepHazards(IdanWrapper* obj, bool hazards) {
    obj->SetIdanSecRepHazards(hazards);
}

void SetIdanSecRepRequestedGear(IdanWrapper* obj, const char* requestedGear) {
    obj->SetIdanSecRepRequestedGear(requestedGear);
}

void SetIdanSecRepActualGear(IdanWrapper* obj, const char* actualGear) {
    obj->SetIdanSecRepActualGear(actualGear);
}

void SetIdanSecRepParkingBrake(IdanWrapper* obj, const char* parkingBrake) {
    obj->SetIdanSecRepParkingBrake(parkingBrake);
}

void SetIdanSecRepRpm(IdanWrapper* obj, float rpm) {
    obj->SetIdanSecRepRpm(rpm);
}

void SetIdanSecRepVelocity(IdanWrapper* obj, float velocity) {
    obj->SetIdanSecRepVelocity(velocity);
}

/************************************************* IDAN Secondary Sensor ********************************************/

void SetIdanSecSenEngineTemp(IdanWrapper* obj, float engineTemp) {
    obj->SetIdanSecSenEngineTemp(engineTemp);
}

void SetIdanSecSenOilPress(IdanWrapper* obj, float oilPress) {
    obj->SetIdanSecSenOilPress(oilPress);
}

void SetIdanSecSenFuelLevel(IdanWrapper* obj, float fuelLevel) {
    obj->SetIdanSecSenFuelLevel(fuelLevel);
}

void SetIdanSecSenAlternatorVoltage(IdanWrapper* obj, float alternatorVoltage) {
    obj->SetIdanSecSenAlternatorVoltage(alternatorVoltage);
}

void SetIdanSecSenBackupBattVoltage(IdanWrapper* obj, float backupBattVoltage) {
    obj->SetIdanSecSenBackupBattVoltage(backupBattVoltage);
}

void SetIdanSecSenBatterySumUp(IdanWrapper* obj, int batterySumUp) {
    obj->SetIdanSecSenBatterySumUp(batterySumUp);
}

void SetIdanSecSenAirPressFront(IdanWrapper* obj, float airPressFront) {
    obj->SetIdanSecSenAirPressFront(airPressFront);
}

void SetIdanSecSenAirPressRear(IdanWrapper* obj, float airPressRear) {
    obj->SetIdanSecSenAirPressRear(airPressRear);
}