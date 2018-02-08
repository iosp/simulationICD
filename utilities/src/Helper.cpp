/**
* Helper.cpp
* Author: Binyamin Appelbaum
* Date: 3.12.17
*/

#include "Helper.h"
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

bool Utilities::MakeDirectory(const std::string& dirName, mode_t mode) {
    return (mkdir(dirName.c_str(), mode) == 0);
}

std::string Utilities::GetHomeDir() {
    const char *homedir = nullptr;
    if ((homedir = getenv("HOME")) == nullptr) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    return (std::string)homedir;
}

double Utilities::dmod(double num, double mod) {
    while (num > mod) {
        num -= mod;
    }
    return num;
}

std::string Utilities::GetFormattedTime(const std::string& format) {
    boost::posix_time::time_facet * facet = new boost::posix_time::time_facet(format.c_str());
    std::ostringstream stream;
    stream.imbue(std::locale(stream.getloc(), facet));
    stream << boost::posix_time::second_clock::local_time();
    return stream.str();
}

void Utilities::PrintToFile(const std::string& fileName, const std::string& text) {
    std::ofstream file(fileName, std::ios_base::app);
    file << text;
    file.close();
}


void Utilities::SleepForRestTime(boost::posix_time::ptime startTime, int maxTimeToSleep) {
	using namespace boost::posix_time;

	ptime endTime = microsec_clock::local_time();
	time_duration diff = endTime - startTime;
	int sleepTime = maxTimeToSleep - diff.total_microseconds();
	if (sleepTime > 0) {
		usleep(sleepTime);
	}
}