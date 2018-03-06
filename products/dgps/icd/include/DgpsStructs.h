#ifndef DGPS_STRUCTS_H
#define DGPS_STRUCTS_H

/*
* DgpsStructs.h
* Holds structs that are in use with DgpsCommunication
* Author: Binyamin Appelbaum
* Date: 15.01.18
* 
*/

#define CRC32_POLYNOMIAL 0xEDB88320L


/* LatLonAlt */
typedef struct{
	float latitude;
	float longitude;
	float altitude;
} LatLonAlt;

/* E_GPS_TIME_STATUS */
typedef enum {
	E_GPS_TIME_STATUS_UNKNOWN                      = 20,
	E_GPS_TIME_STATUS_APPROXIMATE                  = 60,
	E_GPS_TIME_STATUS_COARSEADJUSTING              = 80,
	E_GPS_TIME_STATUS_COARSE                       = 100,
	E_GPS_TIME_STATUS_COARSESTEERING               = 120,
	E_GPS_TIME_STATUS_FREEWHEELING                 = 130,
	E_GPS_TIME_STATUS_FINEADJUSTING                = 140,
	E_GPS_TIME_STATUS_FINE                         = 160,
	E_GPS_TIME_STATUS_FINESTEERING                 = 180,
	E_GPS_TIME_STATUS_SATTIME                      = 200
}E_GPS_TIME_STATUS;

/* E_MESSAGE_ID_INPUT_DGPS_DLV3 */
typedef enum {
	E_MESSAGE_ID_INPUT_DGPS_DLV3_BESTPOS           = 42,
	E_MESSAGE_ID_INPUT_DGPS_DLV3_BESTVEL           = 99,
	E_MESSAGE_ID_INPUT_DGPS_DLV3_TIME              = 101,
	E_MESSAGE_ID_INPUT_DGPS_DLV3_BESTXYZ           = 241
}E_MESSAGE_ID_INPUT_DGPS_DLV3;

/* E_ADVANCE_RTK_VERIFIED */
typedef enum {
	E_ADVANCE_RTK_VERIFIED_NOT_VERIFIED            = 0,
	E_ADVANCE_RTK_VERIFIED_VERIFIED                = 1
}E_ADVANCE_RTK_VERIFIED;

/* E_ANTENA_STATUS */
typedef enum{
	NO_ANTENA_WARNING = 0,
	ANTENA_INFORMATION_IS_MISSING = 1
}E_ANTENA_STATUS;

/* E_PSEUDORANGE_LONO_CORRECTION */
typedef enum {
	E_PSEUDORANGE_LONO_CORRECTION_UNKNOWN          = 0,
	E_PSEUDORANGE_LONO_CORRECTION_KLOBUCHAR_BROADCAST= 1,
	E_PSEUDORANGE_LONO_CORRECTION_SBAS_BROADCAST   = 2,
	E_PSEUDORANGE_LONO_CORRECTION_MULTI_FREQUENCY_COMPUTED= 3,
	E_PSEUDORANGE_LONO_CORRECTION_PSRDIFF_CORRECTION= 4,
	E_PSEUDORANGE_LONO_CORRECTION_NOVATEL_BLENDED_LONO_VALUE= 5
}E_PSEUDORANGE_LONO_CORRECTION;

