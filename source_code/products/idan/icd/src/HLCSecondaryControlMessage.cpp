/*
* HLCSecondaryControlMessage.cpp
* HLC secondary message to send
* Author: Binyamin Appelbaum
* Date: 26.03.18
*/

#include "HLCSecondaryControlMessage.h"
#include "IdanData.h"
#include "LoggerProxy.h"
#include "Helper.h" // GetValFromMap
#include <boost/assign.hpp> // boost::assign::map_list_of

const std::map<unsigned char, std::string> GearToStr = 
            boost::assign::map_list_of(0x02, "R")(0x03, "N")(0x04, "DR")(0xF1, "U")(0xF2, "DO");
static const unsigned char PARKING_RELEASED = 0x01;
static const unsigned char SACS_ON_VAL = 0x0B;

HLCSecondaryControlMessage::HLCSecondaryControlMessage(float hertz, bool isCanView) : IdanMessageGet(hertz) {
    m_isCanView = isCanView;
}

void HLCSecondaryControlMessage::ParseMessage(const char* buffer) {
    int offset = m_isCanView ? CAN_VIEW_DATA_OFFSET : CAN_REG_DATA_OFFSET;
    buffer = buffer + offset;
    m_message.ShutDown = buffer[0];

    m_message.W1.RoadLight = buffer[1] & 1;
	m_message.W1.HighBeam = (buffer[1] >> 1) & 1;
	m_message.W1.LightCutoff = (buffer[1] >> 2) & 1;
	m_message.W1.ParkingLight = (buffer[1] >> 3) & 1;
	
	m_message.W2.KeySwitch = buffer[2] & 1;
	m_message.W2.MotorStarter = (buffer[2] >> 1) & 1;
	m_message.W2.Horn = (buffer[2] >> 2) & 1;
	m_message.W2.LeftTurnSig = (buffer[2] >> 3) & 1;
	m_message.W2.RightTurnSig = (buffer[2] >> 4) & 1;
	m_message.W2.Hazards = (buffer[2] >> 5) & 1;
    
	m_message.Gear = buffer[3];
    m_message.ParkingBrake = buffer[4];
    m_message.EmergencyCmd = buffer[5];
    m_message.SacsOnCmd = buffer[7];
}

void HLCSecondaryControlMessage::UpdateData(IdanData& data) const {
	data.SetHLCSShutDownCmd(m_message.ShutDown == SHUTDOWN_VAL);
	data.SetHLCSRoadLights(m_message.W1.RoadLight);
	data.SetHLCSHighBeam(m_message.W1.HighBeam);
	data.SetHLCSLightsCutoff(m_message.W1.LightCutoff);
	data.SetHLCSParkingLight(m_message.W1.ParkingLight);
	
	data.SetHLCSKeySwitch(m_message.W2.KeySwitch);
	data.SetHLCSMotorStarter(m_message.W2.MotorStarter);
	data.SetHLCSHorn(m_message.W2.Horn);
	data.SetHLCSLeftTurnSignal(m_message.W2.LeftTurnSig);
	data.SetHLCSRightTurnSignal(m_message.W2.RightTurnSig);
	data.SetHLCSHazards(m_message.W2.Hazards);

	//data.SetHLCSGear(Utilities::GetValFromMap(GearToStr, m_message.Gear, (std::string)"N")); // def val: Nuetral);
	data.SetHLCSGearChar(m_message.Gear);
	data.SetHLCSParkingBrake(m_message.ParkingBrake == PARKING_RELEASED);
	data.SetHLCSEmergencyCmd(m_message.EmergencyCmd == EMERGENCY_VAL);
	data.SetHLCSSacsOnCmd(m_message.SacsOnCmd == SACS_ON_VAL);

	DBGLOG << "Data accepted: " << data.toString(HLC_SECONDARY);
}

t_msgID HLCSecondaryControlMessage::GetMsgID() const {
    return HLC_SEC_ID;
}