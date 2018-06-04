/*
* IdanPrimaryMessage.cpp
* Idan primary message to send
* Author: Binyamin Appelbaum
* Date: 26.03.18
*/

#include "IdanPrimaryMessage.h"
#include "IdanData.h"
#include "LoggerProxy.h"

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
    int fixedSteer = data.GetIdanPrimSteerPos() * 2000 + 2000;
    msg.W3.SteerPosMsb = ((fixedSteer >> 8) & 0xff);
    msg.SteerPosLsb = (fixedSteer & 0xff);

    msg.W5.ModeOfGasBrakeSAC = 5;
    msg.W5.Disc1 = 0;
    msg.W5.Disc2 = 1;
    msg.W5.Disc3 = 1;
    msg.GasBrakeErrorSAC = 0xff;

    int fixedGas = data.GetIdanPrimGasPos() * 2000 + 2000;
    msg.W7.GasPosMsb = ((fixedGas >> 8) & 0xff);
    msg.GasPosLsb = (fixedGas & 0xff);

    FillBuffer(msg);
}

t_msgID IdanPrimaryMessage::GetMsgID() const {
    return IDAN_PRIM_ID;
}