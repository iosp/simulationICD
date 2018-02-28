#ifndef LOGGER_H
#define LOGGER_H

/*
* Logger.h
* Control logs
* Author: Binyamin Appelbaum
* Date: 27.11.17
* 
*/

#include "LogConfig.h" // LogLevel
#include <string>
#include <map>
#include <sstream>
#include <cstring> // strrchr
#include <mutex>

#define COL_PREFIX "\033["
#define RESET_COL COL_PREFIX"0m"
#define RED COL_PREFIX"31m"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) // print only file name, without path
/** while using LOG macro - we are creating a temporary instance of LoggerProxy that gets the logger and a mutex as arguments
 * to the Ctor. operator << of LoogerProxy returns the same instance, and the result is sequence write of the line to the log 
 * In the end of the line - LoggerProxy instance is destroyed (because it is a temporary variable) and the mutex is released
*/ 
#define LOG LoggerProxy<std::mutex>(Logger::GetInstance(), Logger::GetLockObject(), _NORMAL_, __FILENAME__, __func__, __LINE__)
#define ERRLOG LoggerProxy<std::mutex>(Logger::GetInstance(), Logger::GetLockObject(), _ERROR_, __FILENAME__, __func__, __LINE__)
#define DBGLOG LoggerProxy<std::mutex>(Logger::GetInstance(), Logger::GetLockObject(), _DEBUG_, __FILENAME__, __func__, __LINE__)
#define ALWLOG LoggerProxy<std::mutex>(Logger::GetInstance(), Logger::GetLockObject(), _ALWAYS_, __FILENAME__, __func__, __LINE__)

class Logger {
private:
    Logger() = default;
    Logger(const Logger&) = default;
    ~Logger();

    LogConfig* m_logConf = nullptr;

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
    std::string m_logFilePath;
    /**
     * log directory
     */ 
    std::string m_logDirPath;

    void Init();
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

public:
    static Logger& GetInstance();

    static std::mutex& GetLockObject();

    /**
     * Write a message to destinations
     * @param msg - the message to write
     */ 
    template <typename T>
    inline void Write(const T& msg) {
        std::stringstream ss;
        ss << msg;
        PrintToFile(m_tmpLevel, ss.str());
        PrintToScreen(m_tmpLevel, ss.str());
    }

    /**
     * Write data of the message to log
     * @param level -log level of the message (debug/normal/etc)
     * @param sourceFile - the cpp file that the message came from
     * @param funcName - function name that the nessage came from
     * @param lineNumber - the line where the message came from
     */ 
    void Write(LogLevel level, const std::string& sourceFile, const std::string& funcName, int lineNumber);

    void SetTmpLevel(LogLevel level) {
        m_tmpLevel = level;
    }
};



#endif // LOGGER_H