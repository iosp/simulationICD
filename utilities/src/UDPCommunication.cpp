/*
* UDPCommunication.cpp
* 
* Author: Binyamin Appelbaum
* Date: 24.01.18
* 
*/

#include "UDPCommunication.h"
#include "LoggerProxy.h"
#include <boost/asio.hpp> // boost::asio::io_service

UDPCommunication::UDPCommunication(const std::string& ipAddress, const std::string& port) : m_port(port), m_ipAddress(ipAddress) {
}

bool UDPCommunication::Init() {
    return true;
}

int UDPCommunication::SendData(const char* buffer, int sizeOfData) const {
    using namespace boost::asio;

    boost::asio::io_service io_service;
    ip::udp::socket socket(io_service);
    socket.open(ip::udp::v4());
    ip::udp::endpoint remote_endpoint = ip::udp::endpoint(ip::address::from_string(m_ipAddress), std::stoi(m_port));
    // set the ip address of the configuration
    remote_endpoint.address(ip::address::from_string(m_ipAddress));
    boost::system::error_code err;
    DBGLOG << "UDP server is going to write buffer with size: " << sizeOfData << "\n";
    socket.send_to(boost::asio::buffer(buffer, sizeOfData), remote_endpoint, 0, err);
    if (err.value() != boost::system::errc::success) {
        ERRLOG << "Failed to send packet. " << err.message() << "\n";
        socket.close();
        return 0;
    }
    socket.close();
    return sizeOfData;
}