#ifndef UTILITIES_H
#define UTILITIES_H

/**
* Helper.h
* Author: Binyamin Appelbaum
* Date: 3.12.17
*/

#include <sys/stat.h> // mode_t
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp> // boost::posix_time::ptime

namespace Utilities {

    /******************************************************** File System **********************************************************/

    /**
     * Make directory named "dirname" on file system
     * @param dirName - path and name of the directory
     * @param mode - permissions of the directory
     * @return true if succeeded and false O.W
     */ 
    bool MakeDirectory(const std::string& dirName, mode_t mode);

    /**
     * Get home directory path on file system
     * @return string of the path to home directory
     */ 
    std::string GetHomeDir();

    /**
     * Check if file path exists on file system
     * @param filePath - the path of the file on file system
     * @return true if file exists and false O.W
     */ 
    bool IsFileExists(const std::string& filePath);

    /**
     * Get file size in bytes
     * @param filePath - the path of the file on file system
     * @return number of bytes which the file takes on file system, and 0 if file does not exist
     */ 
    int GetFileSize(const std::string& filePath);

    /**
     * print text to file
     * @param fileName - the path of the file on file system
     * @param text - text to write to the file
     */ 
    void PrintToFile(const std::string& fileName, const std::string& text);

    /******************************************************** Other **********************************************************/
    
    /**
     * Get current time with specific format
     * @param format - the format to get the time (for instance "%Y_%m_%d_%H_%M_%S" is 2017_11_27_14_37_43)
     * @return string of the desired format time
     */ 
    std::string GetFormattedTime(const std::string& format);

    /**
     * Sleep this time: maxTimeToSleep - (current_time - startTime). NOTE: sleep time is in microseconds!
     * @param startTime - start time of the sample
     * @param maxTimeToSleep - maximum time to sleep
     * @return string of the desired format time
     */ 
    void SleepForRestTime(boost::posix_time::ptime startTime, int maxTimeToSleep);

    /**
     * Run bash command
     * @param cmd - the command to run
     * @return string of the command output
     */ 
    std::string RunSystemCmd(const std::string& cmd);

    /**
     * Add ctrl+c handler to process
     */ 
    void AddStopHandler();
}

#endif // UTILITIES_H