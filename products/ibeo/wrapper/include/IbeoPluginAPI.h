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
    IbeoWrapper* IbeoCreateObject(const char* confFilePath);

    void IbeoDeleteObject(IbeoWrapper* pObj);

    void IbeoRun(IbeoWrapper* pObj);

    void IbeoSendData(IbeoWrapper* pObj);

    void IbeoSetNumOfPoints(IbeoWrapper* pObj, int numOfPoints);

    void IbeoSetRangePointB1(IbeoWrapper* pObj, double point);

    void IbeoSetRangePointB2(IbeoWrapper* pObj, double point);

    void IbeoSetRangePointT1(IbeoWrapper* pObj, double point);

    void IbeoSetRangePointT2(IbeoWrapper* pObj, double point);

    void IbeoSetTimeStamp(IbeoWrapper* pObj, float timeStamp);

}

#endif // IBEOPLUGINAPI_H