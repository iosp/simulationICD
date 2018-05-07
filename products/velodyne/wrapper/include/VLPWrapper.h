#ifndef VLPWRAPPER_H
#define VLPWRAPPER_H

/*
* VLPWrapper.h
* Wrapper fpr velodyne ICD
* Author: Binyamin Appelbaum
* Date: 04.01.18
*/

#include "VelodyneData.h"
#include "IWrapper.h"

/**
 * VLPWrapper holds a pointer to VLPControl, and temporary data.
 * Once the object is created - the pointer is assigned (new).
 * m_data holds the temporary data of the user, and m_currChannles holds the temporary channels that the user saved.
 * m_currBlock holds the temporary block.
 * When the user calls "CloseBlock" we add the current data to m_data.
 * When the user calls "SetData" - we take the data that we aggregated until now and send it (set it) to VLP pointer.
 * We clear the temporary data right after the send
 * */
class VLPWrapper : public IWrapper<VelodyneData> {
private:
    /**
     * temporary data to aggregate
     */ 
    VelodyneData m_data;
    /**
     * temporary block to aggregate
     */ 
    VelodyneData::VelodyneBlock m_currBlock;
    /**
     * temporary channels to aggregate
     */ 
    VelodyneData::t_channel_data m_currChannels;


    /**
     * Initialize current block of the object
     */ 
    void InitCurrBlock();

    /**
     * Initialize current data of the object
     */ 
    void InitData();

public:
    VLPWrapper(const std::string& confFilePath);

    ~VLPWrapper();

    /**
     * Take the temporary data and set it to vlp
     */ 
    virtual void SetData() override;

    /**
     * Set azimuth to the temporary data
     */ 
    void SetAzimuth(double azimuth);

    /**
     * Set time stamp to the temporary data
     */ 
    void SetTimeStamp(float timeStamp);

    /**
     * Set channel to temporary channels
     */ 
    void SetChannel(double distance, short reflectivity);

    /**
     * Add current block to velodyne data
     */ 
    void CloseBlock();

    virtual void GetData() override {}

    virtual void Run() override {}

};

#endif // VLPWRAPPER_H