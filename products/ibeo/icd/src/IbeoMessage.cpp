/*
* IbeoMessage.cpp
* Ibeo message to send
* Author: Binyamin Appelbaum
* Date: 23.04.18
*/

#include "IbeoMessage.h"
#include "Helper.h" // Utilities::LittleEndianToBig
#include <boost/range/adaptor/reversed.hpp>

static const double PI = 3.14159265359;
static const double ANGLE_MULT = 11520 / (2*PI) ;

IbeoMessage::IbeoMessage(double tStartAngle, double tEndAngle, double bStartAngle, double bEndAngle, double angleIncrement) : 
	m_tStartAngle(tStartAngle), m_tEndAngle(tEndAngle), m_bStartAngle(bStartAngle),
	 m_bEndAngle(bEndAngle), m_angleIncrement(angleIncrement) {

}

void IbeoMessage::FillPoints(SibeoScanData& msg, unsigned char layerEcho, double startAngle, const std::vector<double>& ranges) {
	for (int i = 0; i < ranges.size(); i++) {
        msg.Point[m_pointCounter].Layer_Echo = layerEcho;
        msg.Point[m_pointCounter].Flags = 66;
        msg.Point[m_pointCounter].HorizontalAngel = (short)( (startAngle + m_angleIncrement * i) * ANGLE_MULT);
        msg.Point[m_pointCounter].RadialDistance = (unsigned short)(ranges[ranges.size() - i] * 100);
        msg.Point[m_pointCounter].EchoPulseWidth = 120;
        m_pointCounter++;
    }
}

void IbeoMessage::FillMessage(const IbeoData& data) {
	SibeoScanData msg;

    msg.Header.MagicWord = Utilities::LittleEndianToBig<int>(0xaffec0c2);//0xc2c0feaf;
	msg.Header.SizePreviousMessage = 0;
	msg.Header.SizeCurrentMessage = Utilities::LittleEndianToBig<unsigned int>((sizeof(SibeoScanData) + 
                                    (data.GetNumOfPoints()*sizeof(IbeoScanPoint))) - sizeof(ibeoScanDataHeader));

	msg.Header.DeviceID = 0;
	msg.Header.DataType = Utilities::LittleEndianToBig<unsigned short>(0x2202);
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

	msg.Scan.AnglesTicks = 11520; //(0.0023);
	msg.Scan.StartAngle = (short)(std::max(m_tStartAngle, m_bStartAngle) * ANGLE_MULT);
	msg.Scan.EndAngle = (short)(std::min(m_tEndAngle, m_bEndAngle) * ANGLE_MULT);

	msg.Scan.ScanPoints = data.GetRangeB1().size() + data.GetRangeB2().size() + data.GetRangeT1().size() + data.GetRangeT2().size();
	msg.Scan.PositionYaw = 0; //Reserved
	msg.Scan.PositionPitch = 0; //Reserved
	msg.Scan.PositionRoll = 0; //Reserved
	msg.Scan.PositionX = 0; //Reserved
	msg.Scan.PositionY = 0; //Reserved
	msg.Scan.Reserved = 0; //Reserved

	msg.Point = new IbeoScanPoint[data.GetNumOfPoints()];
    m_pointCounter = 0;

	FillPoints(msg, 0, m_bStartAngle, data.GetRangeB2());
	FillPoints(msg, 1, m_bStartAngle, data.GetRangeB1());
	FillPoints(msg, 2, m_tStartAngle, data.GetRangeT1());
	FillPoints(msg, 3, m_tStartAngle, data.GetRangeT2());

    memcpy(m_buffer, &msg, sizeof(SibeoScanData));
	delete msg.Point;
}

int IbeoMessage::GetMessageSize() const {
    return sizeof(SibeoScanData);
}