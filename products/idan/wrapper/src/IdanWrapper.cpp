/*
* IdanWrapper.cpp
* Wrapper for Idan
* Author: Binyamin Appelbaum
* Date: 25.03.18
*/

#include "IdanWrapper.h"
#include "IdanControl.h"


IdanWrapper::IdanWrapper(const std::string& confFilePath) {
    m_icd = new IdanControl(confFilePath);
}

IdanWrapper::~IdanWrapper(){
    delete m_icd;
}

void IdanWrapper::Run() {
    m_icd->Run();
}

void IdanWrapper::GetData() {
    m_data = m_icd->GetData();
}

unsigned char IdanWrapper::GetShutDownCmd() {
    return m_data.GetShutDownCmd();
}

void IdanWrapper::ClearCurrentData() {
    m_data = IdanData();
}
