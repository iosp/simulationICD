#ifndef TCP_CLIENT_COMMUNICATION_H
#define TCP_CLIENT_COMMUNICATION_H

/*
* TCPClientCommunication.h
* 
* Author: Binyamin Appelbaum
* Date: 28.06.18
*/

#include "ICommunication.h"
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class TCPClientCommunication : public ICommunication {
private:
    std::string m_host;
    std::shared_ptr<tcp::socket> m_socket;
    bool m_initialized = false;
    boost::asio::io_service m_io_service;

    bool Connect();

public:
    TCPClientCommunication(const std::string& host);
    ~TCPClientCommunication() = default;

    bool Init() override;
    int SendData(const char* buffer, int sizeOfData) override;
    void GetData(char* buffer) override;
};



#endif // TCP_CLIENT_COMMUNICATION_H