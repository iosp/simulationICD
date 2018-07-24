/*
* ConfigurationINI.cpp
* INI configuration (key-value)
* Author: Binyamin Appelbaum
* Date: 07.02.18
*/

#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp> // trim
#include "ConfigurationINI.h"

ConfigurationINI::ConfigurationINI(const std::string& filePath) : m_filePath(filePath) {
}

void ConfigurationINI::ParseConfFile() {
    static const std::string DELIMITER = "=";

    std::ifstream confFile(m_filePath.c_str());
    if (!confFile.is_open()) {
        ERRLOG << "Failed to open file: " << m_filePath << "\n";
        return;
    }

    // read file line by line
    std::string line;
    while (getline(confFile, line)) {
        // valid line: KEY=VALUE
        if (line.find(DELIMITER) == std::string::npos) {
            ERRLOG << "Line " << line << " is not valid!\n";
            continue;
        }
        std::string key = line.substr(0, line.find(DELIMITER));
        std::string value = line.substr(line.find(DELIMITER) + 1);
        boost::trim(key); // ignore white spaces
        boost::trim(value); // ignore white spaces
        SetValue(key, value);
    }
}

void ConfigurationINI::SetValue(const std::string& key, const std::string& val) {
    m_confMap[key] = val;
}

std::string ConfigurationINI::toString() const {
    std::stringstream ss;
    for (auto kv: m_confMap) {
        ss << kv.first << " : |" << kv.second << "|" << std::endl;
    }
    return ss.str();
}