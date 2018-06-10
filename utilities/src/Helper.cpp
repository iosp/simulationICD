/**
* Helper.cpp
* Author: Binyamin Appelbaum
* Date: 3.12.17
*/

#include "Helper.h"
#include "LoggerProxy.h"
#include <sstream>
#include <fstream>
#include <thread> // std::this_thread::sleep_for
#include <csignal> // std::signal
#include <boost/filesystem.hpp> // boost::filesystem::create_directory
#include <cstdlib> // std::getenv
#include <stdio.h>

/******************************************************** File System **********************************************************/

void Utilities::MakeDirectory(const std::string& dirName) {
    boost::filesystem::path dir(dirName);
    boost::filesystem::create_directory(dir);
}

std::string Utilities::GetHomeDir() {
	static const int BUFFER_LEN = 1024;
	char homedir[BUFFER_LEN]{};
#ifdef __linux__
	snprintf(homedir, BUFFER_LEN, "%s", std::getenv("HOME"));
#elif __WIN32__
	snprintf(homedir, BUFFER_LEN, "%s%s", std::getenv("HOMEDRIVE"), std::getenv("HOMEPATH"));
#endif
    return (std::string)homedir;
}

bool Utilities::IsFileExists(const std::string& filePath) {
    std::ifstream f(filePath.c_str());
    return f.good();
}

int Utilities::GetFileSize(const std::string& filePath) {
    if (!IsFileExists(filePath)) {
        return 0;
    }

    std::ifstream file(filePath.c_str(), std::ifstream::in |std::ifstream::binary);
    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    file.close();

    return fileSize;
}

void Utilities::PrintToFile(const std::string& fileName, const std::string& text) {
    std::ofstream file(fileName, std::ios_base::app);
    file << text;
    file.close();
}

/******************************************************** Other **********************************************************/

std::string Utilities::GetFormattedTime(const std::string& format) {
    boost::posix_time::time_facet * facet = new boost::posix_time::time_facet(format.c_str());
    std::ostringstream stream;
    stream.imbue(std::locale(stream.getloc(), facet));
    stream << boost::posix_time::microsec_clock::local_time();
    return stream.str();
}

void Utilities::SleepForRestTime(boost::posix_time::ptime startTime, int maxTimeToSleep) {
	using namespace boost::posix_time;

	ptime endTime = microsec_clock::local_time();
	time_duration diff = endTime - startTime;
	int sleepTime = maxTimeToSleep - diff.total_microseconds();
	if (sleepTime > 0) {
		std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
	}
}

// TODO cross platform!!!
std::string Utilities::RunSystemCmd(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;
	std::shared_ptr<FILE> pipe;
    LOG << "Going to execute command: " << cmd << "\n";
#ifdef __linux__
	pipe = std::shared_ptr<FILE>(popen(cmd.c_str(), "r"), pclose);
#elif __WIN32__
	pipe = std::shared_ptr<FILE>(_popen(cmd.c_str(), "r"), _pclose);
#endif
    if (!pipe) {
        LOG << "popen() failed!\n";
    }
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr) {
            result += buffer.data();
        }
    }
    return result;
}

void StopHandler(int s){
    LOG << "User pressed ctrl + c, process is stopped\n";
    exit(1); 
}

// TODO cross platform!!!
void Utilities::AddStopHandler() {
	std::signal(SIGINT, StopHandler);
}

Utilities::FunctionLogWrapper::FunctionLogWrapper(const std::string& funcName) : m_funcName(funcName) {
    DBGLOG << "Enter " << m_funcName << "\n";
}

Utilities::FunctionLogWrapper::~FunctionLogWrapper(){
    DBGLOG << "Exit " << m_funcName << "\n";
}