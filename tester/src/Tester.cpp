/**
* Tester.cpp
* Author: Binyamin Appelbaum
* Date: 13.12.17
*/

#include "Tester.h"
#include "VLPPluginAPI.h"
#include "DgpsPluginAPI.h"
#include "Logger.h"
#include "ConfigurationINI.h"
#include <boost/range/irange.hpp> // boost::irange
#include <boost/date_time/posix_time/posix_time.hpp> // boost::posix_time::ptime

void Tester::TestVLP() {
    using namespace boost::posix_time;

    VLPWrapper* vlp = CreateVLPObject("/home/robil/vlp.conf");
    RunVLP(vlp);
    double counter = 0;

    for (auto i : boost::irange(0, 1000000)) {
        for (auto j : boost::irange(0, 16)) {
            SetChannel(vlp, j, 0);
        }
        SetAzimuth(vlp, counter += 0.2);
        time_duration td =  microsec_clock::local_time() - from_time_t(0);
        SetVLPTimeStamp(vlp, td.total_microseconds());
        SendVLPData(vlp);
        usleep(100000);
        counter = (counter >= 360) ? 0 : counter;
    }

    DeleteVLPObject(vlp);
}

void Tester::TestDgps() {
    using namespace boost::posix_time;

    // static const std::string DEV_TTY = "/dev/ttyUSB0";
    // static const int BAUD_RATE = 115200;

    DgpsWrapper* dgps = CreateDgpsObject("/home/robil/dgps.conf");
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

void Tester::TestConf() {
    ConfigurationINI conf("/home/robil/test.conf");
    LOG << conf.GetValue("hello") << "\n";
    LOG << conf.GetValue("hi") << "\n";
    LOG << conf.GetValue("David") << "\n";
    LOG << conf.GetValue("day") << "\n";
}

Tester::Tester() {
    // TestVLP();
    // TestDgps();
    // TestConf();
}