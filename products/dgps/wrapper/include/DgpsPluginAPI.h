
#include "DgpsWrapper.h"

// Functions that can be used by the plugin
extern "C" {
    DgpsWrapper* CreateDgpsObject();

    void DeleteDgpsObject(DgpsWrapper* pObj);

    void RunDgps(DgpsWrapper* pObj);

    void SendDgpsData(DgpsWrapper* pOb);

    void SetDgpsData(DgpsWrapper* pOb, const DgpsData& data);
}