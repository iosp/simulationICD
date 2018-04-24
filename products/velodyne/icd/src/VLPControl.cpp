/**
* VLPControl.cpp
* Manage communication between velodyne sensor with UDP socket
* Author: Binyamin Appelbaum
* Date: 7.11.17
*/

#include "VLPControl.h"
#include "VLPConfig.h"
#include "VLPMessage.h"
#include "UDPCommunication.h"
#include "LoggerProxy.h"
#include "Helper.h"

#include <boost/range/irange.hpp> // boost::irange
#include <boost/assign.hpp> // boost::assign::map_list_of

VLPControl::VLPControl(const std::string& confFilePath) {
	m_vlpConf = new VLPConfig(confFilePath);
    m_comm = new UDPCommunication(m_vlpConf->GetIpAddress(), m_vlpConf->GetPort());
    InitVelodyneData();
}

VLPControl::~VLPControl() {
    m_sendDataThread.interrupt();
    m_sendDataThread.join();
    delete m_comm;
    delete m_vlpConf;
    delete m_message;
}

void VLPControl::InitVelodyneData() {
    int numOfColumns = (DEGREES / m_vlpConf->GetHorizontalResolution());
    for (int i : boost::irange(0, numOfColumns)) {
       m_velodyneData.push_back(VelodyneData(0, VelodyneData::t_channel_data(), 0));
    }
}

bool VLPControl::CheckDataValidation(const VelodyneData& data) const {
    double angle = data.GetAzimuth();
    // avoid 360 Degrees and above
    if ((angle >= DEGREES) || (angle < 0)) {
        ERRLOG << "Angle is not valid: " << angle << "\n";
        return false;
    }
    // check that the data size corresponds to the number of columns
    if (data.GetChannels().size() != 16) { // TODO define
        ERRLOG << "Channels size is not valid: " << data.GetChannels().size() << "\n";
        return false;
    }
    return true;
}

bool VLPControl::CanAddToPacket(float lastDuration, int dataIndex) const {
    return (lastDuration < m_velodyneData[dataIndex].GetSimTime()) && 
                (m_velodyneData[dataIndex].GetSimTime() < m_velodyneData[dataIndex + 1].GetSimTime()) &&
                !IsDataZeroed(dataIndex);
}

bool VLPControl::IsDataZeroed(int dataIndex) const {
    return std::all_of(m_velodyneData[dataIndex].GetChannels().begin(), m_velodyneData[dataIndex].GetChannels().end(), 
            [](const std::pair<double, short>& p) { return p.first == 0; });
}

void VLPControl::SetData(const VelodyneData& data) {
    m_velodyneDataMutex.lock();
    if (!CheckDataValidation(data)) {
        ERRLOG << "received invalid block\n";
        m_velodyneDataMutex.unlock();
        return;
    }
    // index is (angle / resolution) + 0.5 - to round up
    double index = data.GetAzimuth() / m_vlpConf->GetHorizontalResolution() + 0.5f; // HANDLE CASTING!!
    m_velodyneData[index] = data;
    m_velodyneDataMutex.unlock();
}

VelodyneData VLPControl::GetData() {
    ERRLOG << "This function is not implemented!\n";
    return VelodyneData();
}

void VLPControl::Run() {
    if (!m_comm->Init()) {
		LOG << "Failed to initialize communication, not running send thread.\n";
		return;
	}
    // transmittion frequency is the degrees*10 / <degrees range of packet>
    float hertz = (m_vlpConf->GetSensorFrequency() * DEGREES) /
                                    (m_vlpConf->GetHorizontalResolution() * 2*NUM_OF_VLP_DATA_BLOCKS);
    m_message = new VLPMessage(hertz, (int)m_vlpConf->GetReturnMode(), (int)m_vlpConf->GetDataSource());
    m_sendDataThread = boost::thread(&VLPControl::SendThreadMethod, this);
}

void VLPControl::SendThreadMethod() {
    auto lastDuration = 0;
    boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
    // thread works until interrupt
    try {
        while (true) {
            int dataIndex = 0;
            // run over m_velodyneData
            while (dataIndex < (DEGREES / m_vlpConf->GetHorizontalResolution())) {
                // send packet when it contains the required number of blocks
                if (m_message->IsReadyToSend()) {
                    m_message->SendMessage(m_comm);
                    m_message->InitMessage();
                    // calculate sleep time: (<time to sleep> - <time of the iteration>)
                    Utilities::SleepForRestTime(startTime, m_message->GetSleepTimeBetweenEverySend());
                    startTime = boost::posix_time::microsec_clock::local_time();
                }
                boost::this_thread::interruption_point();
                // critical section - try to fill a block
                m_velodyneDataMutex.lock();
                // fill block only if the time stamps of the blocks are valid
                if (CanAddToPacket(lastDuration, dataIndex)) {
                    FillMessage(dataIndex);
                    // take the last duration from the last cell that was inserted
                    lastDuration = m_velodyneData[dataIndex + 1].GetSimTime();
                }
                dataIndex += 2;
                m_velodyneDataMutex.unlock();
            }
        }
    }
    catch (boost::thread_interrupted&) {
        LOG << "thread VLP interruped!\n";
        return;
    }
}

void VLPControl::FillMessage(int dataIndex) {
    auto currData = m_velodyneData[dataIndex];
    auto values = currData.GetChannels();
    auto additionalValues = m_velodyneData[dataIndex + 1].GetChannels();
    values.insert(values.end(), additionalValues.begin(), additionalValues.end());
    currData.SetChannels(values);
    m_message->FillMessage(currData);
}

void VLPControl::printVelData() const {       
    for (auto const& data : m_velodyneData) {
        auto values = data.GetChannels();
        if (values.empty()) {
            continue;
        }
        std::cout << "Angle: ****" << data.GetAzimuth() << "****. Data: " << std::endl;
        for (auto const& val : values) {
            std::cout << "(" << val.first << "," << val.second << ") ";
        }
        std::cout << std::endl;
    }
}