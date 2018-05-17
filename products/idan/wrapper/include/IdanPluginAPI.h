#ifndef IDANPLUGINAPI_H
#define IDANPLUGINAPI_H

/*
* IdanPluginAPI.h
* API for external tools that need to use IDAN
* Author: Binyamin Appelbaum
* Date: 25.03.18
*/

struct IdanWrapper;

// Functions that can be used by the plugin
extern "C" {
    IdanWrapper* IdanCreateObject(const char* confFilePath);

    void IdanDeleteObject(IdanWrapper* pObj);

    void SendIdanPrimaryData(IdanWrapper* pObj);

    void SendIdanSecondaryReportData(IdanWrapper* pObj);

    void SendIdanSecondarySensorData(IdanWrapper* pObj);

    void IdanReceiveData(IdanWrapper* pObj);

    /********************************* HLC Primary *************************************************/
    bool HasHLCPShutDownCmd(IdanWrapper* pObj);

    bool HasHLCPEmergencyCmd(IdanWrapper* pObj);

    float GetHLCPSteerCmd(IdanWrapper* pObj);

    float GetHLCPGasCmd(IdanWrapper* pObj);

    /********************************* HLC Secondary *************************************************/
    bool HasHLCSShutDownCmd(IdanWrapper* pObj);
    
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

    const char* GetHLCSGear(IdanWrapper* pObj);

    bool IsHLCSParkingBrakeReleased(IdanWrapper* pObj);

    bool HasHLCSEmergencyCmd(IdanWrapper* pObj);

    bool HasHLCSSacsOnCmd(IdanWrapper* pObj);

   /************************************************* IDAN Primary ********************************************/
    void SetIdanPrimSteerPos(IdanWrapper* obj, float steerPose);

    void SetIdanPrimGasPos(IdanWrapper* obj, float gasPose);

    /************************************************* IDAN Secondary Report ********************************************/
	
    void SetIdanSecRepRoadLights(IdanWrapper* obj, bool roadLights); 

    void SetIdanSecRepHighBeam(IdanWrapper* obj, bool highBeam);

    void SetIdanSecRepLightsCutoff(IdanWrapper* obj, bool lightsCutoff) ;

    void SetIdanSecRepKeySwitch(IdanWrapper* obj, bool keySwitch);

    void SetIdanSecRepMotorStarter(IdanWrapper* obj, bool motorStarter);

    void SetIdanSecRepHorn(IdanWrapper* obj, bool horn);

    void SetIdanSecRepLeftTurnSignal(IdanWrapper* obj, bool leftTurnSignal);

    void SetIdanSecRepRightTurnSignal(IdanWrapper* obj, bool rightTurnSignal);

    void SetIdanSecRepHazards(IdanWrapper* obj, bool hazards);

    void SetIdanSecRepRequestedGear(IdanWrapper* obj, const char* requestedGear);

    void SetIdanSecRepActualGear(IdanWrapper* obj, const char* actualGear);

    void SetIdanSecRepParkingBrake(IdanWrapper* obj, const char* parkingBrake);

    void SetIdanSecRepRpm(IdanWrapper* obj, float rpm);

    void SetIdanSecRepVelocity(IdanWrapper* obj, float velocity);

    /************************************************* IDAN Secondary Sensor ********************************************/
    
    void SetIdanSecSenEngineTemp(IdanWrapper* obj, float engineTemp);

    void SetIdanSecSenOilPress(IdanWrapper* obj, float oilPress);

    void SetIdanSecSenFuelLevel(IdanWrapper* obj, float fuelLevel);

    void SetIdanSecSenAlternatorVoltage(IdanWrapper* obj, float alternatorVoltage);

    void SetIdanSecSenBackupBattVoltage(IdanWrapper* obj, float backupBattVoltage);

    void SetIdanSecSenBatterySumUp(IdanWrapper* obj, int batterySumUp);

    void SetIdanSecSenAirPressFront(IdanWrapper* obj, float airPressFront);

    void SetIdanSecSenAirPressRear(IdanWrapper* obj, float airPressRear);
}

#endif // IDANPLUGINAPI_H