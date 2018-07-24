/*
* TCPServerCommunication.cpp
* 
* Author: Binyamin Appelbaum
* Date: 15.02.18
*/

#include "TCPServerCommunication.h"
#include "LoggerProxy.h"

TCPServerCommunication::TCPServerCommunication(const std::string& port) : 
    m_port(port){

}

bool TCPServerCommunication::Init() {
    LOG << "Going to initialize TCP Server communication to port: " << m_port << "\n";
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
    LOG << "TCP server communication initialized successfully\n";
    return true;
}

int TCPServerCommunication::SendData(const char* buffer, int sizeOfData) {

    try {
        // writing the message for current time
        DBGLOG << "TCP server is going to write to port: " << m_port << ". buffer size: " << sizeOfData << "\n";
        boost::asio::write(*m_socket, boost::asio::buffer(buffer, sizeOfData));
    }
    catch (std::exception& e) {
       ERRLOG << e.what() << "\n";
       return 0;
    }

    return sizeOfData;
}