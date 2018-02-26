/**
* Logger.cpp
* 
* Author: Binyamin Appelbaum
* Date: 27.11.17
*/

#include <sstream>
#include <iostream>
#include "Logger.h"
#include "Helper.h"

Logger::~Logger() {
    delete m_logConf;
}

void Logger::Init() {
    m_logConf = new LogConfig(Utilities::GetHomeDir() + "/confFiles/log.conf");
    m_screenLogLevel = m_logConf->GetScreenLogLevel();
    m_fileLogLevel = m_logConf->GetFileLogLevel();
    m_logDirPath = Utilities::GetHomeDir() + "/" + m_logConf->GetLogDirName() + "/";
    Utilities::MakeDirectory(m_logDirPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    m_logFilePath = m_logDirPath + "icd_" + Utilities::GetFormattedTime("%Y_%m_%d_%H_%M_%S") + ".log";
}

Logger& Logger::GetInstance() {
    static bool isInitialized = false;
    static Logger l;
    if (!isInitialized) {
        isInitialized = true;
        l.Init();
    }
    return l;
}

void Logger::Write(LogLevel level, const std::string& sourceFile, const std::string& funcName, int lineNumber) {
    std::stringstream ss;
    ss << Utilities::GetFormattedTime("%d.%m.%y %H:%M:%S") << "::" << sourceFile << "(" << lineNumber << ")::" <<
            funcName << "::(*" << LogConfig::m_logLevelToStr.left.find(level)->second.front() << "*) ";
    PrintToFile(level, ss.str());
    PrintToScreen(level, ss.str());
}

void Logger::PrintToFile(LogLevel level, const std::string& message) const {
    if (level >= m_fileLogLevel) {
        Utilities::PrintToFile(m_logFilePath, message);
    }
}

void Logger::PrintToScreen(LogLevel level, const std::string& message) const {
    // error messages are displayed in red
    std::string msgToDisp = message;
    if (level < m_screenLogLevel) {
        return;
    }
    if (level == _ERROR_) {
        msgToDisp = MarkMessageWithColor(message, RED);
    }
    std::cout << msgToDisp;
}

template <typename T>
std::string Logger::MarkMessageWithColor(const T& message, const std::string& color) const {
    std::stringstream ss;
    ss << color << message << RESET_COL;
    return ss.str();
}


std::mutex& Logger::GetLockObject() {
    static std::mutex lockObj;
    return lockObj;
}