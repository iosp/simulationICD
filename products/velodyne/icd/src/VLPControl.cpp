/**
* VLPControl.cpp
* Manage communication between velodyne sensor with UDP socket
* Author: Binyamin Appelbaum
* Date: 7.11.17
*/

#include "VLPControl.h"
#include "Logger.h"
#include "Helper.h"
#include "UDPCommunication.h"
#include "VLPConfig.h"

#include <boost/range/irange.hpp> // boost::irange
#include <boost/assign.hpp> // boost::assign::map_list_of

static const int DISTANCE_MULT = 500;
static const int AZIMUTH_MULT = 100;
static const unsigned long HOUR_TO_MICRO_SEC = 360 * SECOND_TO_MICROSECOND;

VLPControl::VLPControl(const std::string& confFilePath) {
	m_vlpConf = new VLPConfig(confFilePath);
    InitVelodyneData();
    // transmittion frequency is the degrees*10 / <degrees range of packet>
    size_t transmissionFrequency = (m_vlpConf->GetSensorFrequency() * DEGREES) /
                                    (m_vlpConf->GetHorizontalResolution() * 2*NUM_OF_VLP_DATA_BLOCKS);
    m_comm = new UDPCommunication(m_vlpConf->GetIpAddress(), m_vlpConf->GetPort());
	m_sleepTimeBetweenEverySend = SECOND_TO_MICROSECOND / transmissionFrequency;
}

VLPControl::~VLPControl() {
    m_sendDataThread.interrupt();
    delete m_comm;
    delete m_vlpConf;
}


void VLPControl::VLPDataPacket::InitVLPDataPacket() {
    std::fill_n(dataBlocks, NUM_OF_VLP_DATA_BLOCKS, VLPDataBlock());
    std::fill_n(timeStamp, 4, 0);
}

void VLPControl::InitVelodyneData() {
    int numOfColumns = (DEGREES / m_vlpConf->GetHorizontalResolution());
    for (int i : boost::irange(0,numOfColumns)) {
       m_velodyneData.push_back(VelodyneData::VLPBlock(0, VelodyneData::VLPBlock::t_channel_data(), boost::posix_time::microseconds(0)));
    }
}

bool VLPControl::CheckDataValidation(const VelodyneData::VLPBlock& data) const {
    double angle = data.GetAzimuth();
    // avoid 360 Degrees and above
    if ((angle >= DEGREES) || (angle < 0)) {
        ERRLOG << "Angle is not valid: " << angle << "\n";
        return false;
    }
    // check that the data size corresponds to the number of columns
    if (data.GetChannels().size() != GetNumOfrowsInColumn()) {
         ERRLOG << "Channels size is not valid: " << data.GetChannels().size() << "\n";
        return false;
    }
    return true;
}

bool VLPControl::IsDataZeroed(int dataIndex) const {
    return std::all_of(m_velodyneData[dataIndex].GetChannels().begin(), m_velodyneData[dataIndex].GetChannels().end(), 
            [](const std::pair<double, short>& p) { return p.first == 0; });
}

void VLPControl::SetData(const VelodyneData& data) {
    for (auto const& block : data.GetData()) {
        m_velodyneDataMutex.lock();
        if (!CheckDataValidation(block)) {
            ERRLOG << "received invalid block\n";
            m_velodyneDataMutex.unlock();
            continue;
        }
        // index is (angle / resolution) + 0.5 - to round up
        double index = block.GetAzimuth() / m_vlpConf->GetHorizontalResolution() + 0.5f; // HANDLE CASTING!!
        m_velodyneData[index] = block;
        m_velodyneDataMutex.unlock();
    }
}

VelodyneData* VLPControl::GetData() {
    ERRLOG << "This function is not implemented!\n";
    return nullptr;
}

void VLPControl::SendPacket(const VLPDataPacket& packet) const {
    char buf[sizeof(VLPDataPacket)]{};
    memcpy(buf, &packet, sizeof(packet));
    m_comm->SendData(buf, sizeof(buf));
}

void VLPControl::SendData() const {
    using namespace boost::posix_time;

    VLPDataPacket packet;
    FillFactory(packet);
    int packetIndex = 0;
    time_duration lastDuration = microseconds(0);
    ptime startTime = microsec_clock::local_time();
    // thread works until interrupt
    while (true) {
        int dataIndex = 0;
        // run over m_velodyneData
        while (dataIndex < (DEGREES / m_vlpConf->GetHorizontalResolution())) {
            // send packet when it contains the required number of blocks
            if (packetIndex == NUM_OF_VLP_DATA_BLOCKS) {
                SendPacket(packet);
                // printPacketData(packet);
                packet.InitVLPDataPacket();
                packetIndex = 0;
                // calculate sleep time: (<time to sleep> - <time of the iteration>)
                Utilities::SleepForRestTime(startTime, m_sleepTimeBetweenEverySend);
                startTime = microsec_clock::local_time();
            }
            // critical section - try to fill a block
            m_velodyneDataMutex.lock();
            // fill block only if the time stamps of the blocks are valid
            if (CanAddToPacket(lastDuration, dataIndex)) {
                FillBlockInPacket(dataIndex, packetIndex, packet);
                // take the last duration from the last cell that was inserted
                lastDuration = m_velodyneData[dataIndex + DataIndexIncrement() - 1].GetSimTime();
                packetIndex++;
            }
            dataIndex += DataIndexIncrement();
            m_velodyneDataMutex.unlock();
        }
    }
}

