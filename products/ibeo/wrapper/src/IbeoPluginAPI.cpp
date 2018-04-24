/*
* IbeoPluginAPI.h
* API for external tools that need to use IBEO
* Author: Binyamin Appelbaum
* Date: 24.04.18
*/

#include "IbeoPluginAPI.h"

IbeoWrapper* CreateIbeoObject(const char* confFilePath) {
    return new IbeoWrapper(confFilePath);
}

void DeleteIbeoObject(IbeoWrapper* pObj) { delete pObj;}

void RunIbeo(IbeoWrapper* pObj) { pObj->Run(); }

void SendIbeoData(IbeoWrapper* pObj) { pObj->SetData();}

void SetNumOfPoints(IbeoWrapper* pObj, int numOfPoints) {
    pObj->SetNumOfPoints(numOfPoints);
}

void SetRangePointB1(IbeoWrapper* pObj, double point) {
    pObj->SetRangePointB1(point);
}

void SetRangePointB2(IbeoWrapper* pObj, double point) {
    pObj->SetRangePointB2(point);
}

void SetRangePointT1(IbeoWrapper* pObj, double point) {
    pObj->SetRangePointT1(point);
}

void SetRangePointT2(IbeoWrapper* pObj, double point) {
    pObj->SetRangePointT2(point);
}

void SetIbeoTimeStamp(IbeoWrapper* pObj, float timeStamp) {
    pObj->SetTimeStamp(timeStamp);
}