/* E_SOLUTION_STATUS */
typedef enum {
	E_SOLUTION_STATUS_SOL_COMPUTED                 = 0,
	E_SOLUTION_STATUS_INSUFFICIENT_OBS             = 1,
	E_SOLUTION_STATUS_NO_CONVERGENCE               = 2,
	E_SOLUTION_STATUS_SINGULARITY                  = 3,
	E_SOLUTION_STATUS_COV_TRACE                    = 4,
	E_SOLUTION_STATUS_TEST_DIST                    = 5,
	E_SOLUTION_STATUS_COLD_START                   = 6,
	E_SOLUTION_STATUS_V_H_LIMIT                    = 7,
	E_SOLUTION_STATUS_VARIANCE                     = 8,
	E_SOLUTION_STATUS_RESIDUALS                    = 9,
	E_SOLUTION_STATUS_DELTA_POS                    = 10,
	E_SOLUTION_STATUS_NEGATIVE_VAR                 = 11,
	E_SOLUTION_STATUS_RESERVED                     = 12,
	E_SOLUTION_STATUS_INTEGRITY_WARNING            = 13,
	E_SOLUTION_STATUS_INS_SOLUTION_STATUS_VALUES   = 14,
	E_SOLUTION_STATUS_INS_SOLUTION_STATUS_VALUES1  = 15,
	E_SOLUTION_STATUS_INS_SOLUTION_STATUS_VALUES2  = 16,
	E_SOLUTION_STATUS_INS_SOLUTION_STATUS_VALUES3  = 17,
	E_SOLUTION_STATUS_PENDING                      = 18,
	E_SOLUTION_STATUS_INVALID_FIX                  = 19,
	E_SOLUTION_STATUS_UNAUTHORIZED                 = 20,
	E_SOLUTION_STATUS_ANTENNA_WARNING              = 21
}E_SOLUTION_STATUS;

/* E_POSITION_OR_VELOCITY_TYPE */
typedef enum {
	E_POSITION_OR_VELOCITY_TYPE_NONE               = 0,
	E_POSITION_OR_VELOCITY_TYPE_FIXEDPOS           = 1,
	E_POSITION_OR_VELOCITY_TYPE_FIXEDHEIGHT        = 2,
	E_POSITION_OR_VELOCITY_TYPE_DOPPLER_VELOCITY   = 8,
	E_POSITION_OR_VELOCITY_TYPE_SINGLE             = 16,
	E_POSITION_OR_VELOCITY_TYPE_PSRDIFF            = 17,
	E_POSITION_OR_VELOCITY_TYPE_WAAS               = 18,
	E_POSITION_OR_VELOCITY_TYPE_PROPAGATED         = 19,
	E_POSITION_OR_VELOCITY_TYPE_OMNISTAR           = 20,
	E_POSITION_OR_VELOCITY_TYPE_L1_FLOAT           = 32,
	E_POSITION_OR_VELOCITY_TYPE_IONOFREE_FLOAT     = 33,
	E_POSITION_OR_VELOCITY_TYPE_NARROW_FLOAT       = 34,
	E_POSITION_OR_VELOCITY_TYPE_L1_INT             = 48,
	E_POSITION_OR_VELOCITY_TYPE_WIDE_INT           = 49,
	E_POSITION_OR_VELOCITY_TYPE_NARROW_INT         = 50,
	E_POSITION_OR_VELOCITY_TYPE_RTK_DIRECT_INS     = 51,
	E_POSITION_OR_VELOCITY_TYPE_INS                = 52,
	E_POSITION_OR_VELOCITY_TYPE_INS_PSRSP          = 53,
	E_POSITION_OR_VELOCITY_TYPE_INS_PSRDIFF        = 54,
	E_POSITION_OR_VELOCITY_TYPE_INS_RTKFLOAT       = 55,
	E_POSITION_OR_VELOCITY_TYPE_INS_RTKFIXED       = 56,
	E_POSITION_OR_VELOCITY_TYPE_OMNISTAR_HP        = 64,
	E_POSITION_OR_VELOCITY_TYPE_OMNISTAR_XP        = 65,
	E_POSITION_OR_VELOCITY_TYPE_CDGPS              = 66
}E_POSITION_OR_VELOCITY_TYPE;

/* E_DATUM_DGPS */
typedef enum {
	E_DATUM_DGPS_WGS84                             = 61
}E_DATUM_DGPS;

