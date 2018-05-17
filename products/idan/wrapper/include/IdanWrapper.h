#ifndef IDANWRAPPER_H
#define IDANWRAPPER_H

/*
* IdanWrapper.h
* Wrapper for Idan
* Author: Binyamin Appelbaum
* Date: 25.03.18
*/

#include "IdanData.h"
#include "IWrapper.h"

/**

 * */
class IdanWrapper : public IWrapper<IdanData> {
private:
    IdanData m_data;
    /**
     * Clear current data of the object
     */ 
    void ClearCurrentData();

public:
    IdanWrapper(const std::string& confFilePath);

    ~IdanWrapper();

    virtual void SendData() override;

    virtual void ReceiveData() override;

    void SetMsgType(IdanMsgType msgType);

    /********************************* HLC Primary *************************************************/
    bool HasHLCPShutDownCmd() const;

    bool HasHLCPEmergencyCmd() const;

    float GetHLCPSteerCmd() const;

    float GetHLCPGasCmd() const;

    /********************************* HLC Secondary *************************************************/
    bool HasHLCSShutDownCmd() const;
    
    bool IsHLCSRoadLightsApplied() const;

    bool IsHLCSHighBeamApplied() const;

    bool IsHLCSLightsCutoffApplied() const;

    bool IsHLCSParkingLightApplied() const;

    bool IsHLCSKeySwitchApplied() const;

    bool IsHLCSMotorStarterApplied() const;

    bool IsHLCSHornApplied() const;

    bool IsHLCSLeftTurnSignalApplied() const;

    bool IsHLCSRightTurnSignalApplied() const;

    bool IsHLCSHazardsApplied() const;

    std::string GetHLCSGear() const;

    bool IsHLCSParkingBrakeReleased() const;

    bool HasHLCSEmergencyCmd() const;

    bool HasHLCSSacsOnCmd() const;

    /************************************************* IDAN Primary ********************************************/
    void SetIdanPrimSteerPos(float steerPose);

    void SetIdanPrimGasPos(float gasPose);

    /************************************************* IDAN Secondary Report ********************************************/
	
    void SetIdanSecRepRoadLights(bool roadLights); 

    void SetIdanSecRepHighBeam(bool highBeam);

    void SetIdanSecRepLightsCutoff(bool lightsCutoff) ;

    void SetIdanSecRepKeySwitch(bool keySwitch);

    void SetIdanSecRepMotorStarter(bool motorStarter);

    void SetIdanSecRepHorn(bool horn);

    void SetIdanSecRepLeftTurnSignal(bool leftTurnSignal);

    void SetIdanSecRepRightTurnSignal(bool rightTurnSignal);

    void SetIdanSecRepHazards(bool hazards);

    void SetIdanSecRepRequestedGear(const std::string& requestedGear);

    void SetIdanSecRepActualGear(const std::string& actualGear);

    void SetIdanSecRepParkingBrake(const std::string& parkingBrake);

    void SetIdanSecRepRpm(float rpm);

    void SetIdanSecRepVelocity(float velocity);

    /************************************************* IDAN Secondary Sensor ********************************************/
    
    void SetIdanSecSenEngineTemp(float engineTemp);

    void SetIdanSecSenOilPress(float oilPress);

    void SetIdanSecSenFuelLevel(float fuelLevel);

    void SetIdanSecSenAlternatorVoltage(float alternatorVoltage);

    void SetIdanSecSenBackupBattVoltage(float backupBattVoltage);

    void SetIdanSecSenBatterySumUp(int batterySumUp);

    void SetIdanSecSenAirPressFront(float airPressFront);

    void SetIdanSecSenAirPressRear(float airPressRear);

};

#endif // IDANWRAPPER_H