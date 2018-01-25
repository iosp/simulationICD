/*
* RSCommunication.cpp
* 
* Author: Binyamin Appelbaum
* Date: 24.01.18
* 
*/

#include "RSCommunication.h"
#include "Logger.h"

RSCommunication::RSCommunication(const std::string& tty) : m_tty(tty) {
    Init();
}

bool RSCommunication::Init() {
    boost::asio::io_service io_service;
    boost::system::error_code ec;

    m_port = serial_port_ptr(new boost::asio::serial_port(io_service));
    m_port->open(m_tty.c_str(), ec);
 
    if (!m_port->is_open()) {
        LOG(_ERROR_, "unable to open port: " + ec.message());
        return false;
    }

    m_port->set_option(boost::asio::serial_port_base::baud_rate(115200));
    m_port->set_option(boost::asio::serial_port_base::character_size(8));
	m_port->set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
	m_port->set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
	m_port->set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
}

int RSCommunication::SendData(const char* buffer, int sizeOfData) const {
	int n = m_port->write_some(boost::asio::buffer(buffer, sizeOfData));
    return n;
}