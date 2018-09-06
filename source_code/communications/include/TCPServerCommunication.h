#ifndef TCP_SERVER_COMMUNICATION_H
#define TCP_SERVER_COMMUNICATION_H

/*
* TCPServerCommunication.h
* 
* Author: Binyamin Appelbaum
* Date: 15.02.18
* 
*/

#include "ICommunication.h"
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class TCPServerCommunication : public ICommunication {
private:
    std::string m_port;
    std::shared_ptr<tcp::socket> m_socket;
    boost::asio::io_service io_service;

public:
    TCPServerCommunication(const std::string& port);
    ~TCPServerCommunication() = default;

    bool Init() override;
    int SendData(const char* buffer, int sizeOfData) override;
    virtual void GetData(char* buffer) override {}
};



#endif // TCP_SERVER_COMMUNICATION_H