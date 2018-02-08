#ifndef DGPSPLUGINAPI_H
#define DGPSPLUGINAPI_H

/*
* DgpsPluginAPI.h
* API for external tools that need to use DGPS
* Author: Binyamin Appelbaum
* Date: 23.01.18
*/

#include "DgpsWrapper.h"

// Functions that can be used by the plugin
extern "C" {
    DgpsWrapper* CreateDgpsObject(const char* confFilePath);

    void DeleteDgpsObject(DgpsWrapper* pObj);

    void RunDgps(DgpsWrapper* pObj);

    void SendDgpsData(DgpsWrapper* pOb);

    void SetPosition(DgpsWrapper* pObj, double latitude, double longitude, double altitude);

    void SetVelocities(DgpsWrapper* pObj, double latSpeed, double longSpeed, double altAzimuth);

    void SetDgpsTimeStamp(DgpsWrapper* pVlp, int timeStamp);
}

#endif // DGPSPLUGINAPI_H