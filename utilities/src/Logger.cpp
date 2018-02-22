/**
* Logger.cpp
* 
* Author: Binyamin Appelbaum
* Date: 27.11.17
*/

#include "Logger.h"
#include "Helper.h"
#include <boost/assign.hpp> // boost::assign::map_list_of
#include <sstream>
#include <iostream>

const std::map<LogLevel, std::string> Logger::m_logLevelToStr = boost::assign::map_list_of(_DEBUG_, "D")(_NORMAL_, "N")(_ERROR_, "E")(_ALWAYS_, "A");
const std::string Logger::DEF_LOG_DIR_NAME = "/icd/";


Logger::Logger(LogLevel screenLogLevel/* = _NORMAL_*/, LogLevel fileLogLevel /** = _NORMAL_ */) :
     m_screenLogLevel(screenLogLevel), m_fileLogLevel(fileLogLevel){
        m_logDirName = Utilities::GetHomeDir() + DEF_LOG_DIR_NAME;
        Utilities::MakeDirectory(m_logDirName, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        m_logFileName = m_logDirName + "icd_" + Utilities::GetFormattedTime("%Y_%m_%d_%H_%M_%S") + ".log";
}

Logger& Logger::GetInstance() {
    static Logger l;
    return l;
}

void Logger::WriteMsgPrefix(LogLevel level, const std::string& sourceFile, const std::string& funcName, int lineNumber) {
    std::stringstream ss;
    ss << Utilities::GetFormattedTime("%d.%m.%y %H:%M:%S") << "::" << sourceFile << "(" << lineNumber << ")::" <<
            funcName << "::(*" << m_logLevelToStr.find(level)->second << "*) ";
    PrintToFile(level, ss.str());
    PrintToScreen(level, ss.str());
}

void Logger::PrintToFile(LogLevel level, const std::string& message) const {
    if (level >= m_fileLogLevel) {
        Utilities::PrintToFile(m_logFileName, message);
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