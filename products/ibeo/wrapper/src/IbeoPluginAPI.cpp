/*
* IbeoPluginAPI.h
* API for external tools that need to use IBEO
* Author: Binyamin Appelbaum
* Date: 24.04.18
*/

#include "IbeoPluginAPI.h"

IbeoWrapper* IbeoCreateObject(const char* confFilePath) {
    return new IbeoWrapper(confFilePath);
}

void IbeoDeleteObject(IbeoWrapper* pObj) {
    delete pObj;
}

void IbeoSendData(IbeoWrapper* pObj) {
    pObj->SendData();
}

void IbeoSetNumOfPoints(IbeoWrapper* pObj, int numOfPoints) {
	pObj->SetNumOfPoints(numOfPoints);
}

void IbeoSetRangePointB1(IbeoWrapper* pObj, double point) {
	pObj->SetRangePointB1(point);
}

void IbeoSetRangePointB2(IbeoWrapper* pObj, double point) {
	pObj->SetRangePointB2(point);
}

void IbeoSetRangePointT1(IbeoWrapper* pObj, double point) {
	pObj->SetRangePointT1(point);
}

void IbeoSetRangePointT2(IbeoWrapper* pObj, double point) {
	pObj->SetRangePointT2(point);
}

void IbeoSetTimeStamp(IbeoWrapper* pObj, float timeStamp) {
	pObj->SetTimeStamp(timeStamp);
}