#ifndef VLPSMESSAGE_H
#define VLPSMESSAGE_H

/*
* VLPMessage.h
* Velodyne message to send
* Author: Binyamin Appelbaum
* Date: 07.03.18
*/

#include "VLPStructs.h"
#include "IMessage.h"
#include "VelodyneData.h"

class ICommunication; // forward declaration

static const int DEGREES = 360;

class VLPMessage : public IMessage<VelodyneData>{
private:
	VLPDataPacket m_packet;
	int m_packetIndex = 0;

    /**
     * Fill time stamp on VLP packet
     * @param data - velodyne data to fill
     */ 
    void FillTimeStamp(const VelodyneData& data);

    /**
     * Fill factory field on VLP packet
     * @param returnMode
	 * @param dataSource
     */
    void FillFactory(int returnMode, int dataSource);

    /**
     * Fill azimuth on VLP packet
     * @param data - velodyne data to fill
     */
    void FillAzimuth(const VelodyneData& data);

    /**
     * Transform vector of channels to adapt Velodyne format.
     * The method converts vector indexes ( the example is for VLP16 but works also for VLP32)
     * Orig: 0  1  2  3  4  5  6  7  8  9  10  11  12  13  14  15
     * New:  0  8  1  9  2  10 3 11  4  12 5   13  6   14  7   15
     * @param channels - vector of channel pairs (distance and reflectivity)
     * @return new formatted vector
     */
    VelodyneData::t_channel_data MapChannels(const VelodyneData::t_channel_data& channels) const;

    /**
     * Fill channles in specific packet in packet index
     * @param channels - the data of the channels
     */
    void FillChannelsInPacket(const VelodyneData::t_channel_data& channels);

    /**
     * Fill data records on VLP packet
     * @param data - velodyne data to fill
     */
    virtual void FillDataRecords(const VelodyneData& data);
	/**
     * convert number to unsigned char array with HEX values of this number. the array bytes are reversed.
     * This function works only for unsigned types!
     * @param num - unsinged long / int / short number
     * @param ret - return buffer
     * @size - size of ret array
     * @return bool - true for success, false for wrong input (ret == nullptr)
     */ 
    template <typename T>
    bool ToByteArray(T num, unsigned char* ret, size_t size) const;

	/**
     * convert block of unsigned char array with HEX values to number. the array bytes are reversed.
     * This function works only for unsigned types!
     * @param arr - the array with HEX values
     * @size - size of array
     * @func - lambda function to operate on the number
     * @return double - the original number after func operated on it
     */ 
    template <typename Func>
    double FormatBlock(const unsigned char* arr, size_t size, Func func) const;

	/**
     * Print the packet data (formatted). for debug only
     */ 
    void printPacketData() const;

public:
	VLPMessage(int hertz, int returnMode, int dataSource);

	virtual ~VLPMessage() = default;

	virtual void FillMessage(const VelodyneData& data);

	virtual int SendMessage(ICommunication* comm) const override;

	virtual int GetMessageSize() const override;

	bool IsReadyToSend() const;

    void InitMessage();
};

#endif // VLPSMESSAGE_H