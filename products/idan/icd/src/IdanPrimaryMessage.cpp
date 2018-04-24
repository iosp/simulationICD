/*
* IdanPrimaryMessage.cpp
* Idan primary message to send
* Author: Binyamin Appelbaum
* Date: 26.03.18
*/

#include "IdanPrimaryMessage.h"
#include "IdanData.h"
#include "LoggerProxy.h"

IdanPrimaryMessage::IdanPrimaryMessage(float hertz) : IdanMessageSend(hertz) {

}

int IdanPrimaryMessage::GetMessageSize() const {
    return sizeof(IDAN_PrimaryReportMsgType);
}

void IdanPrimaryMessage::FillMessage(const IdanData& data) {
    IDAN_PrimaryReportMsgType msg;
    msg.W1.ModeOfSteeringSAC = 5;
    msg.W1.Disc1 = 0;
    msg.W1.Disc2 = 1;
    msg.W1.Disc3 = 1;

    msg.SteeringErrorSAC = 0xff;
    msg.W3.SteerPosMsb = ((data.GetIdanPrimSteerPos() >> 8) & 0xff);
    msg.SteerPosLsb = (data.GetIdanPrimSteerPos() & 0xff);

    msg.W5.ModeOfGasBrakeSAC = 5;
    msg.W5.Disc1 = 0;
    msg.W5.Disc2 = 1;
    msg.W5.Disc3 = 1;
    msg.GasBrakeErrorSAC = 0xff;

    msg.W7.GasPosMsb = ((data.GetIdanPrimGasPos() >> 8) & 0xff);
    msg.GasPosLsb = (data.GetIdanPrimGasPos() & 0xff);

    FillBuffer(msg);
}

t_msgID IdanPrimaryMessage::GetMsgID() const {
    return 0x60;
}