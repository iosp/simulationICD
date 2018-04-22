#ifndef VLP_STRUCTS_H
#define VLP_STRUCTS_H

/*
* VLPStructs.h
* Holds structs that are in use with VLPControl
* Author: Binyamin Appelbaum
* Date: 07.03.18
*/

static const int NUM_OF_VLP_DATA_CHANNELS_IN_BLOCK = 32;
static const int NUM_OF_VLP_DATA_BLOCKS = 12;

struct VLPDataPacket {
	struct VLPDataBlock {
		struct DataChannel {
			unsigned char distance[2]{};
			unsigned char reflectivity{};
		};

		short flag = 0xEEFF; // same for every block
		unsigned char azimuth[2]{};
		DataChannel dataRecords[NUM_OF_VLP_DATA_CHANNELS_IN_BLOCK];
	};
	
	VLPDataBlock dataBlocks[NUM_OF_VLP_DATA_BLOCKS];
	unsigned char timeStamp[4]{}; // time stamp is how much seconds passed after the last round hour
	unsigned char factory[2]{};
};

#endif // VLP_STRUCTS_H