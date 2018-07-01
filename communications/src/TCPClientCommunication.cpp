/*
* TCPClientCommunication.cpp
* 
* Author: Binyamin Appelbaum
* Date: 28.06.18
*/

#include "TCPClientCommunication.h"
#include "LoggerProxy.h"

TCPClientCommunication::TCPClientCommunication(const std::string& host): m_host(host) {
    // busy wait to init tcp communication
    while (true) {
        if (!Init()) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else {
            break;
        }
    }
}

bool TCPClientCommunication::Init() {
    m_socket = std::make_shared<tcp::socket>(m_io_service);
    if (!Connect()) {
        m_socket.reset();
        return false;
    }
    else {
        m_initialized = true;
        return true;
    }
}

bool TCPClientCommunication::Connect() {
    try {
        tcp::resolver resolver(m_io_service);
        tcp::resolver::query query(m_host, "daytime");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        boost::system::error_code error = boost::asio::error::host_not_found;

        boost::asio::connect(*m_socket, endpoint_iterator, error);
        if (error) {
            throw boost::system::system_error(error);
        }
        return true;
    }
    catch (std::exception& e) {
        ERRLOG << e.what() << "\n";
        return false;
    }
}

int TCPClientCommunication::SendData(const char* buffer, int sizeOfData) {
    if (!m_initialized) {
        return 0;
    }
    try {
        Connect();
        LOG << "TCP client is going to write to IP: " << m_host << ". buffer size: " << sizeOfData << "\n";
        boost::asio::write(*m_socket, boost::asio::buffer(buffer, sizeOfData));
        return sizeOfData;
    }
    catch (std::exception& e) {
        ERRLOG << e.what() << "\n";
    }
}

void TCPClientCommunication::GetData(char* buffer) {
    if (!m_initialized) {
        return;
    }
    try {
        Connect();
        std::array<char, 2048> buf;
        boost::system::error_code error;

        size_t len = boost::asio::read(*m_socket, boost::asio::buffer(buf), error);
        if (error == boost::asio::error::eof) {
            strcpy(buffer, buf.data());
            return;
        }
        else if (error) {
            throw boost::system::system_error(error);
        }
    }
    catch (std::exception& e) {
       ERRLOG << e.what() << "\n";
    }
}