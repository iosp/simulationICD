/*
* HLCPrimaryControlMessage.cpp
* HLC primary message to send
* Author: Binyamin Appelbaum
* Date: 20.03.18
*/

#include "HLCPrimaryControlMessage.h"
#include "IdanData.h"
#include "LoggerProxy.h"

HLCPrimaryControlMessage::HLCPrimaryControlMessage(int hertz) : IdanMessageGet(hertz) {
}

void HLCPrimaryControlMessage::ParseMessage(const char* buffer) {
    buffer = buffer + 8;
    m_message.ShutDownCmd = buffer[0];
    m_message.EmergencyCmd = buffer[1];
    m_message.SteerCmdMsb = buffer[2];
    m_message.SteerCmdLsb = buffer[3];
    m_message.GasCmdMsb = buffer[4];
    m_message.GasCmdLsb = buffer[5];
}

void HLCPrimaryControlMessage::UpdateData(IdanData& data) const {
    data.SetHLCPShutDownCmd(m_message.ShutDownCmd == SHUTDOWN_VAL);
    data.SetHLCPEmergencyCmd(m_message.EmergencyCmd == EMERGENCY_VAL);
    // combine msb and lsb to one integer
    int steerCombined = (m_message.SteerCmdMsb << 8 ) | (m_message.SteerCmdLsb & 0xff);
    int gasCombined = (m_message.GasCmdMsb << 8 ) | (m_message.GasCmdLsb & 0xff);
    float fixedSteer = float(steerCombined - 2000) / 2000;
    float fixedGas = float(gasCombined - 2000) / 2000;
    data.SetHLCPSteerCmd(fixedSteer);
    data.SetHLCPGasCmd(fixedGas);
}

t_msgID HLCPrimaryControlMessage::GetMsgID() const {
    return 0x50;
}