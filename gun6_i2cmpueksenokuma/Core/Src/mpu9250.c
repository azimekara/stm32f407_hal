/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "mpu9250.h"

#define max(a,b) \
 ({ __typeof__ (a) _a = (a); \
     __typeof__ (b) _b = (b); \
   _a > _b ? _a : _b; })
   
#define SEC2US 1e6
#define SEC2MS 1e3
#define US2MS 1e-3

#define _MAX4468_SHDN_PIN 29 // BCM 21
#define _MCP9250_PRI 81

double Ts = 0.01 * SEC2US;
unsigned int N = 1000;
unsigned int n = 0;

short accl_x, accl_y, accl_z;
double* accl_x_buff; double* accl_y_buff; double* accl_z_buff;
short gyro_x, gyro_y, gyro_z;
double* gyro_x_buff; double* gyro_y_buff; double* gyro_z_buff;
short magn_x, magn_y, magn_z;
double* magn_x_buff; double* magn_y_buff; double* magn_z_buff;
short magn_asax, magn_asay, magn_asaz;

double accl_scale, gyro_scale, magn_scale;

double tic, toc;

int mpu9250inst, ak8963inst;

char init_seq = 0;

PI_THREAD(readThread)
{
  piHiPri(_MCP9250_PRI+1);
  while(1)
  {
    accl_x = (wiringPiI2CReadReg8(mpu9250inst, MPU9250_ACCEL_XOUT_H)<<8) + (unsigned short)wiringPiI2CReadReg8(mpu9250inst, MPU9250_ACCEL_XOUT_L);
    accl_y = (wiringPiI2CReadReg8(mpu9250inst, MPU9250_ACCEL_YOUT_H)<<8) + (unsigned short)wiringPiI2CReadReg8(mpu9250inst, MPU9250_ACCEL_YOUT_L);
    accl_z = (wiringPiI2CReadReg8(mpu9250inst, MPU9250_ACCEL_ZOUT_H)<<8) + (unsigned short)wiringPiI2CReadReg8(mpu9250inst, MPU9250_ACCEL_ZOUT_L);
    
    gyro_x = (wiringPiI2CReadReg8(mpu9250inst, MPU9250_GYRO_XOUT_H)<<8) + (unsigned short)wiringPiI2CReadReg8(mpu9250inst, MPU9250_GYRO_XOUT_L);
    gyro_y = (wiringPiI2CReadReg8(mpu9250inst, MPU9250_GYRO_YOUT_H)<<8) + (unsigned short)wiringPiI2CReadReg8(mpu9250inst, MPU9250_GYRO_YOUT_L);
    gyro_z = (wiringPiI2CReadReg8(mpu9250inst, MPU9250_GYRO_ZOUT_H)<<8) + (unsigned short)wiringPiI2CReadReg8(mpu9250inst, MPU9250_GYRO_ZOUT_L);
    
    if ((wiringPiI2CReadReg8(ak8963inst, AK8963_ST1) & 0x01) == 1)
    {
    	magn_x = (wiringPiI2CReadReg8(mpu9250inst, AK8963_HXH)<<8) + (unsigned short)wiringPiI2CReadReg8(mpu9250inst, AK8963_HXL);
    	magn_y = (wiringPiI2CReadReg8(mpu9250inst, AK8963_HYH)<<8) + (unsigned short)wiringPiI2CReadReg8(mpu9250inst, AK8963_HYL);
    	magn_z = (wiringPiI2CReadReg8(mpu9250inst, AK8963_HZH)<<8) + (unsigned short)wiringPiI2CReadReg8(mpu9250inst, AK8963_HZL);
    }
    
    init_seq=1;
    if(n>=(N-1))
      break;
  }
}

