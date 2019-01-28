#ifndef IDAN_DATA_H
#define IDAN_DATA_H

/*
* IdanData.h
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 20.03.18
*/

#include <string>

enum IdanMsgType {HLC_PRIMARY, HLC_SECONDARY, IDAN_PRIMARY, IDAN_SECONDARY_REPORT, IDAN_SECONDARY_SENSOR };

class IdanData {
private:
    IdanMsgType m_currMsgType;

    struct HLC_Primary {
        bool hasShutDownCmd = false;
        bool hasEmergencyCmd = false;
        float steerCmd = 0;
        float gasCmd = 0;
    } m_HLCPrimary;

    struct HLC_Secondary {
        bool hasShutDownCmd = false;
        bool roadLights = false;
        bool highBeam = false;
        bool lightsCutoff = false;
        bool parkingLight = false;
        bool keySwitch = false;
        bool motorStarter = false;
        bool horn = false;
        bool leftTurnSignal = false;
        bool rightTurnSignal = false;
        bool hazards = false;
		char gearChar;
        bool IsParkingBrakeReleased = false;
        bool hasEmergencyCmd = false;
        bool HasSacsOnCmd = false;
    } m_HLCSecondary;

    struct IDAN_Primary {
        float steerPose = 0;
        float gasPose = 0;
    } m_IDANPrimary;

	struct IDAN_SecondaryReport {
        bool roadLights = false;
        bool highBeam = false;
        bool lightsCutoff = false;
        bool keySwitch = false;
        bool motorStarter = false;
        bool horn = false;
        bool leftTurnSignal = false;
        bool rightTurnSignal = false;
        bool hazards = false;
		char requestedGearChar;
		char actualGearChar;
        std::string parkingBrake;
        float rpm = 0;
        float velocity = 0;
    } m_IDANSecondaryReport;

    struct IDAN_SecondarySensor {
        float engineTemp = 0;
        float oilPress = 0;
        float fuelLevel = 0;
        float alternatorVoltage = 0;
        float backupBattVoltage = 0;
        int batterySumUp = 0;
        float airPressFront = 0;
        float airPressRear = 0;
    } m_IDANSecondarySensor;


public:
    IdanData() = default;
    
    ~IdanData() = default;

    IdanMsgType GetCurrMsgType() const {
        return m_currMsgType;
    }

    void SetCurrMsgType(IdanMsgType msgType) {
        m_currMsgType = msgType;
    }

    /************************************************* HLC Primary ********************************************/

    bool HasHLCPShutDownCmd() const {
        return m_HLCPrimary.hasShutDownCmd;
    }

    void SetHLCPShutDownCmd(bool hasShutDownCmd) {
        m_HLCPrimary.hasShutDownCmd = hasShutDownCmd;
    }

    bool HasHLCPEmergencyCmd() const {
        return m_HLCPrimary.hasEmergencyCmd;
    }

    void SetHLCPEmergencyCmd(bool hasEmergencyCmd) {
        m_HLCPrimary.hasEmergencyCmd = hasEmergencyCmd;
    }

    float GetHLCPSteerCmd() const {
        return m_HLCPrimary.steerCmd;
    }

    void SetHLCPSteerCmd(float steerCmd) {
        m_HLCPrimary.steerCmd = steerCmd;
    }

    float GetHLCPGasCmd() const {
        return m_HLCPrimary.gasCmd;
    }

    void SetHLCPGasCmd(float gasCmd) {
        m_HLCPrimary.gasCmd = gasCmd;
    }

    /************************************************* HLC Secondary ********************************************/

    bool HasHLCSShutDownCmd() const {
        return m_HLCSecondary.hasShutDownCmd;
    }

    void SetHLCSShutDownCmd(bool hasShutDownCmd) {
        m_HLCSecondary.hasShutDownCmd = hasShutDownCmd;
    }

    bool IsHLCSRoadLightsApplied() const {
        return m_HLCSecondary.roadLights;
    }

    void SetHLCSRoadLights(bool roadLights) {
        m_HLCSecondary.roadLights = roadLights;
    }

    bool IsHLCSHighBeamApplied() const {
        return m_HLCSecondary.highBeam;
    }

    void SetHLCSHighBeam(bool highBeam) {
        m_HLCSecondary.highBeam = highBeam;
    }

    bool IsHLCSLightsCutoffApplied() const {
        return m_HLCSecondary.lightsCutoff;
    }

    void SetHLCSLightsCutoff(bool lightsCutoff) {
        m_HLCSecondary.lightsCutoff = lightsCutoff;
    }

    bool IsHLCSParkingLightApplied() const {
        return m_HLCSecondary.parkingLight;
    }

