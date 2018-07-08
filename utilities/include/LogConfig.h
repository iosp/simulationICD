#ifndef LOGCONFIG_H
#define LOGCONFIG_H

/*
* LogConfig.h
* 
* Author: Binyamin Appelbaum
* Date: 22.02.18
* 
*/

#include "ProdConfig.h"
#include <string>
#include <boost/bimap/bimap.hpp>

enum LogLevel {_NONE_ = -1, _DEBUG_, _NORMAL_, _ERROR_, _ALWAYS_};

class ConfigurationINI; // forward declaration

class LogConfig : public ProdConfig {
private:
    static const std::string SCREEN_LOG_LEVEL_KEY;
    static const std::string SCREEN_LOG_LEVEL_DEF_VAL;
    static const std::string FILE_LOG_LEVEL_KEY;
    static const std::string FILE_LOG_LEVEL_DEF_VAL;

    static const std::string LOG_DIR_NAME_KEY;
    static const std::string LOG_DIR_NAME_DEF_VAL;
    static const std::string DELETE_OLD_LOGS_KEY;
    static const std::string DELETE_OLD_LOGS_DEF_VAL;

    LogLevel GetLevelEnumByKey(const std::string& key) const;
 
protected:
    virtual void SetConfDefaultValues() override;

    virtual std::string GetProdName() const override;

public:

    LogConfig(const std::string& confFilePath);

    virtual ~LogConfig(){}

    LogLevel GetScreenLogLevel() const;

    LogLevel GetFileLogLevel() const;

    std::string GetLogDirName() const;

    bool DeleteOldLogs() const;

    static const boost::bimaps::bimap<LogLevel, std::string> m_logLevelToStr;
};



#endif // LOGCONFIG_H