
#include "DgpsPluginAPI.h"

static const std::string DEV_TTY = "/dev/ttyUSB0";
static const int BAUD_RATE = 115200;

DgpsWrapper* CreateDgpsObject() {
    return new DgpsWrapper(DEV_TTY, BAUD_RATE);
}

void DeleteDgpsObject(DgpsWrapper* pObj) {delete pObj;}

void RunDgps(DgpsWrapper* pObj) { pObj->Run(); }

void SendDgpsData(DgpsWrapper* pObj) { pObj->SetData(); }

void SetPosition(DgpsWrapper* pObj, double latitude, double longitude, double altitude) {
    pObj->SetPosition(latitude, longitude, altitude);
}

void SetVelocities(DgpsWrapper* pObj, double latSpeed, double longSpeed, double altAzimuth) {
    pObj->SetVelocities(latSpeed, longSpeed, altAzimuth);
}

void SetDgpsTimeStamp(DgpsWrapper* pObj, int timeStamp) {
    pObj->SetTimeStamp(timeStamp);
}