    void SetHLCSParkingLight(bool parkingLight) {
        m_HLCSecondary.parkingLight = parkingLight;
    }

    bool IsHLCSKeySwitchApplied() const {
        return m_HLCSecondary.keySwitch;
    }

    void SetHLCSKeySwitch(bool keySwitch) {
        m_HLCSecondary.keySwitch = keySwitch;
    }

    bool IsHLCSMotorStarterApplied() const {
        return m_HLCSecondary.motorStarter;
    }

    void SetHLCSMotorStarter(bool motorStarter) {
        m_HLCSecondary.motorStarter = motorStarter;
    }

    bool IsHLCSHornApplied() const {
        return m_HLCSecondary.horn;
    }

    void SetHLCSHorn(bool horn) {
        m_HLCSecondary.horn = horn;
    }

    bool IsHLCSLeftTurnSignalApplied() const {
        return m_HLCSecondary.leftTurnSignal;
    }

    void SetHLCSLeftTurnSignal(bool leftTurnSignal) {
        m_HLCSecondary.leftTurnSignal = leftTurnSignal;
    }

    bool IsHLCSRightTurnSignalApplied() const {
        return m_HLCSecondary.rightTurnSignal;
    }

    void SetHLCSRightTurnSignal(bool rightTurnSignal) {
        m_HLCSecondary.rightTurnSignal = rightTurnSignal;
    }

    bool IsHLCSHazardsApplied() const {
        return m_HLCSecondary.hazards;
    }

    void SetHLCSHazards(bool hazards) {
        m_HLCSecondary.hazards = hazards;
    }

    char GetHLCSGearChar() const {
        return m_HLCSecondary.gearChar;
    }

    void SetHLCSGearChar(const char gear) {
        m_HLCSecondary.gearChar = gear;
    }

    bool IsHLCSParkingBrakeReleased() const {
        return m_HLCSecondary.IsParkingBrakeReleased;
    }

    void SetHLCSParkingBrake(bool IsParkingBrakeReleased) {
        m_HLCSecondary.IsParkingBrakeReleased = IsParkingBrakeReleased;
    }

    bool HasHLCSEmergencyCmd() const {
        return m_HLCSecondary.hasEmergencyCmd;
    }

    void SetHLCSEmergencyCmd(bool hasEmergencyCmd) {
        m_HLCSecondary.hasEmergencyCmd = hasEmergencyCmd;
    }

    bool HasHLCSSacsOnCmd() const {
        return m_HLCSecondary.HasSacsOnCmd;
    }

    void SetHLCSSacsOnCmd(bool HasSacsOnCmd) {
        m_HLCSecondary.HasSacsOnCmd = HasSacsOnCmd;
    }

    /************************************************* IDAN Primary ********************************************/
    float GetIdanPrimSteerPos() const {
        return m_IDANPrimary.steerPose;
    }

    void SetIdanPrimSteerPos(float steerPose) {
        m_IDANPrimary.steerPose = steerPose;
    }

    float GetIdanPrimGasPos() const {
        return m_IDANPrimary.gasPose;
    }

    void SetIdanPrimGasPos(float gasPose) {
        m_IDANPrimary.gasPose = gasPose;
    }

    /************************************************* IDAN Secondary Report ********************************************/
	
    bool IsIdanSecRepRoadLightsApplied() const {
        return m_IDANSecondaryReport.roadLights;
    }

    void SetIdanSecRepRoadLights(bool roadLights) {
        m_IDANSecondaryReport.roadLights = roadLights;
    }

    bool IsIdanSecRepHighBeamApplied() const {
        return m_IDANSecondaryReport.highBeam;
    }

    void SetIdanSecRepHighBeam(bool highBeam) {
        m_IDANSecondaryReport.highBeam = highBeam;
    }

    bool IsIdanSecRepLightsCutoffApplied() const {
        return m_IDANSecondaryReport.lightsCutoff;
    }

    void SetIdanSecRepLightsCutoff(bool lightsCutoff) {
        m_IDANSecondaryReport.lightsCutoff = lightsCutoff;
    }

    bool IsIdanSecRepKeySwitchApplied() const {
        return m_IDANSecondaryReport.keySwitch;
    }

    void SetIdanSecRepKeySwitch(bool keySwitch) {
        m_IDANSecondaryReport.keySwitch = keySwitch;
    }

    bool IsIdanSecRepMotorStarterApplied() const {
        return m_IDANSecondaryReport.motorStarter;
    }

    void SetIdanSecRepMotorStarter(bool motorStarter) {
        m_IDANSecondaryReport.motorStarter = motorStarter;
    }

