
/*
* VLPPluginAPI.cpp
* API for external tools that need to use VLP
* Author: Binyamin Appelbaum
* Date: 04.01.18
*/

#include "VLPPluginAPI.h"

VLPWrapper* CreateVLPObject(const char* confFilePath) {
    return new VLPWrapper(confFilePath);
}

void DeleteVLPObject(VLPWrapper* pVlp) {delete pVlp;}

void RunVLP(VLPWrapper* pVlp) { pVlp->Run();}

void SetAzimuth(VLPWrapper* pVlp, double azimuth){ pVlp->SetAzimuth(azimuth); }

void SetVLPTimeStamp(VLPWrapper* pVlp, int timeStamp) { pVlp->SetTimeStamp(timeStamp); }

void SetChannel(VLPWrapper* pVlp, double distance, short reflectivity) { pVlp->SetChannel(distance, reflectivity); }

void SendVLPData(VLPWrapper* pVlp) { pVlp->SetData(); }