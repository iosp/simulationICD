/*
* DgpsWrapper.cpp
* Wrapper for DGPS
* Author: Binyamin Appelbaum
* Date: 23.01.18
*/

#include "DgpsWrapper.h"
#include "DgpsControl.h"


DgpsWrapper::DgpsWrapper(const std::string& confFilePath) {
    m_icd = new DgpsControl(confFilePath);
}

DgpsWrapper::~DgpsWrapper(){
    delete m_icd;
}

void DgpsWrapper::SetPosition(double latitude, double longitude, double altitude) {
    m_data.SetBestPosLatitude(latitude);
    m_data.SetBestPosLongitude(longitude);
    m_data.SetBestPosAltitude(altitude);
}

void DgpsWrapper::SetVelocities(double latSpeed, double longSpeed, double altAzimuth) {
    m_data.SetBestVelLatitude(latSpeed);
    m_data.SetBestVelLongitude(longSpeed);
    m_data.SetBestVelAltitude(altAzimuth);
}

void DgpsWrapper::SetTimeStamp(float timeStamp) {
    m_data.SetSimTime(timeStamp);
}

void DgpsWrapper::SetMsgType(DgpsMsgType msgType) {
    m_data.SetCurrMsgType(msgType);
}

void DgpsWrapper::SendData() {
    m_icd->SendData(m_data);
    ClearCurrentData();
}

void DgpsWrapper::ClearCurrentData() {
    m_data = DgpsData();
}
