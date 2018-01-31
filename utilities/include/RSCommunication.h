#ifndef RSCOMMUNICATION_H
#define RSCOMMUNICATION_H

/*
* RSCommunication.h
* 
* Author: Binyamin Appelbaum
* Date: 24.01.18
* 
*/

#include <boost/asio.hpp> // boost::asio::io_service
#include <boost/asio/serial_port.hpp>
#include "ICommunication.h"
#include <string>

typedef boost::shared_ptr<boost::asio::serial_port> serial_port_ptr;

class RSCommunication : public ICommunication {
private:
    // shared ptr of the port
    serial_port_ptr m_port;
    // baud rate of the RS communication
    int m_baudRate;
    // tty device number
    std::string m_tty;

public:
    RSCommunication(const std::string& tty, int baudRate);
    ~RSCommunication() = default;

    bool Init() override;
    int SendData(const char* buffer, int sizeOfData) const override;
};



#endif // RSCOMMUNICATION_H