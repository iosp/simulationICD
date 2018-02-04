
#include "DgpsWrapper.h"

// Functions that can be used by the plugin
extern "C" {
    DgpsWrapper* CreateDgpsObject();

    void DeleteDgpsObject(DgpsWrapper* pObj);

    void RunDgps(DgpsWrapper* pObj);

    void SendDgpsData(DgpsWrapper* pOb);

    void SetPosition(DgpsWrapper* pObj, double latitude, double longitude, double altitude);

    void SetVelocities(DgpsWrapper* pObj, double latSpeed, double longSpeed, double altAzimuth);

    void SetDgpsTimeStamp(DgpsWrapper* pVlp, int timeStamp);
}