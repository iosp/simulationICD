
/*
* LogConfig.cpp
* 
* Author: Binyamin Appelbaum
* Date: 22.02.18
* 
*/

// need to undefine those macros - because using them cause infinite loop
#undef LOG
#undef ERRLOG
#undef DBGLOG
#undef ALWLOG

#include "LogConfig.h"
#include "ConfigurationINI.h"
#include <sstream>
#include <boost/assign.hpp> // boost::assign::map_list_of

const std::string LogConfig::SCREEN_LOG_LEVEL_KEY = "SCREEN_LOG_LEVEL";
const std::string LogConfig::SCREEN_LOG_LEVEL_DEF_VAL = "NORMAL";
const std::string LogConfig::FILE_LOG_LEVEL_KEY = "FILE_LOG_LEVEL";
const std::string LogConfig::FILE_LOG_LEVEL_DEF_VAL = "NORMAL";
const std::string LogConfig::LOG_DIR_NAME_KEY = "LOG_DIR_NAME";
const std::string LogConfig::LOG_DIR_NAME_DEF_VAL = "icd_log";
const std::string LogConfig::DELETE_OLD_LOGS_KEY = "DELETE_OLD_LOGS";
const std::string LogConfig::DELETE_OLD_LOGS_DEF_VAL = "0";

const boost::bimaps::bimap<LogLevel, std::string> LogConfig::m_logLevelToStr = 
    boost::assign::list_of<boost::bimaps::bimap<LogLevel, std::string>::relation>(_DEBUG_, "DEBUG")(_NORMAL_, "NORMAL")(_ERROR_, "ERROR")(_ALWAYS_, "ALWAYS");

LogConfig::LogConfig(const std::string& confFilePath) : ProdConfig(confFilePath) {
    // must call Init from derived class - because init calls pure virtual methods, that cannot be called from base Ctor
    Init();
}

void LogConfig::SetConfDefaultValues() {
    m_conf->SetValue(SCREEN_LOG_LEVEL_KEY, SCREEN_LOG_LEVEL_DEF_VAL);
    m_conf->SetValue(FILE_LOG_LEVEL_KEY, FILE_LOG_LEVEL_DEF_VAL);
    m_conf->SetValue(LOG_DIR_NAME_KEY, LOG_DIR_NAME_DEF_VAL);
    m_conf->SetValue(DELETE_OLD_LOGS_KEY, DELETE_OLD_LOGS_DEF_VAL);
}

std::string LogConfig::GetProdName() const {
    return "Log";
}

LogLevel LogConfig::GetLevelEnumByKey(const std::string& key) const {
    std::string val = m_conf->GetValue<std::string>(key);
    auto enumIt = m_logLevelToStr.right.find(val);
    if (enumIt != m_logLevelToStr.right.end()) {
        return enumIt->second;
    }
    else {
        return _NORMAL_;
    }
}

LogLevel LogConfig::GetScreenLogLevel() const {
    return GetLevelEnumByKey(SCREEN_LOG_LEVEL_KEY);
}

LogLevel LogConfig::GetFileLogLevel() const {
    return GetLevelEnumByKey(FILE_LOG_LEVEL_KEY);
}

std::string LogConfig::GetLogDirName() const {
    return m_conf->GetValue<std::string>(LOG_DIR_NAME_KEY);
}

bool LogConfig::DeleteOldLogs() const {
    return m_conf->GetValue<bool>(DELETE_OLD_LOGS_KEY);
}