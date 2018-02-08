#ifndef VLPPLUGIN_H
#define VLPPLUGIN_H

/*
* VLPPluginAPI.h
* API for external tools that need to use VLP
* Author: Binyamin Appelbaum
* Date: 04.01.18
*/

#include "VLPWrapper.h"

// Functions that can be used by the plugin
extern "C" {
    VLPWrapper* CreateVLPObject(const char* confFilePath);

    void DeleteVLPObject(VLPWrapper* pVlp);

    void RunVLP(VLPWrapper* pVlp);

    void SetAzimuth(VLPWrapper* pVlp, double azimuth);

    void SetVLPTimeStamp(VLPWrapper* pVlp, int timeStamp);

    void SetChannel(VLPWrapper* pVlp, double distance, short reflectivity);

    void SendVLPData(VLPWrapper* pVlp);
}

#endif // VLPPLUGIN_H