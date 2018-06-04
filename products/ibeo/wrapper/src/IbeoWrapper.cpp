/*
* IbeoWrapper.cpp
* Wrapper for IBEO
* Author: Binyamin Appelbaum
* Date: 24.04.18
*/

#include "IbeoWrapper.h"
#include "IbeoControl.h"


IbeoWrapper::IbeoWrapper(const std::string& confFilePath) {
    m_icd = new IbeoControl(confFilePath);
}

IbeoWrapper::~IbeoWrapper(){
    delete m_icd;
}

void IbeoWrapper::SetNumOfPoints(int numOfPoints) {
    m_data.SetNumOfPoints(numOfPoints);
}

void IbeoWrapper::SetRangePointB1(double point) {
    m_currRangeB1.push_back(point);
}

void IbeoWrapper::SetRangePointB2(double point){
    m_currRangeB2.push_back(point);
}

void IbeoWrapper::SetRangePointT1(double point){
    m_currRangeT1.push_back(point);
}

void IbeoWrapper::SetRangePointT2(double point){
    m_currRangeT2.push_back(point);
}

void IbeoWrapper::SetTimeStamp(float timeStamp) {
    m_data.SetSimTime(timeStamp);
}

void IbeoWrapper::SendData() {
    m_data.SetRangeB1(m_currRangeB1);
    m_data.SetRangeB2(m_currRangeB2);
    m_data.SetRangeT1(m_currRangeT1);
    m_data.SetRangeT2(m_currRangeT2);
    m_icd->SendData(m_data);
    ClearCurrentData();
}

void IbeoWrapper::ClearCurrentData() {
    m_data = IbeoData();
    m_currRangeB1.clear();
    m_currRangeB2.clear();
    m_currRangeT1.clear();
    m_currRangeT2.clear();
}
