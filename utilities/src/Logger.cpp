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

static const long MAX_FILE_SIZE = 209715200; // 200 MB

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
    m_basicLogFilePath = m_logFilePath;
}

Logger& Logger::GetInstance() {
    static bool isInitialized = false;
    static Logger l;
    // we need to make GetInstance method like this - because initializing logger on the ctor - may cause infinite loop.
    // see https://stackoverflow.com/questions/48927570/constructors-infinite-cycle-in-cpp
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

void Logger::PrintToFile(LogLevel level, const std::string& message) {
    static int suffix = 1;
    if (level >= m_fileLogLevel) {
        // if current file size is over the limit - create new file with new suffix
        if (Utilities::GetFileSize(m_logFilePath) > MAX_FILE_SIZE) {
            m_logFilePath = m_basicLogFilePath + "_" + std::to_string(suffix++);
        }
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