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
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class TCPCommunication : public ICommunication {
private:
    std::string m_ipAddress;
    std::string m_port;
    std::shared_ptr<tcp::socket> m_socket;

public:
    TCPCommunication(const std::string& ipAddress, const std::string& port);
    ~TCPCommunication() = default;

    bool Init() override;
    int SendData(const char* buffer, int sizeOfData) override;
    virtual void GetData(char* buffer) override {}
};



#endif // TCPCOMMUNICATION_H