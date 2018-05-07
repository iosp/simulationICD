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

#include "VLPWrapper.h"

// Functions that can be used by the plugin
extern "C" {
    VLPWrapper* VLPCreateObject(const char* confFilePath);

    void VLPDeleteObject(VLPWrapper* pVlp);

    void VLPSetAzimuth(VLPWrapper* pVlp, double azimuth);

    void VLPSetTimeStamp(VLPWrapper* pVlp, float timeStamp);

    void VLPSetChannel(VLPWrapper* pVlp, double distance, short reflectivity);

    void VLPCloseBlock(VLPWrapper* pVlp);

    void VLPSendData(VLPWrapper* pVlp);
}

#endif // VLPPLUGIN_H