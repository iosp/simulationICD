/**
* Tester.cpp
* Author: Binyamin Appelbaum
* Date: 13.12.17
*/

#include "Tester.h"
#include "VelodynePluginAPI.h"
#include "NovatelPluginAPI.h"
#include "TiltanPluginAPI.h"
#include "IdanPluginAPI.h"
#include "LoggerProxy.h"
#include "ConfigurationINI.h"
#include "TCPServerCommunication.h"
#include "TCPClientCommunication.h"
#include "CanCommunication.h"
#include <boost/range/irange.hpp> // boost::irange
#include <boost/date_time/posix_time/posix_time.hpp> // boost::posix_time::ptime
#include <thread> // std::this_thread::sleep_for

using namespace boost::posix_time;

void Tester::TestVelodyne() {
    LOG << "*************** Running velodyne test ***************\n";

    VelodyneWrapper* velodyne = VelodyneCreateObject("/home/robil/simConfigs/velodyne.conf");
    double azimuth = 0;

    for (auto i : boost::irange(0, 1000000)) {
        for (auto j : boost::irange(0, 24)) {
            for (auto k : boost::irange(0, 16)) {
                VelodyneSetChannel(velodyne, 5, 0);
            }
            VelodyneSetAzimuth(velodyne, azimuth);
            VelodyneSetTimeStamp(velodyne, i);
            VelodyneCloseBlock(velodyne);
            azimuth += 0.2;
            azimuth = (azimuth >= 360) ? 0 : azimuth;
        }
        VelodyneSendData(velodyne);
		std::this_thread::sleep_for(std::chrono::microseconds(1333));
    }

    VelodyneDeleteObject(velodyne);
}

void Tester::TestNovatel() {
    LOG << "*************** Running novatel test ***************\n";\
    NovatelWrapper* novatel = NovatelCreateObject("/home/robil/simConfigs/novatel.conf");
    for (auto i : boost::irange(0, 20)) {
        time_duration td =  microsec_clock::local_time() - from_time_t(0);
        NovatelSetPosition(novatel, 31.771959, 35.217018, 10);
        NovatelSetVelocities(novatel, 10, 10, 10);
        NovatelSetTimeStamp(novatel, td.total_microseconds());
        NovatelSendBestPosData(novatel);
        NovatelSendBestVelData(novatel);
		std::this_thread::sleep_for(std::chrono::microseconds(100000));
    }
  
    NovatelDeleteObject(novatel);
    novatel = nullptr;
}

void Tester::TestTiltan() {
    LOG << "*************** Running tiltan test ***************\n";

    boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
    TiltanWrapper* tiltan = TiltanCreateObject("/home/robil/simConfigs/tiltan.conf");
    for (auto i : boost::irange(0, 30)) {
        boost::posix_time::ptime currTime = boost::posix_time::microsec_clock::local_time();
        int simTime = i;
        TiltanSetTimeStamps(tiltan, simTime, simTime);
        TiltanSetPose(tiltan, 35.217018, 0, 31.771959);
        TiltanSetOrientation(tiltan, i % 360, 0, 0);
        TiltanSetAzimuthRate(tiltan, 0);
        TiltanSetVelocity(tiltan, i % 100, i % 100, i % 100);
        TiltanSetDistances(tiltan, 0, 0);
        TiltanSetMotionDetected(tiltan, true);
       
        TiltanSetInternalGpsFields(tiltan, 0, 4);
        
        TiltanSetDirectionErrors(tiltan, 0,0,0,0,0);
        TiltanSetVelocityErrors(tiltan, 0,0,0);
        TiltanSetOrientationErrors(tiltan, 0,0,0);

        TiltanSendStatusMsgData(tiltan);
        TiltanSendInternalGPSData(tiltan);
        TiltanSendNavigationData(tiltan);
        TiltanSendErrorEstimationData(tiltan);
		std::this_thread::sleep_for(std::chrono::microseconds(100000));
    }

    TiltanDeleteObject(tiltan);
}

void Tester::TestIdan() {
    LOG << "*************** Running idan test ***************\n";

    IdanWrapper* idan = IdanCreateObject("/home/robil/simConfigs/idan.conf");

    for (auto i : boost::irange(0, 10000)) {
        IdanReceiveData(idan);

        SetIdanPrimSteerPos(idan, GetHLCPSteerCmd(idan));
        SetIdanPrimGasPos(idan, GetHLCPGasCmd(idan));
        SendIdanPrimaryData(idan);
        
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
        SendIdanSecondaryReportData(idan);

        SetIdanSecSenEngineTemp(idan, 90);
        SetIdanSecSenOilPress(idan, 50);
        SetIdanSecSenFuelLevel(idan, 100);
        SetIdanSecSenAlternatorVoltage(idan, 25.2);
        SetIdanSecSenBackupBattVoltage(idan, 25.2);
        SetIdanSecSenBatterySumUp(idan, 0);
        SetIdanSecSenAirPressFront(idan, 100);
        SetIdanSecSenAirPressRear(idan, 100);
        SendIdanSecondarySensorData(idan);

		std::this_thread::sleep_for(std::chrono::microseconds(100000));
    }

   IdanDeleteObject(idan);
}

void Tester::TestTCP() {
    TCPClientCommunication* t = new TCPClientCommunication("127.0.0.1");
    t->SendData("hello world", sizeof("hello world"));

    delete t;

}

void Tester::TestConf() {
    ConfigurationINI conf("/home/robil/test.conf");
    LOG << conf.GetValue<std::string>("hello") << "\n";
    LOG << conf.GetValue<std::string>("hi") << "\n";
    LOG << conf.GetValue<std::string>("David") << "\n";
    LOG << conf.GetValue<std::string>("day") << "\n";
}

void Tester::TestLogs() {
    while (true) {
        LOG << "hello world\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
}

Tester::Tester() {
    // TestLogs();
    // TestVelodyne();
    // TestNovatel();
    TestTiltan();
    // TestIdan();
    // TestTCP();
}