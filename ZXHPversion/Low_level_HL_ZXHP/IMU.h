/***********************************************************************
 * IMU data collectiong function
 * System model parameters
 **********************************************************************/

#ifndef __IMU_H___
#define __IMU_H___

#include "IIC.h"

/**************************************** IMU parameters definition ********************************/
#define rollChan  0                // Notice that seems the practical pitch angle corresponds to rollChan in this program
#define pitchChan 1
#define yawChan   2
#define AddrIMUA  0x50
#define AddrIMUB  0x51
#define AddrIMUC  0x52
#define IMU_UpdateFre 200          // Hz, Assumed IMU data updated frequency
#define IMUFilterCycles 6
/* IMU alogorithm 6 axis or 9 axis */
typedef enum {
  IMU9Axis = 0,
  IMU6Axis = 1
} IMUAlo;
extern IMUAlo OperaitonAloIMUA;     
extern IMUAlo OperaitonAloIMUB; 
extern IMUAlo OperaitonAloIMUC; 

extern unsigned char yaw2zero[2];  // The command for IMU yaw angle return to zero (only for 6-axis algorithm)

extern unsigned char angleTempA[6];   // store the raw data get from IMU A(addr 0x50)
extern unsigned char angleTempB[6];   // store the raw data get from IMU B(addr 0x51)
extern unsigned char angleTempC[6];   // store the raw data get from IMU C(addr 0x52)
extern unsigned char velTempA[6];     // store the raw data get from IMU A(addr 0x50)
extern unsigned char velTempB[6];     // store the raw data get from IMU B(addr 0x51)
extern unsigned char velTempC[6];     // store the raw data get from IMU C(addr 0x52)
extern unsigned char accTempA[6];     // store the raw data get from IMU A(addr 0x50)
extern unsigned char accTempB[6];     // store the raw data get from IMU B(addr 0x51)
extern unsigned char accTempC[6];     // store the raw data get from IMU C(addr 0x52)

extern float angleActualA[3];         // store the angle of IMU A(addr 0x50) for calculation
extern float angleActualB[3];         // store the angle of IMU B(addr 0x51) for calculation
extern float angleActualC[3];         // store the angle of IMU C(addr 0x52) for calculation
extern float angleActual_p[3][3];     // store the last time angle of IMU C(addr 0x52) for calculation of velocity

extern float velActualA[3];           // store the velocity of IMU A(addr 0x50)
extern float velActualB[3];           // store the velocity of IMU B(addr 0x51)
extern float velActualC[3];           // store the velocity of IMU C(addr 0x52)

extern float accActualA[3];           // store the acceleration of IMU A(addr 0x50)
extern float accActualB[3];           // store the acceleration of IMU B(addr 0x51)
extern float accActualC[3];           // store the acceleration of IMU C(addr 0x52)

extern double IMUA_value_filtered[3][IMUFilterCycles];  // store data from IMUA for filtering
extern double IMUB_value_filtered[3][IMUFilterCycles];  // store data from IMUB for filtering
extern double IMUC_value_filtered[3][IMUFilterCycles];  // store data from IMUC for filtering
extern double IMU_value_Prev[3][3];                     // store last time angle of 3 IMU * 3 channel

/**
 * IMU angle feedback return to zero
 */
void IMU_Init(void);

/**
 * Get euler angle from first IMU
 */
void getIMUangleL(void);

/**
 * Get euler angle from second IMU
 */
void getIMUangleR(void);

/**
 * Get euler angle from third IMU
 */
void getIMUangleT(void);

/**
 * Get euler angle from all IMUs
 */
void getIMUangle(void);

/**
 * Get angular velocity from first IMU
 */
void getIMUvelL(void);

/**
 * Get angular velocity from second IMU
 */
void getIMUvelR(void);

/**
 * Get angular velocity from third IMU
 */
void getIMUvelT(void);

/**
 * Get angular velocity from all IMUs
 */
void getIMUvel(void);

/**
 * Get angular acceleration from third IMU
 */
void getIMUaccT(void);

/**
 * Yaw angle set to zero for first IMU
 * Can only be set to zero under 6-axis mode
 */
void set2zeroL(void);

/**
 * Yaw angle set to zero for second IMU
 * Can only be set to zero under 6-axis mode
 */
void set2zeroR(void);

/**
 * Yaw angle set to zero for third IMU
 * Can only be set to zero under 6-axis mode
 */
void set2zeroT(void);

/**
 * Mean Moving filter for the IMUA feedback
 * @param int - channel: rollChan/pitchChan/yawChan
 * @param int - cycles: 1~IMUFilterCycles
 */
void MovingAverFilterIMUA(int channel, int cycles);

/**
 * Mean Moving filter for the IMUB feedback
 * @param int - channel: rollChan/pitchChan/yawChan
 * @param int - cycles: 1~IMUFilterCycles
 */
void MovingAverFilterIMUB(int channel, int cycles);

/**
 * Mean Moving filter for the IMUC feedback
 * @param int - channel: rollChan/pitchChan/yawChan
 * @param int - cycles: 1~IMUFilterCycles
 */
void MovingAverFilterIMUC(int channel, int cycles);


#endif
