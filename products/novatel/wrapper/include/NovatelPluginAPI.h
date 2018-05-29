#ifndef NOVATELPLUGINAPI_H
#define NOVATELPLUGINAPI_H

/*
* NovatelPluginAPI.h
* API for external tools that need to use Novatel
* Author: Binyamin Appelbaum
* Date: 23.01.18
*/

struct NovatelWrapper;

// Functions that can be used by the plugin
extern "C" {
    NovatelWrapper* NovatelCreateObject(const char* confFilePath);

    void NovatelDeleteObject(NovatelWrapper* pObj);

    void NovatelInitCommunication(NovatelWrapper* pObj);

    void NovatelSendBestPosData(NovatelWrapper* pObj);

    void NovatelSendBestVelData(NovatelWrapper* pObj);

    void NovatelSetPosition(NovatelWrapper* pObj, double latitude, double longitude, double altitude);

    void NovatelSetVelocities(NovatelWrapper* pObj, double latSpeed, double longSpeed, double altAzimuth);

    void NovatelSetTimeStamp(NovatelWrapper* pObj, float timeStamp);
}

#endif // NOVATELPLUGINAPI_H