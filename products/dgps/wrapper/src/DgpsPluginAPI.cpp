
#include "DgpsPluginAPI.h"

DgpsWrapper* CreateDgpsObject() {
    return new DgpsWrapper();
}

void DeleteDgpsObject(DgpsWrapper* pObj) {delete pObj;}

void RunDgps(DgpsWrapper* pObj) { pObj->Run(); }

void SendDgpsData(DgpsWrapper* pObj) { pObj->SetData(); }

void SetDgpsData(DgpsWrapper* pObj, const DgpsData& data) { pObj->SetDgpsData(data); }