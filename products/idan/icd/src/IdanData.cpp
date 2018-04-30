/*
* IdanData.cpp
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 20.03.18
* 
*/

#include "IdanData.h"
#include <sstream>

std::string IdanData::toString(const std::bitset<8>& message) const {
    std::stringstream ss;

    if ((message & HLC_PRIM).any()) {
        ss << std::endl << "***** HLC Primary *****" << std::endl <<
            "hasShutDownCmd: " << m_HLCPrimary.hasShutDownCmd << ", hasEmergencyCmd: " << m_HLCPrimary.hasEmergencyCmd << 
            ", steerCmd: " << m_HLCPrimary.steerCmd << ", gasCmd: " << m_HLCPrimary.gasCmd << std::endl;
    }

    if ((message & HLC_SEC).any()) {
        ss << "***** HLC Secondary *****" << std::endl << 
            "hasShutDownCmd: " << m_HLCSecondary.hasShutDownCmd << ", roadLights: " << m_HLCSecondary.roadLights << 
            ", highBeam: " << m_HLCSecondary.highBeam << ", lightsCutoff: " << m_HLCSecondary.lightsCutoff << 
            ", parkingLight: " << m_HLCSecondary.parkingLight << ", keySwitch: " << m_HLCSecondary.keySwitch << 
            ", motorStarter: " << m_HLCSecondary.motorStarter << ", horn: " << m_HLCSecondary.horn <<
            ", leftTurnSignal: " << m_HLCSecondary.leftTurnSignal << ", rightTurnSignal: " << m_HLCSecondary.rightTurnSignal << 
            ", hazards: " << m_HLCSecondary.hazards << ", gear: " << m_HLCSecondary.gear << 
            ", IsParkingBrakeReleased: " << m_HLCSecondary.IsParkingBrakeReleased << ", hasEmergencyCmd: " << m_HLCSecondary.hasEmergencyCmd << 
            ", HasSacsOnCmd: " << m_HLCSecondary.HasSacsOnCmd << std::endl;
    }

    if ((message & IDAN_PRIM).any()) {
        ss << "***** IDAN Primary *****" << std::endl << 
        "steerPose: " << m_IDANPrimary.steerPose << ", gasPose: " << m_IDANPrimary.gasPose << std::endl;
    }

    if ((message & IDAN_SEC_REP).any()) {
        ss << "***** IDAN Secondary Report *****" << std::endl << 
            "roadLights: " << m_IDANSecondaryReport.roadLights << ", highBeam: " << m_IDANSecondaryReport.highBeam << 
            ", lightsCutoff: " << m_IDANSecondaryReport.lightsCutoff << ", keySwitch: " << m_IDANSecondaryReport.keySwitch << 
            ", horn: " << m_IDANSecondaryReport.horn << ", leftTurnSignal: " << m_IDANSecondaryReport.leftTurnSignal << 
            ", rightTurnSignal: " << m_IDANSecondaryReport.rightTurnSignal << ", hazards: " << m_IDANSecondaryReport.hazards <<
            ", requestedGear: " << m_IDANSecondaryReport.requestedGear << ", actualGear: " << m_IDANSecondaryReport.actualGear << 
            ", parkingBrake: " << m_IDANSecondaryReport.parkingBrake << ", rpm: " << m_IDANSecondaryReport.rpm <<
            ", velocity: " << m_IDANSecondaryReport.velocity << std::endl;
    }


    if ((message & IDAN_SEC_SEN).any()) {
        ss << "***** IDAN Secondary Sensor *****" << std::endl << 
            ", engineTemp: " << m_IDANSecondarySensor.engineTemp << ", oilPress: " << m_IDANSecondarySensor.oilPress << 
            ", fuelLevel: " << m_IDANSecondarySensor.fuelLevel << ", alternatorVoltage: " << m_IDANSecondarySensor.alternatorVoltage <<
            ", backupBattVoltage: " << m_IDANSecondarySensor.backupBattVoltage << ", batterySumUp: " << m_IDANSecondarySensor.batterySumUp << 
            ", airPressFront: " << m_IDANSecondarySensor.airPressFront << ", airPressRear: " << m_IDANSecondarySensor.airPressRear << std::endl;
    }
    
    return ss.str();
}