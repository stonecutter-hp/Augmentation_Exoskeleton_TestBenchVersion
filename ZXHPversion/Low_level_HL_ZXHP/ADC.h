/***********************************************************************
 * The ADC pin definition and processing function
 **********************************************************************/

#ifndef _ADC__H__
#define _ADC__H__

#include <AD7173.h>
#include "GenerIO.h"

// Ch0~Ch3 is for load cell
// Ch4 is for battery voltage detection with attenuation ratio 1:11
// Ch5~Ch9 is for motor driver signal detection with attenuation ratio 1:2
// Ch10~Ch15 is for potentiometer with no attenuation
// --------------------- CH0 CH1 CH2 CH3   CH4   CH5 CH6 CH7 CH8 CH9 CH10 CH11 CH12 CH13 CH14 CH15
const int attRatio[16] = {1,  1,  1,  1,  22.5,   2,  2,  2,  2,  2,   1,   1,   1,   1,   1,   1};
#define ADC_SS PA4           //SPI1_NSS-CS 
#define ADC_MISO PA6         //SPI1_MISO-DOUT/RDY
#define ENABLED_CH 16        //sum of ADC Channels
#define ENABLED_CH_Work 8    //Practical working channels
#define MotorCurrL 6         //ADC channel assigned for left motor current feedback
#define MotorCurrR 8         //ADC channel assigned for right motor current feedback
#define MotorVeloL 5         //ADC channel assigned for left motor velocity feedback
#define MotorVeloR 7         //ADC channel assigned for right motor velocity feedback
#define PotentioLP1 10       //ADC channel assigned for left potentiometer 1(P1)
#define PotentioRP2 11       //ADC channel assigned for right potentiometer 1(P2)
#define TorqueSensorL 12     //ADC channel assigned for left torque sensor
#define TorqueSensorR 13     //ADC channel assigned for right torque sensor
#define ForceSensorL 14      //ADC channel assigned for left force sensor
#define ForceSensorR 15      //ADC channel assigned for right force sensor
#define FilterCycles 20      //FilterCycles for moving/exponetial average filter

// Parameters for ADC raw data processing for sensors
#define PotentioLP1_Sensitivity 105              // 120 = 300/2.5 (deg/v); for left potentiometer calibration 
#define PotentioRP2_Sensitivity 103              // 120 = 300/2.5 (deg/v); for right potentiometer calibration 
#define TorqueSensorL_Sensitivity -31.6          // Nm/v, for left torque sensor calibration 
#define TorqueSensorL_Offset 1.2614              // v, for left torque sensor calibration 
#define TorqueSensorR_Sensitivity 31.7           // Nm/v, for right torque sensor calibration 
#define TorqueSensorR_Offset 1.33404             // v, for right torque sensor calibration 
#define ForceSensorL_Sensitivity 1       // v/N, for left force sensor calibration
#define ForceSensorR_Sensitivity 1       // v/N, for right force sensor calibration

/* ADC conversion data and STATUS register */
extern byte ADC_data[ENABLED_CH][4];             // store raw data from ADC
extern bool ADC_update;                          // ADC_update enable flag 
extern float ADC_updateFre;                      // ADC feedback update frequency
extern unsigned long ADC_value[ENABLED_CH];      // store ADC value in long format  
extern double Aver_ADC_value[ENABLED_CH];        // store the transferred ADC value for calculation
extern double Aver_ADC_value_Prev[ENABLED_CH];   // Store last time processed ADC feedaback
extern double Aver_ADC_mean_Prev[ENABLED_CH];    // Store last time mean of ADC feedback
// Notice in ZXHP version EXO:
// some ADC channels are for High-level control with high-level controlfrequency time interval
// some ADC channels are for Low-level control with low-level control frequency time interval
// A window store the historical unfiltered ADC value of certain cycle for ADC feedback moving average  
extern double Aver_ADC_value_unfiltered[ENABLED_CH][FilterCycles];
// A window store the historical (maybe)filtered ADC value of certain cycle for standard deviation calculation
extern double Aver_ADC_value_filtered[ENABLED_CH][FilterCycles];
/* load cell force transfer */
extern double LoadCell[4];                      // store the transferred force value


/**
 * ADC initialization for channel mode configuration
 */
void ADC_Init(void); 

/**
 * Get the ADC value of all channels once
 */
void getADC(void);

/**
 * Get average value from ADC for cycles
 * @para int - times: the cycles ADC go through before give you the detected value
 */
void getADCaverage(int times);

/**
 * Initial the matrix for average filter Aver_ADC_value_unfiltered[ENABLED_CH][FilterCycles]
 */
void Filter_Init(void);

/**
 * Mean Moving filter for the ADC value within certain cycles
 * @param int - channel: 0~ENABLED_CH-1
 * @param int - cycles: 1~FilterCycles
 * ATTENTION: When using the moving mean filter, the initial value in the filter window should be initialized before the main loop to ensure no mutation of the filtered feedabck
 */
void MovingAverageFilter(int channel, int cycles);

/**
 * Exponential moving average filter for the ADC value within certain cycles
 * @param int - channel: 0~ENABLED_CH-1
 * @param float - alpha: weighting decreasing coefficient (0~1)
 */
void ExponentialMovingFilter(int channel, float alpha);

/**
 * Calculate standard deviation for the ADC value within certain cycles
 * @param int - channel: 0~ENABLED_CH-1
 * @param int - cycles: 1~FilterCycles
 */
double ADCStdCal(int channel, int cycles);

#endif
