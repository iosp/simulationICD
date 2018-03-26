#ifndef IDANPLUGINAPI_H
#define IDANPLUGINAPI_H

/*
* IdanPluginAPI.h
* API for external tools that need to use IDAN
* Author: Binyamin Appelbaum
* Date: 25.03.18
*/

#include "IdanWrapper.h"

// Functions that can be used by the plugin
extern "C" {
    IdanWrapper* CreateIdanObject(const char* confFilePath);

    void DeleteIdanObject(IdanWrapper* pObj);

    void RunIdan(IdanWrapper* pObj);

    unsigned char GetShutDownCmd(IdanWrapper* pObj);

    void GetIdanData(IdanWrapper* pObj);
}

#endif // IDANPLUGINAPI_H