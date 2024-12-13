#ifndef __JAILO
#define __JAILO
int MPU6050_ADDR=0x68; // または 0x69
#define MPU6050_SMPLRT_DIV 0x19
#define MPU6050_CONFIG 0x1a
#define MPU6050_GYRO_CONFIG 0x1b
#define MPU6050_ACCEL_CONFIG 0x1c
#define MPU6050_PWR_MGMT_1 0x6b

int16_t raw_acc_x, raw_acc_y, raw_acc_z, raw_t, raw_gyro_x, raw_gyro_y, raw_gyro_z;
float absAccelerometer;
float acc_x, acc_y, acc_z, pitch, roll, pitch_0, roll_0,pitch_feed,roll_feed; // ピッチとロールの角度用変数を追加
int j_flag=0,j_ON=0,feed_on_flag=0,feed_off_flag=0;

#endif