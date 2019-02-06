
/*
* IdanConfig.cpp
* 
* Author: Binyamin Appelbaum
* Date: 20.03.18
* 
*/

#include "IdanConfig.h"
#include "ConfigurationINI.h"

const std::string IdanConfig::INTERFACE_NAME_KEY = "IFACE_NAME";
const std::string IdanConfig::INTERFACE_NAME_DEF_VAL = "can0";
const std::string IdanConfig::IS_VIRTUAL_INTERFACE_KEY = "IS_VIRTUAL_INTERFACE";
const std::string IdanConfig::IS_VIRTUAL_INTERFACE_DEF_VAL = "0";
const std::string IdanConfig::IS_CANVIEW_KEY = "IS_CANVIEW";
#ifdef _WIN32
    const std::string IdanConfig::IS_CANVIEW_DEF_VAL = "1";
#else
    const std::string IdanConfig::IS_CANVIEW_DEF_VAL = "0";
#endif
const std::string IdanConfig::CAN_BAUD_RATE_KEY = "CAN_BAUD_RATE";
const std::string IdanConfig::CAN_BAUD_RATE_DEF_VAL = "500000";
const std::string IdanConfig::HLC_HERTZ_KEY = "HLC_HERTZ";
const std::string IdanConfig::HLC_HERTZ_DEF_VAL = "50";
const std::string IdanConfig::TCP_PORT_KEY = "TCP_PORT";
const std::string IdanConfig::TCP_PORT_DEF_VAL = "30000";

IdanConfig::IdanConfig(const std::string& confFilePath) : ProdConfig(confFilePath)  {
    LOG << "Initializing idan configurations\n";
    Init();
}

void IdanConfig::SetConfDefaultValues() {
	m_conf->SetValue(INTERFACE_NAME_KEY, INTERFACE_NAME_DEF_VAL);
    m_conf->SetValue(IS_VIRTUAL_INTERFACE_KEY, IS_VIRTUAL_INTERFACE_DEF_VAL);
    m_conf->SetValue(IS_CANVIEW_KEY, IS_CANVIEW_DEF_VAL);
    m_conf->SetValue(CAN_BAUD_RATE_KEY, CAN_BAUD_RATE_DEF_VAL);
    m_conf->SetValue(HLC_HERTZ_KEY, HLC_HERTZ_DEF_VAL);
    m_conf->SetValue(TCP_PORT_KEY, TCP_PORT_DEF_VAL);
}

std::string IdanConfig::GetProdName() const {
    return "IDAN";
}

std::string IdanConfig::GetInterfaceName() const {
    return m_conf->GetValue<std::string>(INTERFACE_NAME_KEY);
}

int IdanConfig::GetBaudRate() const {
    return m_conf->GetValue<int>(CAN_BAUD_RATE_KEY);
}

float IdanConfig::GetHLCHertz() const {
    return m_conf->GetValue<float>(HLC_HERTZ_KEY);
}

bool IdanConfig::IsVirtualInterface() const {
    return m_conf->GetValue<bool>(IS_VIRTUAL_INTERFACE_KEY);
}

bool IdanConfig::IsCanView() const {
    return m_conf->GetValue<bool>(IS_CANVIEW_KEY);
}

std::string IdanConfig::GetTCPPort() const {
    return m_conf->GetValue<std::string>(TCP_PORT_KEY);
}