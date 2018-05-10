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
#include "IbeoPluginAPI.h"
#include "LoggerProxy.h"
#include "ConfigurationINI.h"
#include "TCPCommunication.h"
#include "CanCommunication.h"
#include <boost/range/irange.hpp> // boost::irange
#include <boost/date_time/posix_time/posix_time.hpp> // boost::posix_time::ptime

using namespace boost::posix_time;

void Tester::TestVLP() {
    VLPWrapper* vlp = VLPCreateObject("/home/robil/simConfigs/vlp.conf");
    double azimuth = 0;

    for (auto i : boost::irange(0, 1000000)) {
        for (auto j : boost::irange(0, 24)) {
            for (auto k : boost::irange(0, 16)) {
                VLPSetChannel(vlp, 5, 0);
            }
            VLPSetAzimuth(vlp, azimuth);
            VLPSetTimeStamp(vlp, i);
            VLPCloseBlock(vlp);
            usleep(1000);
            azimuth += 0.2;
            azimuth = (azimuth >= 360) ? 0 : azimuth;
        }
        VLPSendData(vlp);
    }

    VLPDeleteObject(vlp);
}

void Tester::TestDgps() {
    DgpsWrapper* dgps = CreateDgpsObject("/home/robil/simConfigs/dgps.conf");
    RunDgps(dgps);
    for (auto i : boost::irange(0, 20)) {
        time_duration td =  microsec_clock::local_time() - from_time_t(0);
        SetPosition(dgps, 31.771959, 35.217018, 10);
        SetVelocities(dgps, 10, 10, 10);
        SetDgpsTimeStamp(dgps, td.total_microseconds());
        SendDgpsData(dgps);
        usleep(100000);
    }
  
    DeleteDgpsObject(dgps);
    dgps = nullptr;
}

void Tester::TestIns() {
    boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
    InsWrapper* ins = CreateInsObject("/home/robil/simConfigs/ins.conf");
    RunIns(ins);
    for (auto i : boost::irange(0, 30)) {
        boost::posix_time::ptime currTime = boost::posix_time::microsec_clock::local_time();
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

    DeleteInsObject(ins);
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

    for (auto i : boost::irange(0, 10000)) {
        GetIdanData(idan);

        SetIdanPrimSteerPos(idan, GetHLCPSteerCmd(idan));
        SetIdanPrimGasPos(idan, GetHLCPGasCmd(idan));
        
        SetIdanSecRepRoadLights(idan, IsHLCSRoadLightsApplied(idan));
        SetIdanSecRepHighBeam(idan, IsHLCSHighBeamApplied(idan));
        SetIdanSecRepLightsCutoff(idan, IsHLCSLightsCutoffApplied(idan));
        SetIdanSecRepKeySwitch(idan, IsHLCSKeySwitchApplied(idan));
        SetIdanSecRepMotorStarter(idan, IsHLCSMotorStarterApplied(idan));
        SetIdanSecRepHorn(idan, IsHLCSHornApplied(idan));
        SetIdanSecRepLeftTurnSignal(idan, IsHLCSLeftTurnSignalApplied(idan));
        SetIdanSecRepRightTurnSignal(idan, IsHLCSRightTurnSignalApplied(idan));
        SetIdanSecRepHazards(idan, IsHLCSHazardsApplied(idan));
        SetIdanSecRepRequestedGear(idan, GetHLCSGear(idan));
        SetIdanSecRepActualGear(idan, GetHLCSGear(idan));
        SetIdanSecRepParkingBrake(idan, IsHLCSParkingBrakeReleased(idan) ? "R" : "E");
        // SetIdanSecRepRpm(idan, 0);
        // SetIdanSecRepVelocity(idan, 0);

        SetIdanSecSenEngineTemp(idan, 90);
        SetIdanSecSenOilPress(idan, 50);
        SetIdanSecSenFuelLevel(idan, 100);
        SetIdanSecSenAlternatorVoltage(idan, 25.2);
        SetIdanSecSenBackupBattVoltage(idan, 25.2);
        SetIdanSecSenBatterySumUp(idan, 0);
        SetIdanSecSenAirPressFront(idan, 100);
        SetIdanSecSenAirPressRear(idan, 100);

        SendIdanData(idan);
        usleep(100000);
    }

    DeleteIdanObject(idan);
}

void Tester::TestIbeo() {
    IbeoWrapper* ibeo = IbeoCreateObject("/home/robil/simConfigs/ibeo.conf");
    IbeoRun(ibeo);

    while (true) {
        sleep(1);
    }

    IbeoDeleteObject(ibeo);
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
    // TestIdan();
    TestIbeo();
    // TestTCP();
}