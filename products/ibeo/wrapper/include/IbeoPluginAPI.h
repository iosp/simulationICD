#ifndef IBEOPLUGINAPI_H
#define IBEOPLUGINAPI_H

/*
* IbeoPluginAPI.h
* API for external tools that need to use IBEO
* Author: Binyamin Appelbaum
* Date: 24.04.18
*/

#include "IbeoWrapper.h"

// Functions that can be used by the plugin
extern "C" {
    IbeoWrapper* CreateIbeoObject(const char* confFilePath);

    void DeleteIbeoObject(IbeoWrapper* pObj);

    void RunIbeo(IbeoWrapper* pObj);

    void SendIbeoData(IbeoWrapper* pOb);

    void SetNumOfPoints(IbeoWrapper* pOb, int numOfPoints);

    void SetRangePointB1(IbeoWrapper* pOb, double point);

    void SetRangePointB2(IbeoWrapper* pOb, double point);

    void SetRangePointT1(IbeoWrapper* pOb, double point);

    void SetRangePointT2(IbeoWrapper* pOb, double point);

    void SetIbeoTimeStamp(IbeoWrapper* pVlp, float timeStamp);
}

#endif // IBEOPLUGINAPI_H