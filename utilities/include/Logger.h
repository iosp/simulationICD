#ifndef LOGGER_H
#define LOGGER_H

/*
* Logger.h
* Control log s
* Author: Binyamin Appelbaum
* Date: 27.11.17
* 
*/

#include <string>
#include <map>
#include <sstream>

enum LogLevel {_NONE_ = -1, _DEBUG_, _NORMAL_, _ERROR_, _ALWAYS_};

#define COL_PREFIX "\033["
#define RESET_COL COL_PREFIX"0m"
#define RED COL_PREFIX"31m"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) // print only file name, without path
#define LOG Logger::GetInstance()(_NORMAL_, __FILENAME__, __func__, __LINE__)
#define ERRLOG Logger::GetInstance()(_ERROR_, __FILENAME__, __func__, __LINE__)
#define DBGLOG Logger::GetInstance()(_DEBUG_, __FILENAME__, __func__, __LINE__)
#define ALWLOG Logger::GetInstance()(_ALWAYS_, __FILENAME__, __func__, __LINE__)

class Logger {
private:
    Logger(LogLevel screenLogLevel = _NORMAL_, LogLevel fileLogLevel = _NORMAL_);
    Logger(const Logger&) = default;
    ~Logger() = default;

    /**
     * temporary level of the current message
     */ 
    LogLevel m_tmpLevel;
    /**
     * screen log level for printing
     */ 
    LogLevel m_screenLogLevel;
    /**
     * file log level for printing
     */ 
    LogLevel m_fileLogLevel;
    /**
     * log destination file name
     */ 
    std::string m_logFileName;
    /**
     * log directory
     */ 
    std::string m_logDirName;
    /**
     * Print message to log file
     * @param message - string of the desired message to print
     */ 
    void PrintToFile(LogLevel level, const std::string& message) const;
    /**
     * Print message to stdout (screen)
     * @param message - string of the desired message to print
     */ 
    void PrintToScreen(LogLevel level, const std::string& message) const;

    template <typename T>
    std::string MarkMessageWithColor(const T& message, const std::string& color) const;

    static const std::string DEF_LOG_DIR_NAME;

    static const std::map<LogLevel, std::string> m_logLevelToStr;


public:
    static Logger& GetInstance();
    /**
     * operator () of class Logger
     * @param level -log level of the message (debug/normal/etc)
     * @param sourceFile - the cpp file that the message came from
     * @param funcName - function name that the nessage came from
     * @param lineNumber - the line where the message came from
     * @return instance of Logger class
     */ 
    Logger& operator () (LogLevel level, const std::string& sourceFile, const std::string& funcName, int lineNumber);

    /**
     * operator << of class Logger - implementation of template function must be on header file
     * @param message - the message body to print
     * @return instance of Logger class
     */     
    template <typename T>
    inline Logger& operator << (const T& msg) {
        std::stringstream ss;
        ss << msg;
        PrintToFile(m_tmpLevel, ss.str());
        PrintToScreen(m_tmpLevel, ss.str());
        return *this;
    }
};



#endif // LOGGER_H