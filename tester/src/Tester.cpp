/**
* Tester.cpp
* Author: Binyamin Appelbaum
* Date: 13.12.17
*/

#include "Tester.h"
#include "VLPPluginAPI.h"
#include "DgpsPluginAPI.h"
#include "InsPluginAPI.h"
#include "IdanPluginAPI.h"
#include "LoggerProxy.h"
#include "ConfigurationINI.h"
#include "TCPCommunication.h"
#include "CanCommunication.h"
#include <boost/range/irange.hpp> // boost::irange
#include <boost/date_time/posix_time/posix_time.hpp> // boost::posix_time::ptime

using namespace boost::posix_time;

void Tester::TestVLP() {
    VLPWrapper* vlp = CreateVLPObject("/home/robil/simConfigs/vlp.conf");
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
    DgpsWrapper* dgps = CreateDgpsObject("/home/robil/simConfigs/dgps.conf");
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
    boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
    InsWrapper* ins = CreateInsObject("/home/robil/simConfigs/ins.conf");
    RunIns(ins);
    for (auto i : boost::irange(0, 1000000)) {
        boost::posix_time::ptime currTime = boost::posix_time::microsec_clock::local_time();
        // int simTime = (currTime - startTime).total_seconds();
        int simTime = i;
        SetInsTimeStamps(ins, simTime, simTime);
        SetInsPose(ins, 35.217018, 0, 31.771959);
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
    // TCPCommunication* t = new TCPCommunication("172.23.40.92", "50013");
    // t->SendData("hello world", sizeof("hello world"));

    // delete t;

}

void Tester::TestCAN() {
    CanCommunication* c = new CanCommunication("vscan0", 500000, true);
    char buffer[100]{};
    c->Init();
    c->SendData(buffer, 100);
    c->GetData(buffer);
    delete c;
}

void Tester::TestIdan() {
    IdanWrapper* idan = CreateIdanObject("/home/robil/simConfigs/idan.conf");
    RunIdan(idan);

    while (true) {
        GetIdanData(idan);
        auto steerPose = GetHLCPSteerCmd(idan);
        auto gasPose = GetHLCPGasCmd(idan);
        
        SetIdanPrimSteerPos(idan, steerPose);
        SetIdanPrimGasPos(idan, gasPose);
        SendIdanData(idan);
        usleep(2000);
    }
    DeleteIdanObject(idan);
    // Check send by IdanControl
}

void Tester::TestConf() {
    ConfigurationINI conf("/home/robil/test.conf");
    LOG << conf.GetValue<std::string>("hello") << "\n";
    LOG << conf.GetValue<std::string>("hi") << "\n";
    LOG << conf.GetValue<std::string>("David") << "\n";
    LOG << conf.GetValue<std::string>("day") << "\n";
}

Tester::Tester() {
    // TestVLP();
    // TestDgps();
    // TestConf();
    // TestIns();
    // TestCAN();
    TestIdan();
    //TestTCP();
}