int main(int argc, char *argv[])
{
  for(n=0; n<=argc; n=n+1)
  {
    switch(n) 
    {
      case 1: Ts=atof(argv[n])* SEC2US;
      case 2: N=atoi(argv[n]);
    }
  }
  
  accl_x_buff = (double*)calloc(N, sizeof(double));
  accl_y_buff = (double*)calloc(N, sizeof(double));
  accl_z_buff = (double*)calloc(N, sizeof(double));
  gyro_x_buff = (double*)calloc(N, sizeof(double));
  gyro_y_buff = (double*)calloc(N, sizeof(double));
  gyro_z_buff = (double*)calloc(N, sizeof(double));
  magn_x_buff = (double*)calloc(N, sizeof(double));
  magn_y_buff = (double*)calloc(N, sizeof(double));
  magn_z_buff = (double*)calloc(N, sizeof(double));
  
  wiringPiSetup();
  piHiPri(_MCP9250_PRI);
  
  mpu9250inst = wiringPiI2CSetup(MPU9250_DEFAULT_ADDRESS);

  wiringPiI2CWriteReg8(mpu9250inst, MPU9250_PWR_MGMT_1, 0);
  
  // Accel Range +-2g
  wiringPiI2CWriteReg8(mpu9250inst, MPU9250_ACCEL_CONFIG, 0);
  accl_scale = 16384.0;
  // Accel Range +-4g
  // wiringPiI2CWriteReg8(mpu9250inst,MPU9250_ACCEL_CONFIG, 8);
  // accl_scale = 8192.0;
  // Accel Range +-8g
  // wiringPiI2CWriteReg8(mpu9250inst,MPU9250_ACCEL_CONFIG, 16);
  // accl_scale = 4096.0;
  // Accel Range +-16g
  // wiringPiI2CWriteReg8(mpu9250inst, MPU9250_ACCEL_CONFIG, 24);
  // accl_scale = 2048.0;

  // Filter 420 Hz
  wiringPiI2CWriteReg8(mpu9250inst, MPU9250_ACCEL_CONFIG2, 15);
  
  // Gyro Range +-250 degrees/s
  wiringPiI2CWriteReg8(mpu9250inst, MPU9250_GYRO_CONFIG, 0);
  gyro_scale = 131.0;
  // Gyro Range +-500 degrees/s
  // wiringPiI2CWriteReg8(mpu9250inst, MPU9250_GYRO_CONFIG, 8);
  // gyro_scale = 65.5;
  // Gyro Range +-1000 degrees/s
  // wiringPiI2CWriteReg8(mpu9250inst, MPU9250_GYRO_CONFIG, 16);
  // gyro_scale = 32.8;
  // Gyro Range +-2000 degrees/s
  // wiringPiI2CWriteReg8(mpu9250inst, MPU9250_GYRO_CONFIG, 24);
  // gyro_scale = 16.4;
  
  // DLPF Bandwidth = 10
  wiringPiI2CWriteReg8(mpu9250inst, MPU9250_CONFIG, 5);
  
  // Enable Magnetometer (address 0x0c)
  wiringPiI2CWriteReg8(mpu9250inst, MPU9250_INT_PIN_CFG, 2);

  ak8963inst = wiringPiI2CSetup(AK8963_DEFAULT_ADDRESS);
  
  // Set Fuse ROM access mode
  wiringPiI2CWriteReg8(ak8963inst, AK8963_CNTL, 0x0F);
  
  // Read Magnetic sensor axis sensitivity adjustment value
  magn_asax = wiringPiI2CReadReg8(ak8963inst, AK8963_ASAX);
  magn_asay = wiringPiI2CReadReg8(ak8963inst, AK8963_ASAY);
  magn_asaz = wiringPiI2CReadReg8(ak8963inst, AK8963_ASAZ);
  
  // Set power-down mode before the transition to another mode.
  wiringPiI2CWriteReg8(ak8963inst, AK8963_CNTL, 0x00);
  
  // Set Continuous measurement mode 0x12 - 8Hz & 16-bit; 0x16 - 100 Hz & 16-bit
  wiringPiI2CWriteReg8(ak8963inst, AK8963_CNTL, 0x16);

  // Magnetometer Range +-4.8 mT
  magn_scale = 6826.7;
  
  // Create read thread
  piThreadCreate(readThread);
  
  // Sample input
  while(init_seq==0);
  for(n=0; n<N; n=n+1)
  {
    tic = micros();
    
    accl_x_buff[n] = (double)accl_x/accl_scale;
    accl_y_buff[n] = (double)accl_y/accl_scale;
    accl_z_buff[n] = (double)accl_z/accl_scale;
    
    gyro_x_buff[n] = (double)gyro_x/gyro_scale;
    gyro_y_buff[n] = (double)gyro_y/gyro_scale;
    gyro_z_buff[n] = (double)gyro_z/gyro_scale;
    
  	magn_x_buff[n] = (double)magn_x/magn_scale;
  	magn_y_buff[n] = (double)magn_y/magn_scale;
  	magn_z_buff[n] = (double)magn_z/magn_scale;

    toc = micros() -tic;
    delayMicroseconds(max(Ts-toc, 0));
  }
  
  //Save data
  FILE *f_accl_x; FILE *f_accl_y; FILE *f_accl_z;
  f_accl_x = fopen("/home/cil/.sensor_drivers_c/output/mpu9250_acclx.data", "wb");
  f_accl_y = fopen("/home/cil/.sensor_drivers_c/output/mpu9250_accly.data", "wb");
  f_accl_z = fopen("/home/cil/.sensor_drivers_c/output/mpu9250_acclz.data", "wb");
  FILE *f_gyro_x; FILE *f_gyro_y; FILE *f_gyro_z;
  f_gyro_x = fopen("/home/cil/.sensor_drivers_c/output/mpu9250_gyrox.data", "wb");
  f_gyro_y = fopen("/home/cil/.sensor_drivers_c/output/mpu9250_gyroy.data", "wb");
  f_gyro_z = fopen("/home/cil/.sensor_drivers_c/output/mpu9250_gyroz.data", "wb");
  FILE *f_magn_x; FILE *f_magn_y; FILE *f_magn_z;
  f_magn_x = fopen("/home/cil/.sensor_drivers_c/output/mpu9250_magnx.data", "wb");
  f_magn_y = fopen("/home/cil/.sensor_drivers_c/output/mpu9250_magny.data", "wb");
  f_magn_z = fopen("/home/cil/.sensor_drivers_c/output/mpu9250_magnz.data", "wb");
  
  fwrite(accl_x_buff, sizeof(*accl_x_buff), N, f_accl_x);
  fwrite(accl_y_buff, sizeof(*accl_y_buff), N, f_accl_y);
  fwrite(accl_z_buff, sizeof(*accl_z_buff), N, f_accl_z);
  fwrite(gyro_x_buff, sizeof(*gyro_x_buff), N, f_gyro_x);
  fwrite(gyro_y_buff, sizeof(*gyro_y_buff), N, f_gyro_y);
  fwrite(gyro_z_buff, sizeof(*gyro_z_buff), N, f_gyro_z);
  fwrite(magn_x_buff, sizeof(*magn_x_buff), N, f_magn_x);
  fwrite(magn_y_buff, sizeof(*magn_y_buff), N, f_magn_y);
  fwrite(magn_z_buff, sizeof(*magn_z_buff), N, f_magn_z);
  
  fclose(f_accl_x);
  fclose(f_accl_y);
  fclose(f_accl_z);
  fclose(f_gyro_x);
  fclose(f_gyro_y);
  fclose(f_gyro_z);
  fclose(f_magn_x);
  fclose(f_magn_y);
  fclose(f_magn_z);
  
  free(accl_x_buff);
  free(accl_y_buff);
  free(accl_z_buff);
  free(gyro_x_buff);
  free(gyro_y_buff);
  free(gyro_z_buff);
  free(magn_x_buff);
  free(magn_y_buff);
  free(magn_z_buff);
  
  return 0;
}
*/
