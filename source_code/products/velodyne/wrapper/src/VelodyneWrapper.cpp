/*
* VelodyneWrapper.cpp
* Wrapper fpr velodyne ICD
* Author: Binyamin Appelbaum
* Date: 04.01.18
*/

#include "VelodyneWrapper.h"
#include "VelodyneControl.h"

VelodyneWrapper::VelodyneWrapper(const std::string& confFilePath) {
    m_icd = new VelodyneControl(confFilePath);
}

VelodyneWrapper::~VelodyneWrapper(){
    delete m_icd;
}

void VelodyneWrapper::SendData() {
    m_icd->SendData(m_data);
    InitData();
}

void VelodyneWrapper::SetAzimuth(double azimuth){
     m_currBlock.SetAzimuth(azimuth);
}

void VelodyneWrapper::SetTimeStamp(float timeStamp) {
     m_currBlock.SetSimTime(timeStamp);
}

void VelodyneWrapper::SetChannel(double distance, short reflectivity) {
    m_currChannels.push_back(std::pair<double, short>(distance, reflectivity));
}

void VelodyneWrapper::CloseBlock() {
    m_currBlock.SetChannels(m_currChannels);
    m_data.AddBlock(m_currBlock);
    InitCurrBlock();
}

void VelodyneWrapper::InitData() {
    m_data = VelodyneData();
}

void VelodyneWrapper::InitCurrBlock() {
    m_currChannels.clear();
    m_currBlock = VelodyneData::VelodyneBlock();
}