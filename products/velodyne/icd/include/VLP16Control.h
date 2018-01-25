#ifndef VLP16CONTROL_H
#define VLP16CONTROL_H

/*
* VLP16Control.h
* Manage communication between velodyne sensor with UDP socket - for VLP 16
* Author: Binyamin Appelbaum
* Date: 13.12.17
*/

#include "VLPControl.h"


class VLP16Control : public VLPControl {
protected:

    virtual void FillDataRecords(VLPDataPacket& packet, int dataIndex, int packetIndex) const;

    virtual int GetNumOfrowsInColumn() const;

    virtual bool CanAddToPacket(const boost::posix_time::time_duration& lastDuration, int dataIndex) const;

    virtual int DataIndexIncrement() const;

public:
    VLP16Control(const VLPConfig& vlpConfig);
    ~VLP16Control() = default;
};



#endif // VLP16CONTROL_H