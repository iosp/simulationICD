
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
const std::string LogConfig::LOG_DIR_NAME_DEF_VAL = "icd";

const boost::bimaps::bimap<LogLevel, std::string> LogConfig::m_logLevelToStr = 
    boost::assign::list_of<boost::bimaps::bimap<LogLevel, std::string>::relation>(_DEBUG_, "DEBUG")(_NORMAL_, "NORMAL")(_ERROR_, "ERROR")(_ALWAYS_, "ALWAYS");

LogConfig::LogConfig(const std::string& confFilePath) {
    m_logConf = new ConfigurationINI(confFilePath);
    SetConfDefaultValues();
    m_logConf->ParseConfFile();
}

LogConfig::~LogConfig() {
    delete m_logConf;
}

void LogConfig::SetConfDefaultValues() {
    m_logConf->SetValue(SCREEN_LOG_LEVEL_KEY, SCREEN_LOG_LEVEL_DEF_VAL);
    m_logConf->SetValue(FILE_LOG_LEVEL_KEY, FILE_LOG_LEVEL_DEF_VAL);
    m_logConf->SetValue(LOG_DIR_NAME_KEY, LOG_DIR_NAME_DEF_VAL);
}

LogLevel LogConfig::GetLevelEnumByKey(const std::string& key) const {
    std::string val = m_logConf->GetValue<std::string>(key);
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
    return m_logConf->GetValue<std::string>(LOG_DIR_NAME_KEY);
}