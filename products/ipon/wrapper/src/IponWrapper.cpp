/*
* IponWrapper.cpp
* Wrapper for IPON
* Author: Binyamin Appelbaum
* Date: 08.05.18
*/

#include "IponWrapper.h"
#include "IponControl.h"


IponWrapper::IponWrapper(const std::string& confFilePath) {
    m_icd = new IponControl(confFilePath);
}

IponWrapper::~IponWrapper(){
    delete m_icd;
}

void IponWrapper::Run() {
    m_icd->Run();
}

void IponWrapper::SetData() {
    m_icd->SetData(m_data);
    ClearCurrentData();
}

void IponWrapper::ClearCurrentData() {
    m_data = IponData();
}
