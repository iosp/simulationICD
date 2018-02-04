/*
* DgpsWrapper.cpp
* Wrapper for DGPS
* Author: Binyamin Appelbaum
* Date: 23.01.18
*/

#include "DgpsWrapper.h"
#include "DgpsControl.h"


DgpsWrapper::DgpsWrapper(const std::string& portName, int baudRate) {
    DgpsConfig config(portName, baudRate);
    m_icd = new DgpsControl(config);
}

DgpsWrapper::~DgpsWrapper(){
    delete m_icd;
}

void DgpsWrapper::Run() {
    m_icd->Run();
}

void DgpsWrapper::SetPosition(double latitude, double longitude, double altitude) {
    m_data.SetLatitude(latitude);
    m_data.SetLongitude(longitude);
    m_data.SetAltitude(altitude);
}

void DgpsWrapper::SetVelocities(double latSpeed, double longSpeed, double altAzimuth) {
    m_data.SetLatSpeed(latSpeed);
    m_data.SetLongSpeed(longSpeed);
    m_data.SetAltAzimuth(altAzimuth);
}

void DgpsWrapper::SetTimeStamp(int timeStamp) {
    m_data.SetSimTime(boost::posix_time::microseconds(timeStamp));
}

void DgpsWrapper::SetData() {
    m_icd->SetData(m_data);
    ClearCurrentData();
}

void DgpsWrapper::ClearCurrentData() {
    m_data = DgpsData();
}
