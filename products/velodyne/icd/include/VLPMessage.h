#ifndef VLPSMESSAGE_H
#define VLPSMESSAGE_H

/*
* VLPMessage.h
* Velodyne message to send
* Author: Binyamin Appelbaum
* Date: 07.03.18
*/

#include "VLPStructs.h"
#include "Message.h"
#include "VelodyneData.h"

class ICommunication; // forward declaration

static const int DEGREES = 360;

class VLPMessage : public Message<VelodyneData>{
private:
	VLPDataPacket m_packet;

    int m_packetIndex = 0;

    /**
     * Take every blocks[i] channels (i % 2 == 1) and combine it with blocks[i-1] channels.
     * @param blocks - the blocks to combine
     * @return combined vector (0,1,2,3,4,5 => 01, 23, 45)
     */ 
    std::vector<VelodyneData::VelodyneBlock> CombineBlocks(const std::vector<VelodyneData::VelodyneBlock>& blocks) const;
    
    /**
     * Fill time stamp on VLP packet
     * @param timeStamp - time stamp data to fill
     */ 
    void FillTimeStamp(float timeStamp);

    /**
     * Fill factory field on VLP packet
     * @param returnMode
	 * @param dataSource
     */
    void FillFactory(int returnMode, int dataSource);

    /**
     * Fill azimuth on VLP packet
     * @param azimuth - azimuth data to fill
     */
    void FillAzimuth(float azimuth);

    /**
     * Fill channles in on the packet
     * @param channels - the data of the channels
     */
    void FillChannels(const VelodyneData::t_channel_data& channels);

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
	VLPMessage(int returnMode, int dataSource);

	virtual ~VLPMessage() = default;

	virtual void FillMessage(const VelodyneData& data) override;

	virtual int GetMessageSize() const override;
};

#endif // VLPSMESSAGE_H