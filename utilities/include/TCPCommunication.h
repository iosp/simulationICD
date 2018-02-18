#ifndef TCPCOMMUNICATION_H
#define TCPCOMMUNICATION_H

/*
* TCPCommunication.h
* 
* Author: Binyamin Appelbaum
* Date: 15.02.18
* 
*/

#include "ICommunication.h"
#include <string>

class TCPCommunication : public ICommunication {
private:
    std::string m_ipAddress;
    std::string m_port;

public:
    TCPCommunication(const std::string& ipAddress, const std::string& port);
    ~TCPCommunication() = default;

    bool Init() override;
    int SendData(const char* buffer, int sizeOfData) const override;
};



#endif // TCPCOMMUNICATION_H