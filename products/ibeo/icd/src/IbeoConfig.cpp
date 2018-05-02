/*
* IbeoConfig.cpp
* 
* Author: Binyamin Appelbaum
* Date: 23.04.18
*/

#include "IbeoConfig.h"
#include "LoggerProxy.h"
#include "ConfigurationINI.h"

const std::string IbeoConfig::IP_ADDRESS_KEY = "IP_ADDRESS";
const std::string IbeoConfig::IP_ADDRESS_DEF_VAL = "192.168.0.1";
const std::string IbeoConfig::PORT_KEY = "PORT";
const std::string IbeoConfig::PORT_DEF_VAL = "12002";
const std::string IbeoConfig::HERTZ_KEY = "HERTZ";
const std::string IbeoConfig::HERTZ_DEF_VAL = "12.5";
const std::string IbeoConfig::T_START_ANGLE_KEY = "T_START_ANGLE";
const std::string IbeoConfig::T_START_ANGLE_DEF_VAL = "10";
const std::string IbeoConfig::T_END_ANGLE_KEY = "T_END_ANGLE";
const std::string IbeoConfig::T_END_ANGLE_DEF_VAL = "20";
const std::string IbeoConfig::B_START_ANGLE_KEY = "B_START_ANGLE";
const std::string IbeoConfig::B_START_ANGLE_DEF_VAL = "10";
const std::string IbeoConfig::B_END_ANGLE_KEY = "B_END_ANGLE";
const std::string IbeoConfig::B_END_ANGLE_DEF_VAL = "20";
const std::string IbeoConfig::ANGLE_INCREMENT_KEY = "ANGLE_INCREMENT";
const std::string IbeoConfig::ANGLE_INCREMENT_DEF_VAL = "0.4";

IbeoConfig::IbeoConfig(const std::string& confFilePath) {
    m_ibeoConf = new ConfigurationINI(confFilePath);
    SetConfDefaultValues();
    m_ibeoConf->ParseConfFile();
    LOG << "IBEO configuration is:\n" << m_ibeoConf->toString() << "\n";
}

IbeoConfig::~IbeoConfig() {
    delete m_ibeoConf;
}

void IbeoConfig::SetConfDefaultValues() {
	m_ibeoConf->SetValue(IP_ADDRESS_KEY, IP_ADDRESS_DEF_VAL);
	m_ibeoConf->SetValue(PORT_KEY, PORT_DEF_VAL);
    m_ibeoConf->SetValue(HERTZ_KEY, HERTZ_DEF_VAL);
    m_ibeoConf->SetValue(T_START_ANGLE_KEY, T_START_ANGLE_DEF_VAL);
    m_ibeoConf->SetValue(T_END_ANGLE_KEY, T_END_ANGLE_DEF_VAL);
    m_ibeoConf->SetValue(B_START_ANGLE_KEY, B_START_ANGLE_DEF_VAL);
    m_ibeoConf->SetValue(B_END_ANGLE_KEY, B_END_ANGLE_DEF_VAL);
    m_ibeoConf->SetValue(ANGLE_INCREMENT_KEY, ANGLE_INCREMENT_DEF_VAL);
}

std::string IbeoConfig::GetIpAddress() const {
    return m_ibeoConf->GetValue<std::string>(IP_ADDRESS_KEY);
}

std::string IbeoConfig::GetPort() const {
    return m_ibeoConf->GetValue<std::string>(PORT_KEY);
}

float IbeoConfig::GetHertz() const {
    return m_ibeoConf->GetValue<float>(HERTZ_KEY);
}

double IbeoConfig::GetTStartAngle() const {
    return m_ibeoConf->GetValue<double>(T_START_ANGLE_KEY);
}

double IbeoConfig::GetTEndAngle() const {
    return m_ibeoConf->GetValue<double>(T_END_ANGLE_KEY);
}

double IbeoConfig::GetBStartAngle() const {
    return m_ibeoConf->GetValue<double>(B_START_ANGLE_KEY);
}

double IbeoConfig::GetBEndAngle() const {
    return m_ibeoConf->GetValue<double>(B_END_ANGLE_KEY);
}

double IbeoConfig::GetAngleIncrement() const {
    return m_ibeoConf->GetValue<double>(ANGLE_INCREMENT_KEY);
}