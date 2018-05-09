/*
* IponPluginAPI.cpp
* API for external tools that need to use IPON
* Author: Binyamin Appelbaum
* Date: 08.05.18
*/

#include "IponPluginAPI.h"

IponWrapper* IponCreateObject(const char* confFilePath) {
    return new IponWrapper(confFilePath);
}

void IponDeleteObject(IponWrapper* pObj) {
    delete pObj;
}

void IponRun(IponWrapper* pObj) {
    pObj->Run(); 
}

void IponSendData(IponWrapper* pObj) {
    pObj->SetData();
}