#ifndef VLP32CONTROL_H
#define VLP32CONTROL_H

/*
* VLP32Control.h
* Manage communication between velodyne sensor with UDP socket - for VLP 32
* Author: Binyamin Appelbaum
* Date: 13.12.17
*/

#include "VLPControl.h"


class VLP32Control : public VLPControl {
protected:

    virtual void FillDataRecords(VLPDataPacket& packet, int dataIndex, int packetIndex) const;

    virtual int GetNumOfrowsInColumn() const;

    virtual bool CanAddToPacket(const boost::posix_time::time_duration& lastDuration, int dataIndex) const;

    virtual int DataIndexIncrement() const;

public:
    VLP32Control(const VLPConfig& vlpConfig);
    ~VLP32Control() = default;
};



#endif // VLP32CONTROL_H