/*
* NovatelWrapper.cpp
* Wrapper for Novatel
* Author: Binyamin Appelbaum
* Date: 23.01.18
*/

#include "NovatelWrapper.h"
#include "NovatelControl.h"


NovatelWrapper::NovatelWrapper(const std::string& confFilePath) {
    m_icd = new NovatelControl(confFilePath);
}

NovatelWrapper::~NovatelWrapper(){
    delete m_icd;
}

void NovatelWrapper::SetPosition(double latitude, double longitude, double altitude) {
    m_data.SetBestPosLatitude(latitude);
    m_data.SetBestPosLongitude(longitude);
    m_data.SetBestPosAltitude(altitude);
}

void NovatelWrapper::SetVelocities(double latSpeed, double longSpeed, double altAzimuth) {
    m_data.SetBestVelLatitude(latSpeed);
    m_data.SetBestVelLongitude(longSpeed);
    m_data.SetBestVelAltitude(altAzimuth);
}

void NovatelWrapper::SetTimeStamp(float timeStamp) {
    m_data.SetSimTime(timeStamp);
}

void NovatelWrapper::SetMsgType(NovatelMsgType msgType) {
    m_data.SetCurrMsgType(msgType);
}

void NovatelWrapper::SendData() {
    m_icd->SendData(m_data);
    ClearCurrentData();
}

void NovatelWrapper::ClearCurrentData() {
    m_data = NovatelData();
}
