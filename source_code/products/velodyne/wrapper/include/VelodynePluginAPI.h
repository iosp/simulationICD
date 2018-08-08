#ifndef VELODYNEPLUGIN_H
#define VELODYNEPLUGIN_H

/*
* VelodynePluginAPI.h
* API for external tools that need to use Velodyne
    * How to use:
    *   Create Velodyne object
    *   Initialize communication
    *   Set azimuth, time stamp and 16 channels
    *   Close block
    *   After 24 blocks - send data
* Author: Binyamin Appelbaum
* Date: 04.01.18
*/

#ifdef _WIN32
#	define LIBRARY_API __declspec(dllexport)	
#else
#	define LIBRARY_API
#endif


struct VelodyneWrapper;

// Functions that can be used by the plugin
extern "C"  {
	LIBRARY_API VelodyneWrapper* Velodyne16CreateObject(const char* confFilePath);

	LIBRARY_API VelodyneWrapper* Velodyne32CreateObject(const char* confFilePath);

	LIBRARY_API void VelodyneDeleteObject(VelodyneWrapper* pObj);

	LIBRARY_API void VelodyneSetAzimuth(VelodyneWrapper* pObj, double azimuth);

	LIBRARY_API void VelodyneSetTimeStamp(VelodyneWrapper* pObj, float timeStamp);

	LIBRARY_API void VelodyneSetChannel(VelodyneWrapper* pObj, double distance, short reflectivity);

	LIBRARY_API void VelodyneCloseBlock(VelodyneWrapper* pObj);

	LIBRARY_API void VelodyneSendData(VelodyneWrapper* pObj);
}

#endif // VELODYNEPLUGIN_H