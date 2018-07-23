#ifndef IDANPLUGINAPI_H
#define IDANPLUGINAPI_H

/*
* IdanPluginAPI.h
* API for external tools that need to use IDAN
* Author: Binyamin Appelbaum
* Date: 25.03.18
*/

#ifdef _WIN32
#	define LIBRARY_API __declspec(dllexport)	
#else
#	define LIBRARY_API
#endif

struct IdanWrapper;

// Functions that can be used by the plugin
extern "C" {
	LIBRARY_API IdanWrapper* IdanCreateObject(const char* confFilePath);

	LIBRARY_API void IdanDeleteObject(IdanWrapper* pObj);

	LIBRARY_API void SendIdanPrimaryData(IdanWrapper* pObj);

	LIBRARY_API void SendIdanSecondaryReportData(IdanWrapper* pObj);

	LIBRARY_API void SendIdanSecondarySensorData(IdanWrapper* pObj);

	LIBRARY_API void IdanReceiveData(IdanWrapper* pObj);

    /********************************* HLC Primary *************************************************/
	LIBRARY_API bool HasHLCPShutDownCmd(IdanWrapper* pObj);

	LIBRARY_API bool HasHLCPEmergencyCmd(IdanWrapper* pObj);

	LIBRARY_API float GetHLCPSteerCmd(IdanWrapper* pObj);

	LIBRARY_API float GetHLCPGasCmd(IdanWrapper* pObj);

    /********************************* HLC Secondary *************************************************/
	LIBRARY_API bool HasHLCSShutDownCmd(IdanWrapper* pObj);
    
	LIBRARY_API bool IsHLCSRoadLightsApplied(IdanWrapper* pObj);

	LIBRARY_API  bool IsHLCSHighBeamApplied(IdanWrapper* pObj);

	LIBRARY_API bool IsHLCSLightsCutoffApplied(IdanWrapper* pObj);

	LIBRARY_API bool IsHLCSParkingLightApplied(IdanWrapper* pObj);

	LIBRARY_API bool IsHLCSKeySwitchApplied(IdanWrapper* pObj);

	LIBRARY_API bool IsHLCSMotorStarterApplied(IdanWrapper* pObj);

	LIBRARY_API bool IsHLCSHornApplied(IdanWrapper* pObj);

	LIBRARY_API bool IsHLCSLeftTurnSignalApplied(IdanWrapper* pObj);

	LIBRARY_API bool IsHLCSRightTurnSignalApplied(IdanWrapper* pObj);

	LIBRARY_API bool IsHLCSHazardsApplied(IdanWrapper* pObj);

	LIBRARY_API const char* GetHLCSGear(IdanWrapper* pObj);

	LIBRARY_API bool IsHLCSParkingBrakeReleased(IdanWrapper* pObj);

	LIBRARY_API bool HasHLCSEmergencyCmd(IdanWrapper* pObj);

	LIBRARY_API bool HasHLCSSacsOnCmd(IdanWrapper* pObj);

   /************************************************* IDAN Primary ********************************************/
	LIBRARY_API void SetIdanPrimSteerPos(IdanWrapper* obj, float steerPose);

	LIBRARY_API void SetIdanPrimGasPos(IdanWrapper* obj, float gasPose);

    /************************************************* IDAN Secondary Report ********************************************/
	
	LIBRARY_API void SetIdanSecRepRoadLights(IdanWrapper* obj, bool roadLights);

	LIBRARY_API void SetIdanSecRepHighBeam(IdanWrapper* obj, bool highBeam);

	LIBRARY_API void SetIdanSecRepLightsCutoff(IdanWrapper* obj, bool lightsCutoff) ;

	LIBRARY_API void SetIdanSecRepKeySwitch(IdanWrapper* obj, bool keySwitch);

	LIBRARY_API void SetIdanSecRepMotorStarter(IdanWrapper* obj, bool motorStarter);

	LIBRARY_API void SetIdanSecRepHorn(IdanWrapper* obj, bool horn);

	LIBRARY_API void SetIdanSecRepLeftTurnSignal(IdanWrapper* obj, bool leftTurnSignal);

	LIBRARY_API void SetIdanSecRepRightTurnSignal(IdanWrapper* obj, bool rightTurnSignal);

	LIBRARY_API void SetIdanSecRepHazards(IdanWrapper* obj, bool hazards);

	LIBRARY_API void SetIdanSecRepRequestedGear(IdanWrapper* obj, const char* requestedGear);

	LIBRARY_API void SetIdanSecRepActualGear(IdanWrapper* obj, const char* actualGear);

	LIBRARY_API void SetIdanSecRepParkingBrake(IdanWrapper* obj, const char* parkingBrake);

	LIBRARY_API void SetIdanSecRepRpm(IdanWrapper* obj, float rpm);

	LIBRARY_API void SetIdanSecRepVelocity(IdanWrapper* obj, float velocity);

    /************************************************* IDAN Secondary Sensor ********************************************/
    
	LIBRARY_API void SetIdanSecSenEngineTemp(IdanWrapper* obj, float engineTemp);

	LIBRARY_API void SetIdanSecSenOilPress(IdanWrapper* obj, float oilPress);

	LIBRARY_API void SetIdanSecSenFuelLevel(IdanWrapper* obj, float fuelLevel);

	LIBRARY_API void SetIdanSecSenAlternatorVoltage(IdanWrapper* obj, float alternatorVoltage);

	LIBRARY_API void SetIdanSecSenBackupBattVoltage(IdanWrapper* obj, float backupBattVoltage);

	LIBRARY_API void SetIdanSecSenBatterySumUp(IdanWrapper* obj, int batterySumUp);

	LIBRARY_API void SetIdanSecSenAirPressFront(IdanWrapper* obj, float airPressFront);

	LIBRARY_API void SetIdanSecSenAirPressRear(IdanWrapper* obj, float airPressRear);
}

#endif // IDANPLUGINAPI_H