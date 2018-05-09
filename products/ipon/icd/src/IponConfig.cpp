/*
* IponConfig.cpp
* 
* Author: Binyamin Appelbaum
* Date: 08.05.18
*/

#include "IponConfig.h"
#include "LoggerProxy.h"
#include "ConfigurationINI.h"

const std::string IponConfig::UDP_IP_ADDRESS_KEY = "UDP_IP_ADDRESS_KEY";
const std::string IponConfig::UDP_IP_ADDRESS_DEF_VAL = "132.4.6.90";
const std::string IponConfig::UDP_PORT_KEY = "UDP_PORT";
const std::string IponConfig::UDP_PORT_DEF_VAL = "2010";
const std::string IponConfig::TCP_PORT_KEY = "TCP_PORT";
const std::string IponConfig::TCP_PORT_DEF_VAL = "2001";
const std::string IponConfig::PERIODIC_1_HZ_KEY = "PERIODIC_1_HZ";
const std::string IponConfig::PERIODIC_1_HZ_KEY_DEF_VAL = "1";
const std::string IponConfig::PERIODIC_100_HZ_KEY = "PERIODIC_100_HZ";
const std::string IponConfig::PERIODIC_100_HZ_KEY_DEF_VAL = "100";

IponConfig::IponConfig(const std::string& confFilePath) {
    m_confFilePath = confFilePath;
    Init();
}

void IponConfig::SetConfDefaultValues() {
	m_conf->SetValue(UDP_IP_ADDRESS_KEY, UDP_IP_ADDRESS_DEF_VAL);
	m_conf->SetValue(UDP_PORT_KEY, UDP_PORT_DEF_VAL);
    m_conf->SetValue(TCP_PORT_KEY, TCP_PORT_DEF_VAL);
    m_conf->SetValue(PERIODIC_1_HZ_KEY, PERIODIC_1_HZ_KEY_DEF_VAL);
    m_conf->SetValue(PERIODIC_100_HZ_KEY, PERIODIC_100_HZ_KEY_DEF_VAL);
}

std::string IponConfig::GetProdName() const {
    return "IPON";
}

std::string IponConfig::GetUDPIPAdrress() const {
    return m_conf->GetValue<std::string>(UDP_IP_ADDRESS_KEY);
}

std::string IponConfig::GetUDPPort() const {
    return m_conf->GetValue<std::string>(UDP_PORT_KEY);
}

std::string IponConfig::GetTCPPort() const {
    return m_conf->GetValue<std::string>(TCP_PORT_KEY);
}

int IponConfig::GetPeriodic1MsgHertz() const {
    return m_conf->GetValue<int>(PERIODIC_1_HZ_KEY);
}

int IponConfig::GetPeriodic100MsgHertz() const {
    return m_conf->GetValue<int>(PERIODIC_100_HZ_KEY);
}