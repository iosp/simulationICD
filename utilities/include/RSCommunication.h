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

typedef boost::shared_ptr<boost::asio::serial_port> serial_port_ptr;

class RSCommunication : public ICommunication {
private:
    serial_port_ptr m_port;
    int m_baudRate;
    std::string m_tty;

public:
    RSCommunication(const std::string& tty, int baudRate);
    ~RSCommunication() = default;

    bool Init() override;
    int SendData(const std::string& buffer) const override;
};



#endif // RSCOMMUNICATION_H