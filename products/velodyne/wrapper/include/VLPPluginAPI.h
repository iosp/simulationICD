
#include "VLPWrapper.h"

// Functions that can be used by the plugin
extern "C" {
    VLPWrapper* CreateVLPObject(short ip1, short ip2, short ip3, short ip4, int port, int resolution,
        int returnMode, int dataSource, int sensorFrequency, int velType);

    void DeleteVLPObject(VLPWrapper* pVlp);

    void RunVLP(VLPWrapper* pVlp);

    void SetAzimuth(VLPWrapper* pVlp, double azimuth);

    void SetTimeStamp(VLPWrapper* pVlp, int timeStamp);

    void SetChannel(VLPWrapper* pVlp, double distance, short reflectivity);

    void SendVLPData(VLPWrapper* pVlp);
}