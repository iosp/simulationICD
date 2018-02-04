
/*
* VLPWrapper.cpp
* Wrapper fpr velodyne ICD
* Author: Binyamin Appelbaum
* Date: 04.01.18
*/

#include "VLPWrapper.h"
#include "VLPConfig.h"
#include "VLP16Control.h"
#include "VLP32Control.h"

VLPWrapper::VLPWrapper(const std::string& ipAddress, const std::string& port, int resolution,
        int returnMode, int dataSource, int sensorFrequency, int velType) {
    VLPConfig vlpConfig(ipAddress, port, VLPConfig::Resolution(resolution), VLPConfig::ReturnMode(returnMode),
        VLPConfig::DataSource(dataSource), sensorFrequency);
    // create the required object
    if (velType == 16) {
        m_icd = new VLP16Control(vlpConfig);
    }
    else {
        m_icd = new VLP32Control(vlpConfig);
    }
}

VLPWrapper::~VLPWrapper(){
    delete m_icd;
}

void VLPWrapper::Run() {
    m_icd->Run();
}

void VLPWrapper::SetData() {
    // assign the data, create vector in size 1 to adapt the API and clear the current data
    m_data.SetChannels(m_currChannels);
    std::vector<VelodyneData::VLPBlock> vData(1, m_data);
    VelodyneData data(vData);
    m_icd->SetData(data);
    ClearCurrentData();
}

void VLPWrapper::SetAzimuth(double azimuth){
     m_data.SetAzimuth(azimuth);
}

void VLPWrapper::SetTimeStamp(int timeStamp) {
     m_data.SetSimTime(boost::posix_time::microseconds(timeStamp));
}

void VLPWrapper::SetChannel(double distance, short reflectivity) {
    m_currChannels.push_back(std::pair<double, short>(distance, reflectivity));
}

void VLPWrapper::ClearCurrentData() {
    m_currChannels.clear();
    m_data.SetChannels(VelodyneData::VLPBlock::t_channel_data());
    m_data.SetAzimuth(0);
    m_data.SetSimTime(boost::posix_time::microseconds(0));
}
