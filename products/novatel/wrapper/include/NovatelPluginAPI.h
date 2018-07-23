#ifndef NOVATELPLUGINAPI_H
#define NOVATELPLUGINAPI_H

/*
* NovatelPluginAPI.h
* API for external tools that need to use Novatel
* Author: Binyamin Appelbaum
* Date: 23.01.18
*/

#ifdef _WIN32
	#define LIBRARY_API __declspec(dllexport)	
#elif
	#define LIBRARY_API
#endif

struct NovatelWrapper;

// Functions that can be used by the plugin
extern "C" {
	LIBRARY_API NovatelWrapper* NovatelCreateObject(const char* confFilePath);

	LIBRARY_API void NovatelDeleteObject(NovatelWrapper* pObj);

	LIBRARY_API void NovatelSendBestPosData(NovatelWrapper* pObj);

	LIBRARY_API void NovatelSendBestVelData(NovatelWrapper* pObj);

	LIBRARY_API void NovatelSetPosition(NovatelWrapper* pObj, double latitude, double longitude, double altitude);

	LIBRARY_API void NovatelSetVelocities(NovatelWrapper* pObj, double latSpeed, double longSpeed, double altAzimuth);

	LIBRARY_API void NovatelSetTimeStamp(NovatelWrapper* pObj, float timeStamp);
}

#endif // NOVATELPLUGINAPI_H