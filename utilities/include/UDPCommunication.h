#ifndef UDPCOMMUNICATION_H
#define UDPCOMMUNICATION_H

/*
* UDPCommunication.h
* 
* Author: Binyamin Appelbaum
* Date: 25.01.18
* 
*/

#include "ICommunication.h"
#include <string>

class UDPCommunication : public ICommunication{
private:
    std::string m_ipAddress;
    std::string m_port;

public:
    UDPCommunication(const std::string& ipAddress, const std::string& port);
    ~UDPCommunication() = default;

    bool Init() override;
    int SendData(const char* buffer, int sizeOfData) const override;
};



#endif // UDPCOMMUNICATION_H