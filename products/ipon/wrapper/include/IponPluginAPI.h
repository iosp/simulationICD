#ifndef IPONPLUGINAPI_H
#define IPONPLUGINAPI_H

/*
* IponPluginAPI.h
* API for external tools that need to use IPON
* Author: Binyamin Appelbaum
* Date: 08.05.18
*/

#include "IponWrapper.h"

// Functions that can be used by the plugin
extern "C" {
    IponWrapper* IponCreateObject(const char* confFilePath);

    void IponDeleteObject(IponWrapper* pObj);

    void IponRun(IponWrapper* pObj);

    void IponSendData(IponWrapper* pOb);
}

#endif // IPONPLUGINAPI_H