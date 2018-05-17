/*
* IdanWrapper.cpp
* Wrapper for Idan
* Author: Binyamin Appelbaum
* Date: 25.03.18
*/

#include "IdanWrapper.h"
#include "IdanControl.h"


IdanWrapper::IdanWrapper(const std::string& confFilePath) {
    m_icd = new IdanControl(confFilePath);
}

IdanWrapper::~IdanWrapper(){
    delete m_icd;
}

void IdanWrapper::ReceiveData() {
    m_data = m_icd->ReceiveData();
}

void IdanWrapper::SendData() {
    m_icd->SendData(m_data);
}

void IdanWrapper::SetMsgType(IdanMsgType msgType) {
    m_data.SetCurrMsgType(msgType);
}

void IdanWrapper::IdanWrapper::ClearCurrentData() {
    m_data = IdanData();
}

/********************************* HLC Primary *************************************************/
bool IdanWrapper::HasHLCPShutDownCmd() const {
    return m_data.HasHLCPShutDownCmd();
}

bool IdanWrapper::HasHLCPEmergencyCmd() const {
    return m_data.HasHLCPEmergencyCmd();
}

float IdanWrapper::GetHLCPSteerCmd() const {
    return m_data.GetHLCPSteerCmd();
}

float IdanWrapper::GetHLCPGasCmd() const {
    return m_data.GetHLCPGasCmd();
}

/********************************* HLC Secondary *************************************************/
bool IdanWrapper::HasHLCSShutDownCmd() const {
    return m_data.HasHLCSShutDownCmd();
}

bool IdanWrapper::IsHLCSRoadLightsApplied() const {
    return m_data.IsHLCSRoadLightsApplied();
}

bool IdanWrapper::IsHLCSHighBeamApplied() const {
    return m_data.IsHLCSHighBeamApplied();
}

bool IdanWrapper::IsHLCSLightsCutoffApplied() const {
    return m_data.IsHLCSLightsCutoffApplied();
}

bool IdanWrapper::IsHLCSParkingLightApplied() const {
    return m_data.IsHLCSParkingLightApplied();
}

bool IdanWrapper::IsHLCSKeySwitchApplied() const {
    return m_data.IsHLCSKeySwitchApplied();
}

bool IdanWrapper::IsHLCSMotorStarterApplied() const {
    return m_data.IsHLCSMotorStarterApplied();
}

bool IdanWrapper::IsHLCSHornApplied() const {
    return m_data.IsHLCSHornApplied();
}

bool IdanWrapper::IsHLCSLeftTurnSignalApplied() const {
    return m_data.IsHLCSLeftTurnSignalApplied();
}

bool IdanWrapper::IsHLCSRightTurnSignalApplied() const {
    return m_data.IsHLCSRightTurnSignalApplied();
}

bool IdanWrapper::IsHLCSHazardsApplied() const {
    return m_data.IsHLCSHazardsApplied();
}

std::string IdanWrapper::GetHLCSGear() const {
    return m_data.GetHLCSGear();
}

bool IdanWrapper::IsHLCSParkingBrakeReleased() const {
    return m_data.IsHLCSParkingBrakeReleased();
}

bool IdanWrapper::HasHLCSEmergencyCmd() const {
    return m_data.HasHLCSEmergencyCmd();
}

bool IdanWrapper::HasHLCSSacsOnCmd() const {
    return m_data.HasHLCSSacsOnCmd();
}

/************************************************* IDAN Primary ********************************************/
void IdanWrapper::SetIdanPrimSteerPos(float steerPose) {
    m_data.SetIdanPrimSteerPos(steerPose);
}

void IdanWrapper::SetIdanPrimGasPos(float gasPose) {
    m_data.SetIdanPrimGasPos(gasPose);
}

/************************************************* IDAN Secondary Report ********************************************/

void IdanWrapper::SetIdanSecRepRoadLights(bool roadLights) {
    m_data.SetIdanSecRepRoadLights(roadLights);
} 

void IdanWrapper::SetIdanSecRepHighBeam(bool highBeam) {
    m_data.SetIdanSecRepHighBeam(highBeam);
} 

void IdanWrapper::SetIdanSecRepLightsCutoff(bool lightsCutoff) {
    m_data.SetIdanSecRepLightsCutoff(lightsCutoff);
} 

void IdanWrapper::SetIdanSecRepKeySwitch(bool keySwitch) {
    m_data.SetIdanSecRepKeySwitch(keySwitch);
} 

void IdanWrapper::SetIdanSecRepMotorStarter(bool motorStarter) {
    m_data.SetIdanSecRepMotorStarter(motorStarter);
}

void IdanWrapper::SetIdanSecRepHorn(bool horn) {
    m_data.SetIdanSecRepHorn(horn);
} 

void IdanWrapper::SetIdanSecRepLeftTurnSignal(bool leftTurnSignal) {
    m_data.SetIdanSecRepLeftTurnSignal(leftTurnSignal);
} 

void IdanWrapper::SetIdanSecRepRightTurnSignal(bool rightTurnSignal) {
    m_data.SetIdanSecRepRightTurnSignal(rightTurnSignal);
} 

void IdanWrapper::SetIdanSecRepHazards(bool hazards) {
    m_data.SetIdanSecRepHazards(hazards);
} 

void IdanWrapper::SetIdanSecRepRequestedGear(const std::string& requestedGear) {
    m_data.SetIdanSecRepRequestedGear(requestedGear);
} 

void IdanWrapper::SetIdanSecRepActualGear(const std::string& actualGear) {
    m_data.SetIdanSecRepActualGear(actualGear);
} 

void IdanWrapper::SetIdanSecRepParkingBrake(const std::string& parkingBrake) {
    m_data.SetIdanSecRepParkingBrake(parkingBrake);
} 

void IdanWrapper::SetIdanSecRepRpm(float rpm) {
    m_data.SetIdanSecRepRpm(rpm);
} 

void IdanWrapper::SetIdanSecRepVelocity(float velocity) {
    m_data.SetIdanSecRepVelocity(velocity);
} 

/************************************************* IDAN Secondary Sensor ********************************************/

void IdanWrapper::SetIdanSecSenEngineTemp(float engineTemp) {
    m_data.SetIdanSecSenEngineTemp(engineTemp);
} 

void IdanWrapper::SetIdanSecSenOilPress(float oilPress) {
    m_data.SetIdanSecSenOilPress(oilPress);
} 

void IdanWrapper::SetIdanSecSenFuelLevel(float fuelLevel) {
    m_data.SetIdanSecSenFuelLevel(fuelLevel);
} 

void IdanWrapper::SetIdanSecSenAlternatorVoltage(float alternatorVoltage) {
    m_data.SetIdanSecSenAlternatorVoltage(alternatorVoltage);
} 

void IdanWrapper::SetIdanSecSenBackupBattVoltage(float backupBattVoltage) {
    m_data.SetIdanSecSenBackupBattVoltage(backupBattVoltage);
} 

void IdanWrapper::SetIdanSecSenBatterySumUp(int batterySumUp) {
    m_data.SetIdanSecSenBatterySumUp(batterySumUp);
} 

void IdanWrapper::SetIdanSecSenAirPressFront(float airPressFront) {
    m_data.SetIdanSecSenAirPressFront(airPressFront);
} 

void IdanWrapper::SetIdanSecSenAirPressRear(float airPressRear) {
    m_data.SetIdanSecSenAirPressRear(airPressRear);
} 