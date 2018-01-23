
#include "DgpsWrapper.h"
#include "DgpsCommunication.h"


DgpsWrapper::DgpsWrapper() {
    m_icd = new DgpsCommunication();
}

DgpsWrapper::~DgpsWrapper(){
    delete m_icd;
}

void DgpsWrapper::Run() {
    m_icd->Run();
}

void DgpsWrapper::SetData() {
    m_icd->SetData(m_data);
    ClearCurrentData();
}

void DgpsWrapper::ClearCurrentData() {
    m_data = DgpsData();
}
