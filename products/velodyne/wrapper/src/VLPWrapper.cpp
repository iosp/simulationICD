
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

void VLPWrapper::SetData() {
    m_icd->SetData(m_data);
    InitData();
}

void VLPWrapper::SetAzimuth(double azimuth){
     m_currBlock.SetAzimuth(azimuth);
}

void VLPWrapper::SetTimeStamp(float timeStamp) {
     m_currBlock.SetSimTime(timeStamp);
}

void VLPWrapper::SetChannel(double distance, short reflectivity) {
    m_currChannels.push_back(std::pair<double, short>(distance, reflectivity));
}

void VLPWrapper::CloseBlock() {
    m_currBlock.SetChannels(m_currChannels);
    m_data.AddBlock(m_currBlock);
    InitCurrBlock();
}

void VLPWrapper::InitData() {
    m_data = VelodyneData();
}

void VLPWrapper::InitCurrBlock() {
    m_currChannels.clear();
    m_currBlock = VelodyneData::VelodyneBlock();
}