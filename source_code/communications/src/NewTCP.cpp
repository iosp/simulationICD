/*
* NewTCP.cpp
*
* Author: Mor Eliyahu
* Date: 12.11.18
*/

#include "NewTCP.h"
#include "LoggerProxy.h"
//#include "Helper.h"
//#include <iostream>


int  CAN_VIEW_LOCAL_PORT_NUMBER = 30000;
char CAN_VIEW_IP_Number[20] = "192.168.0.101";

NewTCP::NewTCP(const std::string& CAN_VIEW_REMOTE_PORT_NUMBER) :
	m_port(CAN_VIEW_REMOTE_PORT_NUMBER) {

}

NewTCP::NewTCP() {

}
bool NewTCP::Init() {
	b_port_OK = false;
	UdpEth = NULL;

	if (UdpEth == NULL)
		UdpEth = new C_UDPutill();
	if (UdpEth != NULL)
		if (UdpEth->UDPutill_INIT(CAN_VIEW_LOCAL_PORT_NUMBER, m_port, CAN_VIEW_IP_Number, CAN_VIEW_IP_Number, SERVER) == true)
			b_port_OK = true;

	return(b_port_OK);
}

int NewTCP::SendData(const char* buffer, int sizeOfData) {
	
	if (!UdpEth->UDPutill_SEND((char*)buffer, sizeOfData)) {
		return 0;
	}

	return sizeOfData;
}

void NewTCP::GetData(char* buffer) {

	if ((UdpEth != NULL) && (UdpEth->UDPutill_RECEIVE((char *)buffer, INPUT_BUFFER_SIZE)));
	
	
}

