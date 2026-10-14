#ifndef _MPU6050_H
#define _MPU6050_H
#define MPU6050_ADDR        0x68    // AD0拉低；AD0接3.3V改成0x69
#define MPU_PWR_MGMT_1      0x6B
#define MPU_ACCEL_XOUT_H    0x3B
#define MPU_WHO_AM_I        0x75
extern uint8_t mpu_read_id;
typedef struct
{
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
} MPU_DataTypeDef;
uint8_t MPU6050_WriteReg(SoftIIC_HandleTypeDef *hi2c,uint8_t reg_addr, uint8_t data);
uint8_t MPU6050_ReadReg(SoftIIC_HandleTypeDef *hi2c,uint8_t reg_addr, uint8_t *p_data,uint8_t len);
uint8_t MPU6050_Init(SoftIIC_HandleTypeDef *hi2c);
void MPU6050_ReadData(SoftIIC_HandleTypeDef *hi2c, MPU_DataTypeDef *dat);

#endif