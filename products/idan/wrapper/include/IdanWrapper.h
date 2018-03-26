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

    virtual void Run() override;

    virtual void SetData() override {}

    virtual void GetData() override;

    /********************************* HLC Primary *************************************************/
    unsigned char GetHLCPShutDownCmd() const;

    unsigned char GetHLCPEmergencyCmd() const;

    unsigned char GetHLCPSteerCmdMsb() const;

    unsigned char GetHLCPSteerCmdLsb() const;

    unsigned char GetHLCPGasCmdMsb() const;

    unsigned char GetHLCPGasCmdLsb() const;

    /********************************* HLC Secondary *************************************************/
    unsigned char GetHLCSShutDownCmd() const;
    
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

    unsigned char GetHLCSGear() const;

    unsigned char GetHLCSParkingBrake() const;

    unsigned char GetHLCSEmergencyCmd() const;

    unsigned char GetHLCSSacsOnCmd() const;
};

#endif // IDANWRAPPER_H