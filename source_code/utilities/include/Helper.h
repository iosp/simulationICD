#ifndef UTILITIES_H
#define UTILITIES_H

/**
* Helper.h
* Author: Binyamin Appelbaum
* Date: 3.12.17
*/

#include <string>
#include <boost/date_time/posix_time/posix_time.hpp> // boost::posix_time::ptime
#include <boost/filesystem.hpp> // boost::filesystem::perms

namespace Utilities {

    /******************************************************** File System **********************************************************/

    /**
     * Make directory named "dirname" on file system
     * @param dirName - path and name of the directory
     * @param permissions of the directory
     */ 
    void MakeDirectory(const std::string& dirName, boost::filesystem::perms prms);

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

    template <typename T>
    T LittleEndianToBig(T u) {
        union {
            T u;
            unsigned char u8[sizeof(T)];
        } source, dest;
        source.u = u;
        for (size_t k = 0; k < sizeof(T); k++) {
            dest.u8[k] = source.u8[sizeof(T)-k-1];
        }
        return dest.u;
    }

    // get appropriate val from m by the key
	template <class T, class U>
	U GetValFromMap(const std::map<T, U>& m, const T& key, const U& defVal) {
		auto it = m.find(key);
		auto val = (it != m.end() ? it->second : defVal);
		return val;
	}

    /**
     * copy string - cross platform method
     * @param dst - destination to copy
     * @param src - string to copy
     * @param len - length of the string
     */ 
	void StrcpyCrossPlatform(char* dst, const char* src, int len);
   
    /**
     * Add ctrl+c handler to process
     */ 
    void AddStopHandler();

    /** For logging and debugging - the purpose of this feature is to trace enter and exit from a function
     * Someone creates a local instance of the class, the ctor of the class writes that we enter to the function
     * and the dtor (when going out from the function) writes that we exit from the function.
     */ 
    class FunctionLogWrapper {
    private:
        std::string m_funcName;
    public:
        FunctionLogWrapper(const std::string& funcName);
        ~FunctionLogWrapper();
    };
}

#endif // UTILITIES_H