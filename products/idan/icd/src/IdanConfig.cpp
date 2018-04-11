
/*
* IdanConfig.cpp
* 
* Author: Binyamin Appelbaum
* Date: 20.03.18
* 
*/

#include "IdanConfig.h"
#include "LoggerProxy.h"
#include "ConfigurationINI.h"
#include <sstream>

const std::string IdanConfig::INTERFACE_NAME_KEY = "IFACE_NAME";
const std::string IdanConfig::INTERFACE_NAME_DEF_VAL = "vcan0";
const std::string IdanConfig::IS_VIRTUAL_INTERFACE_KEY = "IS_VIRTUAL_INTERFACE";
const std::string IdanConfig::IS_VIRTUAL_INTERFACE_DEF_VAL = "0";
const std::string IdanConfig::CAN_BAUD_RATE_KEY = "CAN_BAUD_RATE";
const std::string IdanConfig::CAN_BAUD_RATE_DEF_VAL = "500000";
const std::string IdanConfig::HLC_HERTZ_KEY = "HLC_HERTZ";
const std::string IdanConfig::HLC_HERTZ_DEF_VAL = "50";
const std::string IdanConfig::IDAN_PRIM_HERTZ_KEY = "IDAN_PRIM_HERTZ";
const std::string IdanConfig::IDAN_PRIM_HERTZ_DEF_VAL = "100";
const std::string IdanConfig::IDAN_SEC_REP_HERTZ_KEY = "IDAN_SEC_REP_HERTZ";
const std::string IdanConfig::IDAN_SEC_REP_HERTZ_DEF_VAL = "10";
const std::string IdanConfig::IDAN_SEC_SEN_HERTZ_KEY = "IDAN_SEC_SEN_HERTZ";
const std::string IdanConfig::IDAN_SEC_SEN_HERTZ_DEF_VAL = "1";

IdanConfig::IdanConfig(const std::string& confFilePath) {
    m_idanConf = new ConfigurationINI(confFilePath);
    SetConfDefaultValues();
    m_idanConf->ParseConfFile();

    LOG << "Idan configuration is:\n" << m_idanConf->toString() << "\n";

}

IdanConfig::~IdanConfig() {
    delete m_idanConf;
}

void IdanConfig::SetConfDefaultValues() {
	m_idanConf->SetValue(INTERFACE_NAME_KEY, INTERFACE_NAME_DEF_VAL);
    m_idanConf->SetValue(IS_VIRTUAL_INTERFACE_KEY, IS_VIRTUAL_INTERFACE_DEF_VAL);
    m_idanConf->SetValue(CAN_BAUD_RATE_KEY, CAN_BAUD_RATE_DEF_VAL);
    m_idanConf->SetValue(HLC_HERTZ_KEY, HLC_HERTZ_DEF_VAL);
    m_idanConf->SetValue(IDAN_PRIM_HERTZ_KEY, IDAN_PRIM_HERTZ_DEF_VAL);
    m_idanConf->SetValue(IDAN_SEC_REP_HERTZ_KEY, IDAN_SEC_REP_HERTZ_DEF_VAL);
    m_idanConf->SetValue(IDAN_SEC_SEN_HERTZ_KEY, IDAN_SEC_SEN_HERTZ_DEF_VAL);
}

std::string IdanConfig::GetInterfaceName() const {
    return m_idanConf->GetValue<std::string>(INTERFACE_NAME_KEY);
}

int IdanConfig::GetBaudRate() const {
    return m_idanConf->GetValue<int>(CAN_BAUD_RATE_KEY);
}

int IdanConfig::GetHLCHertz() const {
    return m_idanConf->GetValue<int>(HLC_HERTZ_KEY);
}

int IdanConfig::GetIdanPrimHertz() const {
    return m_idanConf->GetValue<int>(IDAN_PRIM_HERTZ_KEY);
}

int IdanConfig::GetIdanSecRepHertz() const {
    return m_idanConf->GetValue<int>(IDAN_SEC_REP_HERTZ_KEY);
}

int IdanConfig::GetIdanSecSenHertz() const {
    return m_idanConf->GetValue<int>(IDAN_SEC_SEN_HERTZ_KEY);
}

bool IdanConfig::IsVirtualInterface() const {
    return m_idanConf->GetValue<bool>(IS_VIRTUAL_INTERFACE_KEY);
}