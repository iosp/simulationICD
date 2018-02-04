
#include "VLPPluginAPI.h"

VLPWrapper* CreateVLPObject(short ip1, short ip2, short ip3, short ip4, int port, int resolution,
    int returnMode, int dataSource, int sensorFrequency, int velType) {
    std::string ipAddress = std::to_string(ip1) + "." + std::to_string(ip2) + "." + std::to_string(ip3) + "." + std::to_string(ip4);
    return new VLPWrapper(ipAddress, std::to_string(port), resolution, returnMode, dataSource, sensorFrequency, velType);
}

void DeleteVLPObject(VLPWrapper* pVlp) {delete pVlp;}

void RunVLP(VLPWrapper* pVlp) { pVlp->Run();}

void SetAzimuth(VLPWrapper* pVlp, double azimuth){ pVlp->SetAzimuth(azimuth); }

void SetVLPTimeStamp(VLPWrapper* pVlp, int timeStamp) { pVlp->SetTimeStamp(timeStamp); }

void SetChannel(VLPWrapper* pVlp, double distance, short reflectivity) { pVlp->SetChannel(distance, reflectivity); }

void SendVLPData(VLPWrapper* pVlp) { pVlp->SetData(); }