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