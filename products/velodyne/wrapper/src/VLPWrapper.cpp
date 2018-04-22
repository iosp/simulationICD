
/*
* VLPWrapper.cpp
* Wrapper fpr velodyne ICD
* Author: Binyamin Appelbaum
* Date: 04.01.18
*/

#include "VLPWrapper.h"
#include "VLPControl.h"

VLPWrapper::VLPWrapper(const std::string& confFilePath) {
    m_icd = new VLPControl(confFilePath);
}

VLPWrapper::~VLPWrapper(){
    delete m_icd;
}

void VLPWrapper::Run() {
    m_icd->Run();
}

void VLPWrapper::SetData() {
    m_data.SetChannels(m_currChannels);
    m_icd->SetData(m_data);
    ClearCurrentData();
}

void VLPWrapper::SetAzimuth(double azimuth){
     m_data.SetAzimuth(azimuth);
}

void VLPWrapper::SetTimeStamp(float timeStamp) {
     m_data.SetSimTime(timeStamp);
}

void VLPWrapper::SetChannel(double distance, short reflectivity) {
    m_currChannels.push_back(std::pair<double, short>(distance, reflectivity));
}

void VLPWrapper::ClearCurrentData() {
    m_currChannels.clear();
    m_data.SetChannels(VelodyneData::t_channel_data());
    m_data.SetAzimuth(0);
    m_data.SetSimTime(0);
}
