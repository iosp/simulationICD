/*
* IdanPluginAPI.h
* API for external tools that need to use IDAN
* Author: Binyamin Appelbaum
* Date: 25.03.18
*/

#include "IdanPluginAPI.h"

IdanWrapper* CreateIdanObject(const char* confFilePath) {
    return new IdanWrapper(confFilePath);
}

void DeleteIdanObject(IdanWrapper* pObj) {delete pObj;}

void RunIdan(IdanWrapper* pObj) { pObj->Run(); }

unsigned char GetShutDownCmd(IdanWrapper* pObj) {
    return pObj->GetShutDownCmd();
}

void GetIdanData(IdanWrapper* pObj) {
    pObj->GetData();
}