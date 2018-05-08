
/*
* InsConfig.cpp
* 
* Author: Binyamin Appelbaum
* Date: 12.02.18
* 
*/

#include "InsConfig.h"
#include "LoggerProxy.h"
#include "ConfigurationINI.h"
#include <sstream>

const std::string InsConfig::STATUS_MSG_PORT_KEY = "STATUS_MSG_PORT";
const std::string InsConfig::STATUS_MSG_PORT_DEF_VAL = "2001";
const std::string InsConfig::STATUS_MSG_HZ_KEY = "STATUS_MSG_HERTZ";
const std::string InsConfig::STATUS_MSG_HZ_DEF_VAL = "1";

const std::string InsConfig::NAVIGATION_DATA_MSG_IP_ADDRESS_KEY = "NAVIGATION_DATA_MSG_IP";
const std::string InsConfig::NAVIGATION_DATA_MSG_IP_ADDRESS_DEF_VAL = "224.4.6.61";
const std::string InsConfig::NAVIGATION_DATA_MSG_PORT_KEY = "NAVIGATION_DATA_MSG_PORT";
const std::string InsConfig::NAVIGATION_DATA_MSG_PORT_DEF_VAL = "5010";
const std::string InsConfig::NAVIGATION_DATA_MSG_HZ_KEY = "NAVIGATION_DATA_MSG_HERTZ";
const std::string InsConfig::NAVIGATION_DATA_MSG_HZ_DEF_VAL = "50";

const std::string InsConfig::INTERNAL_GPS_MSG_IP_ADDRESS_KEY = "INTERNAL_GPS_MSG_IP";
const std::string InsConfig::INTERNAL_GPS_MSG_IP_ADDRESS_DEF_VAL = "224.4.6.60";
const std::string InsConfig::INTERNAL_GPS_MSG_PORT_KEY = "INTERNAL_GPS_MSG_PORT";
const std::string InsConfig::INTERNAL_GPS_MSG_PORT_DEF_VAL = "5000";
const std::string InsConfig::INTERNAL_GPS_MSG_HZ_KEY = "INTERNAL_GPS_MSG_HERTZ";
const std::string InsConfig::INTERNAL_GPS_MSG_HZ_DEF_VAL = "1";

const std::string InsConfig::ERRORS_ESTIMATION_MSG_IP_ADDRESS_KEY = "ERRORS_ESTIMATION_MSG_IP";
const std::string InsConfig::ERRORS_ESTIMATION_MSG_IP_ADDRESS_DEF_VAL = "224.4.6.60";
const std::string InsConfig::ERRORS_ESTIMATION_MSG_PORT_KEY = "ERRORS_ESTIMATION_MSG_PORT";
const std::string InsConfig::ERRORS_ESTIMATION_MSG_PORT_DEF_VAL = "5000";
const std::string InsConfig::ERRORS_ESTIMATION_MSG_HZ_KEY = "ERRORS_ESTIMATION_MSG_HERTZ";
const std::string InsConfig::ERRORS_ESTIMATION_MSG_HZ_DEF_VAL = "1";

InsConfig::InsConfig(const std::string& confFilePath) {
    m_confFilePath = confFilePath;
    Init();
}

void InsConfig::SetConfDefaultValues() {
    m_conf->SetValue(STATUS_MSG_PORT_KEY, STATUS_MSG_PORT_DEF_VAL);
    m_conf->SetValue(STATUS_MSG_HZ_KEY, STATUS_MSG_HZ_DEF_VAL);

    m_conf->SetValue(NAVIGATION_DATA_MSG_IP_ADDRESS_KEY, NAVIGATION_DATA_MSG_IP_ADDRESS_DEF_VAL);
    m_conf->SetValue(NAVIGATION_DATA_MSG_PORT_KEY, NAVIGATION_DATA_MSG_PORT_DEF_VAL);
    m_conf->SetValue(NAVIGATION_DATA_MSG_HZ_KEY, NAVIGATION_DATA_MSG_HZ_DEF_VAL);

    m_conf->SetValue(INTERNAL_GPS_MSG_IP_ADDRESS_KEY, INTERNAL_GPS_MSG_IP_ADDRESS_DEF_VAL);
    m_conf->SetValue(INTERNAL_GPS_MSG_PORT_KEY, INTERNAL_GPS_MSG_PORT_DEF_VAL);
    m_conf->SetValue(INTERNAL_GPS_MSG_HZ_KEY, INTERNAL_GPS_MSG_HZ_DEF_VAL);

    m_conf->SetValue(ERRORS_ESTIMATION_MSG_IP_ADDRESS_KEY, ERRORS_ESTIMATION_MSG_IP_ADDRESS_DEF_VAL);
    m_conf->SetValue(ERRORS_ESTIMATION_MSG_PORT_KEY, ERRORS_ESTIMATION_MSG_PORT_DEF_VAL);
    m_conf->SetValue(ERRORS_ESTIMATION_MSG_HZ_KEY, ERRORS_ESTIMATION_MSG_HZ_DEF_VAL);
}

std::string InsConfig::GetProdName() const {
    return "INS";
}

std::string InsConfig::GetStatusMsgPort() const {
    return m_conf->GetValue<std::string>(STATUS_MSG_PORT_KEY);
}

float InsConfig::GetStatusMsgHz() const {
    return m_conf->GetValue<float>(STATUS_MSG_HZ_KEY);
}

std::string InsConfig::GetNavigationDataMsgIpAddress() const {
    return m_conf->GetValue<std::string>(NAVIGATION_DATA_MSG_IP_ADDRESS_KEY);
}

std::string InsConfig::GetNavigationDataMsgPort() const {
    return m_conf->GetValue<std::string>(NAVIGATION_DATA_MSG_PORT_KEY);
}

float InsConfig::GetNavigationDataMsgHz() const {
    return m_conf->GetValue<float>(NAVIGATION_DATA_MSG_HZ_KEY);
}

std::string InsConfig::GetInternalGPSMsgIpAddress() const {
    return m_conf->GetValue<std::string>(INTERNAL_GPS_MSG_IP_ADDRESS_KEY);
}

std::string InsConfig::GetInternalGPSMsgPort() const {
    return m_conf->GetValue<std::string>(INTERNAL_GPS_MSG_PORT_KEY);
}

float InsConfig::GetInternalGPSMsgHz() const {
    return m_conf->GetValue<float>(INTERNAL_GPS_MSG_HZ_KEY);
}

std::string InsConfig::GetErrorsEstimationMsgIpAddress() const {
    return m_conf->GetValue<std::string>(ERRORS_ESTIMATION_MSG_IP_ADDRESS_KEY);
}

std::string InsConfig::GetErrorsEstimationMsgPort() const {
    return m_conf->GetValue<std::string>(ERRORS_ESTIMATION_MSG_PORT_KEY);
}

float InsConfig::GetErrorsEstimationMsgHz() const {
    return m_conf->GetValue<float>(ERRORS_ESTIMATION_MSG_HZ_KEY);
}