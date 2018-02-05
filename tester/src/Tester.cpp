/**
* Tester.cpp
* Author: Binyamin Appelbaum
* Date: 13.12.17
*/

#include "Tester.h"
#include "VLPPluginAPI.h"
#include "DgpsPluginAPI.h"
#include "Logger.h"
#include <boost/range/irange.hpp> // boost::irange
#include <boost/date_time/posix_time/posix_time.hpp> // boost::posix_time::ptime

// std::vector<VLPCommunication::VLPData> generateData(VLPCommunication::Resolution res, int vecSize, int numOfChannels) {
//     using namespace boost::posix_time;
    
//     std::vector<VLPCommunication::VLPData> v;
//     for (auto i : boost::irange(0, vecSize)) {
//         VLPCommunication::t_channel_data channel;
//         for (auto j : boost::irange(0, numOfChannels)) {
//             channel.push_back(std::pair<double,short>(10, 0));
//         }
//         double azimuth = (double) (i / (1000.0 / res));
//         time_duration td =  microsec_clock::local_time() - from_time_t(0);
//         VLPCommunication::VLPData data(azimuth, channel, td);
//         v.push_back(data);
//     }
    
//     return v;
// }


void Tester::TestVLP() {
    static const std::string PORT = "2368";
    static const std::string IP_ADDRESS = "192.168.1.77";

    VLPWrapper* vlp = CreateVLPObject(IP_ADDRESS.c_str(), PORT.c_str(), 200, 37, 22, 10, 16);
    DeleteVLPObject(vlp);
    // VelodyneData::Resolution res = VLPCommunication::_RES02_;
    // double realRes = (res / 1000.0);
    // int vecSize = 360 / realRes;
    // const int JUMP = 30;
    // VLPCommunication::VLPConfig conf(IP_ADDRESS, PORT, res);
    // VLPCommunication* vlp = new VLPCommunication16(conf);

    // vlp->Run();
    // while (true) {
    //     std::vector<VLPCommunication::VLPData> data = generateData(res, vecSize, 16);
    //     for (auto i : boost::irange(0, vecSize, JUMP)) {
    //         std::vector<VLPCommunication::VLPData> newVec(data.begin() + i, data.begin() + i + JUMP);
    //         vlp->SetData(newVec);
    //     }
    // }

    // delete vlp;
}

void Tester::TestDgps() {
    using namespace boost::posix_time;

    static const std::string DEV_TTY = "/dev/ttyUSB0";
    static const int BAUD_RATE = 115200;

    DgpsWrapper* dgps = CreateDgpsObject(DEV_TTY.c_str(), BAUD_RATE);
    RunDgps(dgps);
    for (auto i : boost::irange(0, 1000000)) {
        time_duration td =  microsec_clock::local_time() - from_time_t(0);
        SetPosition(dgps, 31.771959, 35.217018, 10);
        SetVelocities(dgps, 10, 10, 10);
        SetDgpsTimeStamp(dgps, td.total_microseconds());
        SendDgpsData(dgps);
        usleep(100000);
    }
  
    // DeleteDgpsObject(dgps);
    // dgps = nullptr;
}

Tester::Tester() {
    TestDgps();
}