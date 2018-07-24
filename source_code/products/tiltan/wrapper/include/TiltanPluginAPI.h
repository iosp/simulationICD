#ifndef TILTANPLUGINAPI_H
#define TILTANPLUGINAPI_H

/*
* TiltanPluginAPI.h
* API for external tools that need to use Tiltan
* Author: Binyamin Appelbaum
* Date: 18.02.18
*/

#ifdef _WIN32
#	define LIBRARY_API __declspec(dllexport)	
#else
#	define LIBRARY_API
#endif

struct TiltanWrapper;

// Functions that can be used by the plugin
extern "C" {
	LIBRARY_API TiltanWrapper* TiltanCreateObject(const char* confFilePath);

	LIBRARY_API void TiltanDeleteObject(TiltanWrapper* pObj);

	LIBRARY_API void TiltanSendStatusMsgData(TiltanWrapper* pObj);

	LIBRARY_API void TiltanSendInternalGPSData(TiltanWrapper* pObj);

	LIBRARY_API void TiltanSendNavigationData(TiltanWrapper* pObj);

	LIBRARY_API void TiltanSendErrorEstimationData(TiltanWrapper* pObj);

	LIBRARY_API void TiltanSetTimeStamps(TiltanWrapper* pObj, float simTime, float utcTime);

    // Tiltan navigation data message
	LIBRARY_API void TiltanSetPose(TiltanWrapper* pObj, float latitude, float longitude, float altitude);

	LIBRARY_API void TiltanSetOrientation(TiltanWrapper* pObj, float azimuth, float pitch, float roll);

	LIBRARY_API void TiltanSetAzimuthRate(TiltanWrapper* pObj, float azimuthRate);

	LIBRARY_API void TiltanSetVelocity(TiltanWrapper* pObj, float northVelocity, float eastVelocity, float downVelocity);

	LIBRARY_API void TiltanSetDistances(TiltanWrapper* pObj, float distanceTraveled, float odometerDistance);

	LIBRARY_API void TiltanSetMotionDetected(TiltanWrapper* pObj, bool motionDetected);

    // Tiltan internal GPS
	LIBRARY_API void TiltanSetInternalGpsFields(TiltanWrapper* pObj, short gpsFom, short numOfSatelites);

    // Tiltan Errors estimation message
	LIBRARY_API void TiltanSetDirectionErrors(TiltanWrapper* pObj, float horizontalError, float verticalError, float northingError,
                             float eastingError, float altitudeError);

	LIBRARY_API void TiltanSetVelocityErrors(TiltanWrapper* pObj, float northVelocityError, float eastVelocityError, float downVelocityError);

	LIBRARY_API void TiltanSetOrientationErrors(TiltanWrapper* pObj, float azimuthErrorEstimation, float pitchErrorEstimation, float rollErrorEstimation);
}

#endif // TILTANPLUGINAPI_H