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

void IdanWrapper::Run() {
    m_icd->Run();
}

void IdanWrapper::GetData() {
    m_data = m_icd->GetData();
}

void IdanWrapper::ClearCurrentData() {
    m_data = IdanData();
}

/********************************* HLC Primary *************************************************/
unsigned char IdanWrapper::GetHLCPShutDownCmd() const {
    return m_data.GetHLCPShutDownCmd();
}

unsigned char IdanWrapper::GetHLCPEmergencyCmd() const {
    return m_data.GetHLCPEmergencyCmd();
}

unsigned char IdanWrapper::GetHLCPSteerCmdMsb() const {
    return m_data.GetHLCPSteerCmdMsb();
}

unsigned char IdanWrapper::GetHLCPSteerCmdLsb() const {
    return m_data.GetHLCPSteerCmdLsb();
}

unsigned char IdanWrapper::GetHLCPGasCmdMsb() const {
    return m_data.GetHLCPGasCmdMsb();
}

unsigned char IdanWrapper::GetHLCPGasCmdLsb() const {
    return m_data.GetHLCPGasCmdLsb();
}

/********************************* HLC Secondary *************************************************/
unsigned char IdanWrapper::GetHLCSShutDownCmd() const {
    return m_data.GetHLCSShutDownCmd();
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

unsigned char IdanWrapper::GetHLCSGear() const {
    return m_data.GetHLCSGear();
}

unsigned char IdanWrapper::GetHLCSParkingBrake() const {
    return m_data.GetHLCSParkingBrake();
}

unsigned char IdanWrapper::GetHLCSEmergencyCmd() const {
    return m_data.GetHLCSEmergencyCmd();
}

unsigned char IdanWrapper::GetHLCSSacsOnCmd() const {
    return m_data.GetHLCSSacsOnCmd();
}