void VLPControl::FillBlockInPacket(int dataIndex, int packetIndex, VLPDataPacket& packet) const {
    // fill time stamp only for the first index
    if (packetIndex == 0) {
        FillTimeStamp(packet, dataIndex);
    }
    FillAzimuth(packet, dataIndex, packetIndex);
    FillDataRecords(packet, dataIndex, packetIndex);
}

void VLPControl::FillTimeStamp(VLPDataPacket& packet, int dataIndex) const {
    boost::posix_time::time_duration td = m_velodyneData[dataIndex].GetSimTime();
    // reduce hours from the time stamp (time stamp is how much time passed after the last round hour)
    unsigned long microseconds = td.total_microseconds() - (td.hours() * HOUR_TO_MICRO_SEC);
    ToByteArray((unsigned long)microseconds, packet.timeStamp, sizeof(packet.timeStamp));
}

void VLPControl::FillFactory(VLPDataPacket& packet) const {
    packet.factory[0] = m_vlpConf->GetReturnMode();
    packet.factory[1] = m_vlpConf->GetDataSource();    
}

void VLPControl::FillAzimuth(VLPDataPacket& packet, int dataIndex, int packetIndex) const {
    // convert the angle * 100 (in order to save double information) to array on the suitable block of the packet
    ToByteArray((unsigned int) (m_velodyneData[dataIndex].GetAzimuth() * AZIMUTH_MULT),
        packet.dataBlocks[packetIndex].azimuth, sizeof(packet.dataBlocks[packetIndex].azimuth));
}

void VLPControl::FillChannelsInPacket(VLPDataPacket& packet, const VelodyneData::VLPBlock::t_channel_data& channels, int packetIndex) const {
    for (auto i : boost::irange<size_t>(0, channels.size())) {
         // convert the distance * 500 (in order to save double information) to array on the suitable block of the packet
        ToByteArray((unsigned int)(channels[i].first * DISTANCE_MULT), 
            packet.dataBlocks[packetIndex].dataRecords[i].distance, sizeof(packet.dataBlocks[packetIndex].dataRecords[i].distance));
    }
}

VelodyneData::VLPBlock::t_channel_data VLPControl::MapChannels(const VelodyneData::VLPBlock::t_channel_data& channels) const {
    int channelsSize = channels.size();
    VelodyneData::VLPBlock::t_channel_data newChannels(channelsSize);
    // put the size/2 first elements in the correspoindig 2*i indexes on the new vector (0 -> 0, 1 -> 2, 2 -> 4, etc)
    for (auto i : boost::irange(0,channelsSize / 2)) {
        newChannels[i*2] = channels[i];
    }
    // fill the rest indexes of the new vector with the last size/2 elements of the original vector ( 1 -> 8, 3 -> 9, 5 -> 10, etc)
    for (int i = 1, j = channelsSize / 2; i < channelsSize; i += 2, j++) {
        newChannels[i] = channels[j];
    }
    return newChannels;
}

void VLPControl::Run() {
    if (!m_comm->Init()) {
		LOG << "Failed to initialize communication, not running send thread.\n";
		return;
	}
    m_sendDataThread = boost::thread(&VLPControl::SendData, this);
}

template <typename Func>
double VLPControl::FormatBlock(const unsigned char* arr, size_t size, Func func) const {
    long num = 0;
    for (int i = 0; i < size; i++) {
        num += ((long)arr[i] << i*8);
    }
    return func(num);
}

template <typename T>
bool VLPControl::ToByteArray(T num, unsigned char* ret, size_t size) const {
    if (ret == nullptr) {
        ERRLOG << "nullptr\n";
        return false;
    }
    // drop the right-most bytes and convert to new right most byte. after the loop - the bytes will be reversed
    for (int i = 0; i < size; i++) {
        ret[i] = (int)((num >> (8*i)) & 0xFF);
    }
    return true;
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

void VLPControl::printPacketData(const VLPDataPacket& packet) const {
    auto azimuthFunc = [](double num) -> double {return (double)num/AZIMUTH_MULT; };
    auto distanceFunc = [](double num) -> double {return (double)num/DISTANCE_MULT; };
    auto tsFunc = [](double num) -> double {return (double)num/SECOND_TO_MICROSECOND; };
    auto defFunc = [](double num) -> double {return num; };

    for (auto const& block : packet.dataBlocks) {
        LOG << "Azimuth: " << FormatBlock(block.azimuth, sizeof(block.azimuth), azimuthFunc) << "\n";
        int i = 0;
        for (auto const& channel : block.dataRecords) {
            std::stringstream ss;
            ss << "  Distance " << i++ << ": "  << FormatBlock(channel.distance, sizeof(channel.distance), distanceFunc);
            // ss << "  Reflectivity: " << channel.reflectivity;
            LOG << ss.str() << "\n";
        }
        LOG << "\n";
    }
    DBGLOG << "Return mode: " << VLPConfig::retModeToStr.find((VLPConfig::ReturnMode)packet.factory[0])->second << "\n";
    DBGLOG << "Data source: " << VLPConfig::dataSourceToStr.find((VLPConfig::DataSource)packet.factory[1])->second << "\n";
    LOG << "*********** Simulation time: " << FormatBlock(packet.timeStamp, sizeof(packet.timeStamp), tsFunc) << " *********************\n";
}
