#ifndef NEW_TCP_H
#define NEW_TCP_H

/*
* NewTCP.h
*
* Author: Mor Eliyahu
* Date: 12.11.18
*
*/
#ifdef _WIN32
	#include "ICommunication.h"
	#include <string>
	#include "UDPutil.h"


	#define NO_RCV_DATA_MAX_COUNTER	10 
	#define INPUT_BUFFER_SIZE		1000

	class NewTCP : public ICommunication {
	private:
		std::string m_port;
		C_UDPutill *UdpEth;
		bool b_port_OK;

	public:
		NewTCP(const std::string& CAN_VIEW_REMOTE_PORT_NUMBER);
		NewTCP();
		~NewTCP() = default;

		bool Init() override;
		int SendData(const char* buffer, int sizeOfData) override;
		virtual void GetData(char* buffer) override;// {}

	};
#endif

#endif  //NEW_TCP_H