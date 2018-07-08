/*
* IdanSecondaryReportMessage.cpp
* Idan secondary message to send
* Author: Binyamin Appelbaum
* Date: 26.03.18
*/

#include "IdanSecondaryReportMessage.h"
#include "IdanData.h"
#include "LoggerProxy.h"
#include "Helper.h" // GetValFromMap
#include <boost/assign.hpp> // boost::assign::map_list_of

const std::map<std::string, unsigned char> StrToGear = 
            boost::assign::map_list_of("R", 0x02)("N",0x03)("D1", 0x04)("D2", 0x05)("D3", 0x06)("D4", 0x07)("D5", 0x08)("PROG", 0xD);
const std::map<std::string, unsigned char> StrToPark = 
            boost::assign::map_list_of("R", 0x01)("E",0x02)("P", 0x0D);

IdanSecondaryReportMessage::IdanSecondaryReportMessage(bool isCanView) {
    m_isCanView = isCanView;
}

int IdanSecondaryReportMessage::GetMessageSize() const {
    return sizeof(IDAN_SecondaryReportMsgType);
}

void IdanSecondaryReportMessage::FillMessage(const IdanData& data) {
    IDAN_SecondaryReportMsgType msg;

    msg.W0.Disc1 = 0;
    msg.W0.Disc2 = 0;
    msg.W0.Disc3 = 0;
    msg.W0.SACSactive = 0;

    msg.W1.RoadLight = data.IsIdanSecRepRoadLightsApplied();
    msg.W1.HighBeam = data.IsIdanSecRepHighBeamApplied();
    msg.W1.LightCutoff = data.IsIdanSecRepLightsCutoffApplied();

    msg.W2.KeySwitch = data.IsIdanSecRepKeySwitchApplied();
    msg.W2.MotorStarter = data.IsIdanSecRepMotorStarterApplied();
    msg.W2.Horn = data.IsIdanSecRepHornApplied();
    msg.W2.LeftTurn = data.IsIdanSecRepLeftTurnSignalApplied();
    msg.W2.RightTurn = data.IsIdanSecRepRightTurnSignalApplied();
    msg.W2.Hazard = data.IsIdanSecRepHazardsApplied();

    msg.W3.ActualGear = Utilities::GetValFromMap(StrToGear, data.GetIdanSecRepActualGear(), (unsigned char) 0x03); // def val: Nuetral
    msg.W3.ReqGear = Utilities::GetValFromMap(StrToGear, data.GetIdanSecRepRequestedGear(), (unsigned char)0x0E); // def val: Unknown

    msg.ParkingBreak = Utilities::GetValFromMap(StrToPark, data.GetIdanSecRepParkingBrake(), (unsigned char)0x02); // def val : Engaged
    msg.RPMmsb = (((int)data.GetIdanSecRepRpm() >> 8) & 0xff);
    msg.RPMlsb = ((int)data.GetIdanSecRepRpm() & 0xff);
    msg.Velocity = (int)data.GetIdanSecRepVelocity();

    FillBuffer(msg);  
}

t_msgID IdanSecondaryReportMessage::GetMsgID() const {
    return IDAN_SEC_REP_ID;
}