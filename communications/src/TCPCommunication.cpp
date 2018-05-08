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

TCPCommunication::TCPCommunication(const std::string& port) : 
    m_port(port){

}

bool TCPCommunication::Init() {
    try {
        boost::asio::io_service io_service;
        m_socket = std::make_shared<tcp::socket>(io_service);
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), std::stoi(m_port)));
        acceptor.accept(*m_socket);
    }
    catch (std::exception& e) {
       ERRLOG << e.what() << "\n";
       return false;
    }
    return true;
}

int TCPCommunication::SendData(const char* buffer, int sizeOfData) {
    using namespace boost::asio;
    using boost::asio::ip::tcp;

    try {
        // writing the message for current time
        LOG << "TCP server is going to write buffer with size: " << sizeOfData << "\n";
        boost::asio::write(*m_socket, boost::asio::buffer(buffer, sizeOfData));
    }
    catch (std::exception& e) {
       ERRLOG << e.what() << "\n";
       return 0;
    }

    return sizeOfData;
}