/**
* Tester.cpp
* Author: Binyamin Appelbaum
* Date: 13.12.17
*/

#include "Tester.h"
#include "VLPPluginAPI.h"
#include "DgpsPluginAPI.h"
#include "InsPluginAPI.h"
#include "Logger.h"
#include "ConfigurationINI.h"
#include "TCPCommunication.h"
#include <boost/range/irange.hpp> // boost::irange
#include <boost/date_time/posix_time/posix_time.hpp> // boost::posix_time::ptime

using namespace boost::posix_time;

void Tester::TestVLP() {
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

void Tester::TestIns() {
    InsWrapper* ins = CreateInsObject("/home/robil/ins.conf");
    RunIns(ins);
    for (auto i : boost::irange(0, 1000000)) {
        time_duration td =  microsec_clock::local_time() - from_time_t(0);
        SetInsTimeStamps(ins, td.total_microseconds(), td.total_microseconds());
        
        SetInsPose(ins, 0, 31.771959, 35.217018);
        SetInsOrientation(ins, i % 360, 0, 0);
        SetInsAzimuthRate(ins, 0);
        SetInsVelocity(ins, i % 100, i % 100, i % 100);
        SetInsDistances(ins, 0, 0);
        SetInsMotionDetected(ins, true);
       
        SetInsInternalGpsFields(ins, 0, 4);
        
        SetInsDirectionErrors(ins, 0,0,0,0,0);
        SetInsVelocityErrors(ins, 0,0,0);
        SetInsOrientationErrors(ins, 0,0,0);

        SendInsData(ins);
        usleep(100000);
    }

}

void Tester::TestTCP() {

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
    TestIns();
    TestTCP();
}