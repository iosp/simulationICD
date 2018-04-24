/*
* IbeoMessage.cpp
* Ibeo message to send
* Author: Binyamin Appelbaum
* Date: 23.04.18
*/

#include "IbeoMessage.h"
#include "Helper.h"
#include "ICommunication.h"
#include <boost/range/adaptor/reversed.hpp>

IbeoMessage::IbeoMessage(float hertz) : IMessage(hertz) {

}

void IbeoMessage::FillPoints(SibeoScanData& msg, unsigned char layerEcho, const std::vector<double>& ranges) {
    for (auto val : boost::adaptors::reverse(ranges)) {
        msg.Point[m_pointCounter].Layer_Echo = layerEcho;
        msg.Point[m_pointCounter].Flags = 66;
        // msg.Point[m_pointCounter].HorizontalAngel = ?;
        msg.Point[m_pointCounter].RadialDistance = (unsigned short)(val*100);
        msg.Point[m_pointCounter].EchoPulseWidth = 120;
        m_pointCounter++;
    }
}

void IbeoMessage::FillMessage(const IbeoData& data) {
	SibeoScanData msg;

    msg.Header.MagicWord = Utilities::littleEndianToBig<int>(0xaffec0c2);//0xc2c0feaf;
	msg.Header.SizePreviousMessage = 0;
	msg.Header.SizeCurrentMessage = Utilities::littleEndianToBig<unsigned int>((sizeof(SibeoScanData) + 
                                    (data.GetNumOfPoints()*sizeof(IbeoScanPoint))) - sizeof(ibeoScanDataHeader));

	msg.Header.DeviceID = 0;
	msg.Header.DataType = Utilities::littleEndianToBig<unsigned short>(0x2202);
	msg.Header.time_up = 0;	// NTP64
	msg.Header.time_down = 0;  // NTP64
	msg.Header.Reserved = 0; //Reserved

	msg.Scan.ScanNumber = 3;
	msg.Scan.ScannerStatus = 0x20;
	msg.Scan.SyncPhaseOffset = 0;//(1.0/_sensorT1->GetUpdateRate()/700);

	msg.Scan.ScanStratTimeDOWN = data.GetSimTime();
	msg.Scan.ScanStratTimeUP = data.GetSimTime();
	msg.Scan.ScanEndTimeDOWN = data.GetSimTime();
	msg.Scan.ScanEndTimeUP = data.GetSimTime();

	msg.Scan.AngelsTicks = 11520; //(0.0023);
	// msg.Scan.StartAngel = ?;
	// msg.Scan.EndAngel = ?;

	msg.Scan.ScanPoints = data.GetRangeB1().size() + data.GetRangeB2().size() + data.GetRangeT1().size() + data.GetRangeT2().size();
	msg.Scan.PositionYaw = 0; //Reserved
	msg.Scan.PositionPitch = 0; //Reserved
	msg.Scan.PositionRoll = 0; //Reserved
	msg.Scan.PositionX = 0; //Reserved
	msg.Scan.PositionY = 0; //Reserved
	msg.Scan.Reserved = 0; //Reserved

    m_pointCounter = 0;

	FillPoints(msg, 0, data.GetRangeB2());
	FillPoints(msg, 1, data.GetRangeB1());
	FillPoints(msg, 2, data.GetRangeT1());
	FillPoints(msg, 3, data.GetRangeT2());

    memcpy(m_buffer, &msg, sizeof(SibeoScanData));
}

int IbeoMessage::SendMessage(ICommunication* comm) const {
	return comm->SendData(m_buffer, GetMessageSize());
}

int IbeoMessage::GetMessageSize() const {
    return sizeof(SibeoScanData);
}

void IbeoMessage::InitMessage() {
    bzero(m_buffer, BUFFER_SIZE);
}