/* EXTENDED_SOLUTION_STATUS_STRUCT */
typedef struct {
	E_ADVANCE_RTK_VERIFIED                          Bit_AdVance_RTK_Verified; //
	E_PSEUDORANGE_LONO_CORRECTION                   BITS_Pseudorange_lono_Correction; //
	E_ANTENA_STATUS									BIT_Antena_Status;
} EXTENDED_SOLUTION_STATUS_STRUCT;

/* SIGNAL_USED_MASK_STRUCT */
typedef struct {
	unsigned char                                   Bit_GPS_L1_used_in_Solution; //
	unsigned char                                   Bit_GPS_L2_used_in_Solution; //
	unsigned char                                   Bit_GPS_L5_used_in_Solution; //
	unsigned char                                   Bit_Reserved; //
	unsigned char                                   Bit_GLONASS_L1_used_in_Solution; //
	unsigned char                                   Bit_GLONASS_L2_used_in_Solution; //
	unsigned char                                   TWO_BIT_RESERVED; //
} SIGNAL_USED_MASK_STRUCT;

/* DGPS_HEADER */
typedef struct {
	char                                            Sync; //
	char                                            Sync1; //
	char                                            Sync2; //
	unsigned char                                   Header_Lgth; //
	E_MESSAGE_ID_INPUT_DGPS_DLV3                    Message_ID; //
	char                                            Message_Type; //
	unsigned char                                   Port_Address; //
	unsigned short                                  Message_Length; //
	unsigned short                                  Sequence; //
	unsigned char                                   Idle_Time; //
	E_GPS_TIME_STATUS                               Time_Status; //
	unsigned short                                  Week; //
	int                                            ms; // Time  tag for fields sourced from BESTVEL
	unsigned int                                   Receiver_Status; //
	unsigned short                                  Two_Byte_Reserved; //
	unsigned short                                  Receiver_SW_Version; //
} DGPS_HEADER;

/* BESTVEL */
typedef struct {
	DGPS_HEADER                                  	HEADER; // Log header
	E_SOLUTION_STATUS                               sol_stat; // Solution status
	E_POSITION_OR_VELOCITY_TYPE                     vel_type; // Velocity type
	float                                           latency; // measure of the latency in the velocity time tag in seconds
	float                                           age; // differential age in seconds
	double                                          hor_spd; // horizontal speed over ground, in meters per second
	double                                          trk_gnd; // Actual direction of motion over ground with respect to True North, deg
	double                                          vert_spd; // Veritical speed , meters per seconds
	float                                           Four_Float_Reserved; //
	unsigned int                                    CRC; //
} PHS_BESTVEL;

/* BESTPOS */
typedef struct {
	DGPS_HEADER                                   	HEADER; // Log header
	E_SOLUTION_STATUS                               sol_stat; // Solution status
	E_POSITION_OR_VELOCITY_TYPE                     pos_type; // Position type
	double                                          lat_Dgps; //
	double                                          lon_Dgps; //
	double                                          hgt_Dgps; //
	float                                           undulation; //
	E_DATUM_DGPS                                    datum_id; //
	float                                           lat_sd; // latitude standard deviation
	float                                           lon_sd; // longitude standard deviation
	float                                           hgt_sd; // hight standard deviation
	unsigned int                                    stn_id; // Base station ID
	float                                           diff_age; // differential age in seconds
	float                                           sol_age; // solution age in seconds
	unsigned char                                   N_SVs; // number of satellite vehicles tracked
	unsigned char                                   N_solnSVs; // number of satellite vehicles used in solution
	unsigned char                                   N_ggL1; // NUmber of GPS plus GLONASS L1 used in solution
	unsigned char                                   N_ggL1L2; // Number of gps plus GLONASS L1 and L2 used in solution
	unsigned char                                   Byte_Reserved; //
	EXTENDED_SOLUTION_STATUS_STRUCT                 ext_sol_state; //
	unsigned char                                   Byte_Reserved1; //
	SIGNAL_USED_MASK_STRUCT                         sig_mask; //
	unsigned int                                    CRC; //
} PHS_BESTPOS;


#endif // DGPS_STRUCTS_H