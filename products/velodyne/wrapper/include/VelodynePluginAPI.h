#ifndef VELODYNEPLUGIN_H
#define VELODYNEPLUGIN_H

/*
* VelodynePluginAPI.h
* API for external tools that need to use Velodyne
    * How to use:
    *   Create Velodyne object
    *   Set azimuth, time stamp and 16 channels
    *   Close block
    *   After 24 blocks - send data
* Author: Binyamin Appelbaum
* Date: 04.01.18
*/

struct VelodyneWrapper;

// Functions that can be used by the plugin
extern "C" {
    VelodyneWrapper* VelodyneCreateObject(const char* confFilePath);

    void VelodyneDeleteObject(VelodyneWrapper* pObj);

    void VelodyneSetAzimuth(VelodyneWrapper* pObj, double azimuth);

    void VelodyneSetTimeStamp(VelodyneWrapper* pObj, float timeStamp);

    void VelodyneSetChannel(VelodyneWrapper* pObj, double distance, short reflectivity);

    void VelodyneCloseBlock(VelodyneWrapper* pObj);

    void VelodyneSendData(VelodyneWrapper* pObj);
}

#endif // VELODYNEPLUGIN_H