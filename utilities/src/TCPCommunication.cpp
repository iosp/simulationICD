/*
* TCPCommunication.cpp
* 
* Author: Binyamin Appelbaum
* Date: 15.02.18
* 
*/

#include "TCPCommunication.h"
#include "Logger.h"
#include <boost/asio.hpp> // boost::asio::io_service

TCPCommunication::TCPCommunication(const std::string& ipAddress, const std::string& port) : m_port(port), m_ipAddress(ipAddress) {
}

bool TCPCommunication::Init() {
    return true;
}

int TCPCommunication::SendData(const char* buffer, int sizeOfData) const {
    using namespace boost::asio;
    using boost::asio::ip::tcp;

    try {
        // Any program that uses asio need to have at least one io_service object
        boost::asio::io_service io_service;

        // acceptor object needs to be created to listen for new connections
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), std::stoi(m_port)));

        // creates a socket
        tcp::socket socket(io_service);

        // wait and listen
        acceptor.accept(socket);

        boost::system::error_code ignored_error;

        // writing the message for current time
        boost::asio::write(socket, boost::asio::buffer(buffer, sizeOfData), ignored_error);
    }
    catch (std::exception& e) {
       LOG << e.what() << "\n";
    }

}