    bool IsIdanSecRepHornApplied() const {
        return m_IDANSecondaryReport.horn;
    }

    void SetIdanSecRepHorn(bool horn) {
        m_IDANSecondaryReport.horn = horn;
    }

    bool IsIdanSecRepLeftTurnSignalApplied() const {
        return m_IDANSecondaryReport.leftTurnSignal;
    }

    void SetIdanSecRepLeftTurnSignal(bool leftTurnSignal) {
        m_IDANSecondaryReport.leftTurnSignal = leftTurnSignal;
    }

    bool IsIdanSecRepRightTurnSignalApplied() const {
        return m_IDANSecondaryReport.rightTurnSignal;
    }

    void SetIdanSecRepRightTurnSignal(bool rightTurnSignal) {
        m_IDANSecondaryReport.rightTurnSignal = rightTurnSignal;
    }

    bool IsIdanSecRepHazardsApplied() const {
        return m_IDANSecondaryReport.hazards;
    }

    void SetIdanSecRepHazards(bool hazards) {
        m_IDANSecondaryReport.hazards = hazards;
    }

    char GetIdanSecRepRequestedGearChar() const {
        return m_IDANSecondaryReport.requestedGearChar;
    }

    void SetIdanSecRepRequestedGearChar(const char requestedGear) {
        m_IDANSecondaryReport.requestedGearChar = requestedGear;
    }

    char GetIdanSecRepActualGearChar() const {
        return m_IDANSecondaryReport.actualGearChar;
    }

    void SetIdanSecRepActualGearChar(const char actualGear) {
        m_IDANSecondaryReport.actualGearChar = actualGear;
    }

    std::string GetIdanSecRepParkingBrake() const {
        return m_IDANSecondaryReport.parkingBrake;
    }

    void SetIdanSecRepParkingBrake(const std::string& parkingBrake) {
        m_IDANSecondaryReport.parkingBrake = parkingBrake;
    }

    float GetIdanSecRepRpm() const {
        return m_IDANSecondaryReport.rpm;
    }

    void SetIdanSecRepRpm(float rpm) {
        m_IDANSecondaryReport.rpm = rpm;
    }

    float GetIdanSecRepVelocity() const {
        return m_IDANSecondaryReport.velocity;
    }

    void SetIdanSecRepVelocity(float velocity) {
        m_IDANSecondaryReport.velocity = velocity;
    }

    /************************************************* IDAN Secondary Sensor ********************************************/
    
    float GetIdanSecSenEngineTemp() const {
        return m_IDANSecondarySensor.engineTemp;
    }

    void SetIdanSecSenEngineTemp(float engineTemp) {
        m_IDANSecondarySensor.engineTemp = engineTemp;
    }

    float GetIdanSecSenOilPress() const {
        return m_IDANSecondarySensor.oilPress;
    }

    void SetIdanSecSenOilPress(float oilPress) {
        m_IDANSecondarySensor.oilPress = oilPress;
    }

    float GetIdanSecSenFuelLevel() const {
        return m_IDANSecondarySensor.fuelLevel;
    }

    void SetIdanSecSenFuelLevel(float fuelLevel) {
        m_IDANSecondarySensor.fuelLevel = fuelLevel;
    }

    float GetIdanSecSenAlternatorVoltage() const {
        return m_IDANSecondarySensor.alternatorVoltage;
    }

    void SetIdanSecSenAlternatorVoltage(float alternatorVoltage) {
        m_IDANSecondarySensor.alternatorVoltage = alternatorVoltage;
    }

    float GetIdanSecSenBackupBattVoltage() const {
        return m_IDANSecondarySensor.backupBattVoltage;
    }

    void SetIdanSecSenBackupBattVoltage(float backupBattVoltage) {
        m_IDANSecondarySensor.backupBattVoltage = backupBattVoltage;
    }

    int GetIdanSecSenBatterySumUp() const {
        return m_IDANSecondarySensor.batterySumUp;
    }

    void SetIdanSecSenBatterySumUp(int batterySumUp) {
        m_IDANSecondarySensor.batterySumUp = batterySumUp;
    }

    float GetIdanSecSenAirPressFront() const {
        return m_IDANSecondarySensor.airPressFront;
    }

    void SetIdanSecSenAirPressFront(float airPressFront) {
        m_IDANSecondarySensor.airPressFront = airPressFront;
    }

    float GetIdanSecSenAirPressRear() const {
        return m_IDANSecondarySensor.airPressRear;
    }

    void SetIdanSecSenAirPressRear(float airPressRear) {
        m_IDANSecondarySensor.airPressRear = airPressRear;
    }

    std::string toString(IdanMsgType msgType) const;
};



#endif // IDAN_DATA_H