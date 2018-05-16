#ifndef VLPPLUGIN_H
#define VLPPLUGIN_H

/*
* VLPPluginAPI.h
* API for external tools that need to use VLP
    * How to use:
    *   Create VLP object
    *   Set azimuth, time stamp and 16 channels
    *   Close block
    *   After 24 blocks - send data
* Author: Binyamin Appelbaum
* Date: 04.01.18
*/

struct VLPWrapper;

// Functions that can be used by the plugin
extern "C" {
    VLPWrapper* VLPCreateObject(const char* confFilePath);

    void VLPDeleteObject(VLPWrapper* pObj);

    void VLPSetAzimuth(VLPWrapper* pObj, double azimuth);

    void VLPSetTimeStamp(VLPWrapper* pObj, float timeStamp);

    void VLPSetChannel(VLPWrapper* pObj, double distance, short reflectivity);

    void VLPCloseBlock(VLPWrapper* pObj);

    void VLPSendData(VLPWrapper* pObj);
}

#endif // VLPPLUGIN_H