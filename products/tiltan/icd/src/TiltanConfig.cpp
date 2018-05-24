
/*
* TiltanConfig.cpp
* 
* Author: Binyamin Appelbaum
* Date: 12.02.18
* 
*/

#include "TiltanConfig.h"
#include "ConfigurationINI.h" // SetValue, GetValue

const std::string TiltanConfig::STATUS_MSG_PORT_KEY = "STATUS_MSG_PORT";
const std::string TiltanConfig::STATUS_MSG_PORT_DEF_VAL = "2001";

const std::string TiltanConfig::NAVIGATION_DATA_MSG_IP_ADDRESS_KEY = "NAVIGATION_DATA_MSG_IP";
const std::string TiltanConfig::NAVIGATION_DATA_MSG_IP_ADDRESS_DEF_VAL = "224.4.6.61";
const std::string TiltanConfig::NAVIGATION_DATA_MSG_PORT_KEY = "NAVIGATION_DATA_MSG_PORT";
const std::string TiltanConfig::NAVIGATION_DATA_MSG_PORT_DEF_VAL = "5010";

const std::string TiltanConfig::INTERNAL_GPS_MSG_IP_ADDRESS_KEY = "INTERNAL_GPS_MSG_IP";
const std::string TiltanConfig::INTERNAL_GPS_MSG_IP_ADDRESS_DEF_VAL = "224.4.6.60";
const std::string TiltanConfig::INTERNAL_GPS_MSG_PORT_KEY = "INTERNAL_GPS_MSG_PORT";
const std::string TiltanConfig::INTERNAL_GPS_MSG_PORT_DEF_VAL = "5000";

const std::string TiltanConfig::ERRORS_ESTIMATION_MSG_IP_ADDRESS_KEY = "ERRORS_ESTIMATION_MSG_IP";
const std::string TiltanConfig::ERRORS_ESTIMATION_MSG_IP_ADDRESS_DEF_VAL = "224.4.6.60";
const std::string TiltanConfig::ERRORS_ESTIMATION_MSG_PORT_KEY = "ERRORS_ESTIMATION_MSG_PORT";
const std::string TiltanConfig::ERRORS_ESTIMATION_MSG_PORT_DEF_VAL = "5000";

TiltanConfig::TiltanConfig(const std::string& confFilePath) : ProdConfig(confFilePath) {
    Init();
}

void TiltanConfig::SetConfDefaultValues() {
    m_conf->SetValue(STATUS_MSG_PORT_KEY, STATUS_MSG_PORT_DEF_VAL);

    m_conf->SetValue(NAVIGATION_DATA_MSG_IP_ADDRESS_KEY, NAVIGATION_DATA_MSG_IP_ADDRESS_DEF_VAL);
    m_conf->SetValue(NAVIGATION_DATA_MSG_PORT_KEY, NAVIGATION_DATA_MSG_PORT_DEF_VAL);

    m_conf->SetValue(INTERNAL_GPS_MSG_IP_ADDRESS_KEY, INTERNAL_GPS_MSG_IP_ADDRESS_DEF_VAL);
    m_conf->SetValue(INTERNAL_GPS_MSG_PORT_KEY, INTERNAL_GPS_MSG_PORT_DEF_VAL);

    m_conf->SetValue(ERRORS_ESTIMATION_MSG_IP_ADDRESS_KEY, ERRORS_ESTIMATION_MSG_IP_ADDRESS_DEF_VAL);
    m_conf->SetValue(ERRORS_ESTIMATION_MSG_PORT_KEY, ERRORS_ESTIMATION_MSG_PORT_DEF_VAL);
}

std::string TiltanConfig::GetProdName() const {
    return "Tiltan";
}

std::string TiltanConfig::GetStatusMsgPort() const {
    return m_conf->GetValue<std::string>(STATUS_MSG_PORT_KEY);
}

std::string TiltanConfig::GetNavigationDataMsgIpAddress() const {
    return m_conf->GetValue<std::string>(NAVIGATION_DATA_MSG_IP_ADDRESS_KEY);
}

std::string TiltanConfig::GetNavigationDataMsgPort() const {
    return m_conf->GetValue<std::string>(NAVIGATION_DATA_MSG_PORT_KEY);
}

std::string TiltanConfig::GetInternalGPSMsgIpAddress() const {
    return m_conf->GetValue<std::string>(INTERNAL_GPS_MSG_IP_ADDRESS_KEY);
}

std::string TiltanConfig::GetInternalGPSMsgPort() const {
    return m_conf->GetValue<std::string>(INTERNAL_GPS_MSG_PORT_KEY);
}

std::string TiltanConfig::GetErrorsEstimationMsgIpAddress() const {
    return m_conf->GetValue<std::string>(ERRORS_ESTIMATION_MSG_IP_ADDRESS_KEY);
}

std::string TiltanConfig::GetErrorsEstimationMsgPort() const {
    return m_conf->GetValue<std::string>(ERRORS_ESTIMATION_MSG_PORT_KEY);
}