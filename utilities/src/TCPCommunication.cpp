/*
* TCPCommunication.cpp
* 
* Author: Binyamin Appelbaum
* Date: 15.02.18
* 
*/

#include "TCPCommunication.h"
#include "LoggerProxy.h"
#include <boost/asio.hpp> // boost::asio::io_service

TCPCommunication::TCPCommunication(const std::string& ipAddress, const std::string& port, boost::asio::io_service& io_service) : 
    m_port(port), m_ipAddress(ipAddress), m_socket(new tcp::socket(io_service)), m_acceptor(io_service, tcp::endpoint(tcp::v4(), std::stoi(port))) {
    try {
        m_acceptor.accept(*m_socket);
    }
    catch (std::exception& e) {
       ERRLOG << e.what() << "\n";
    }
}

bool TCPCommunication::Init() {
    return true;
}

int TCPCommunication::SendData(const char* buffer, int sizeOfData) {
    using namespace boost::asio;
    using boost::asio::ip::tcp;

    try {
        // writing the message for current time
        DBGLOG << "TCP server is going to write buffer with size: " << sizeOfData << "\n";
        boost::asio::write(*m_socket, boost::asio::buffer(buffer, sizeOfData));
    }
    catch (std::exception& e) {
       ERRLOG << e.what() << "\n";
       return 0;
    }

    return sizeOfData;

}