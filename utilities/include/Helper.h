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
    double dmod(double num, double mod);

    bool MakeDirectory(const std::string& dirName, mode_t mode);

    /**
     * Get current time with specific format
     * @param format - the format to get the time (for instance "%Y_%m_%d_%H_%M_%S" is 2017_11_27_14_37_43)
     * @return string of the desired format time
     */ 
    std::string GetFormattedTime(const std::string& format);

    void PrintToFile(const std::string& fileName, const std::string& text);

    /**
     * Sleep this time: maxTimeToSleep - (current_time - startTime). NOTE: sleep time is in microseconds!
     * @param startTime - start time of the sample
     * @param maxTimeToSleep - maximum time to sleep
     * @return string of the desired format time
     */ 
    void SleepForRestTime(boost::posix_time::ptime startTime, int maxTimeToSleep);
}

#endif // UTILITIES_H