/*
* IdanSecondarySensorMessage.cpp
* Idan secondary sensor message to send
* Author: Binyamin Appelbaum
* Date: 29.03.18
*/

#include "IdanSecondarySensorMessage.h"
#include "IdanData.h"
#include "LoggerProxy.h"

IdanSecondarySensorMessage::IdanSecondarySensorMessage(float hertz) : IdanMessageSend(hertz) {

}

int IdanSecondarySensorMessage::GetMessageSize() const {
    return sizeof(IDAN_SecondarySensorsMsgType);
}

void IdanSecondarySensorMessage::FillMessage(const IdanData& data) {
    IDAN_SecondarySensorsMsgType msg;

    msg.EngineTemp = (int)data.GetIdanSecSenEngineTemp() + 40;
    msg.OilPress = (int)data.GetIdanSecSenOilPress();
    msg.FuelLevel = (int)data.GetIdanSecSenFuelLevel();
    msg.AlternatorVoltage = (int)(data.GetIdanSecSenAlternatorVoltage() * 5);
    msg.BackupBattVoltage = (int)(data.GetIdanSecSenBackupBattVoltage() * 10);
    msg.BatterySumUp = data.GetIdanSecSenBatterySumUp();
    msg.AirPressFront = (int)data.GetIdanSecSenAirPressFront();
    msg.AirPressRear =(int) data.GetIdanSecSenAirPressRear();

    FillBuffer(msg);
}

t_msgID IdanSecondarySensorMessage::GetMsgID() const {
    return IDAN_SEC_SEN_ID;
}