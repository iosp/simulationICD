/*
* IbeoConfig.cpp
* 
* Author: Binyamin Appelbaum
* Date: 23.04.18
*/

#include "IbeoConfig.h"
#include "ConfigurationINI.h"

const std::string IbeoConfig::PORT_KEY = "PORT";
const std::string IbeoConfig::PORT_DEF_VAL = "12002";
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

IbeoConfig::IbeoConfig(const std::string& confFilePath) : ProdConfig(confFilePath) {
    LOG << "Initializing ibeo configurations\n";
    Init();
}

void IbeoConfig::SetConfDefaultValues() {
	m_conf->SetValue(PORT_KEY, PORT_DEF_VAL);
    m_conf->SetValue(T_START_ANGLE_KEY, T_START_ANGLE_DEF_VAL);
    m_conf->SetValue(T_END_ANGLE_KEY, T_END_ANGLE_DEF_VAL);
    m_conf->SetValue(B_START_ANGLE_KEY, B_START_ANGLE_DEF_VAL);
    m_conf->SetValue(B_END_ANGLE_KEY, B_END_ANGLE_DEF_VAL);
    m_conf->SetValue(ANGLE_INCREMENT_KEY, ANGLE_INCREMENT_DEF_VAL);
}

std::string IbeoConfig::GetProdName() const {
    return "IBEO";
}

std::string IbeoConfig::GetPort() const {
    return m_conf->GetValue<std::string>(PORT_KEY);
}

double IbeoConfig::GetTStartAngle() const {
    return m_conf->GetValue<double>(T_START_ANGLE_KEY);
}

double IbeoConfig::GetTEndAngle() const {
    return m_conf->GetValue<double>(T_END_ANGLE_KEY);
}

double IbeoConfig::GetBStartAngle() const {
    return m_conf->GetValue<double>(B_START_ANGLE_KEY);
}

double IbeoConfig::GetBEndAngle() const {
    return m_conf->GetValue<double>(B_END_ANGLE_KEY);
}

double IbeoConfig::GetAngleIncrement() const {
    return m_conf->GetValue<double>(ANGLE_INCREMENT_KEY);
}