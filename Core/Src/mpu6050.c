#include "stm32f1xx_hal.h"
#include "i2c.h"
#include "mpu6050.h"
uint8_t mpu_read_id = 0;
uint8_t MPU6050_WriteReg(SoftIIC_HandleTypeDef *hi2c,uint8_t reg_addr, uint8_t data)
{
    uint8_t ack;
    SoftIIC_Start(hi2c);
    ack = SoftIIC_Write_Byte(hi2c,0x68 << 1);
    if(ack !=0)
    {
        SoftIIC_Stop(hi2c);
        return 1;
    }
    ack = SoftIIC_Write_Byte(hi2c,reg_addr);
    if(ack !=0)
    {
        SoftIIC_Stop(hi2c);
        return 2;
    }
    ack = SoftIIC_Write_Byte(hi2c,data);
    if(ack !=0)
    {
        SoftIIC_Stop(hi2c);
        return 3;
    }
    SoftIIC_Stop(hi2c);
    return 0;
}

uint8_t MPU6050_ReadReg(SoftIIC_HandleTypeDef *hi2c,uint8_t reg_addr, uint8_t *p_data,uint8_t len)
{
    uint8_t ack,i;
    SoftIIC_Start(hi2c);
    ack = SoftIIC_Write_Byte(hi2c,0x68 << 1); //0xD0 写地址
    if(ack != 0)
    {
        SoftIIC_Stop(hi2c);
        return 1;
    }
    ack = SoftIIC_Write_Byte(hi2c, reg_addr);
    if(ack != 0)
    {
        SoftIIC_Stop(hi2c);
        return 2;
    }
    // =========新增：把SCL拉高，等待稳定，才能发重复起始=========
    HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_SET);
    SoftIIC_Delay_us(4);
    // ==========================================================
    SoftIIC_Start(hi2c); //重复起始
    ack = SoftIIC_Write_Byte(hi2c,(0x68 << 1)|0x01); //0xD1读地址
    if(ack != 0)
    {
        SoftIIC_Stop(hi2c);
        return 3;
    }
    //循环读，最后一个字节发NACK，前面字节发ACK
    for(i=0;i<len;i++)
    {
        if(i == len - 1)
        {
            *p_data = SoftIIC_Read_Byte(hi2c,1); //最后1字节 NACK
        }
        else
        {
            *p_data = SoftIIC_Read_Byte(hi2c,0); //前面字节 ACK
        }
        p_data++;
    }
    SoftIIC_Stop(hi2c);
    return 0;
}
uint8_t MPU6050_Init(SoftIIC_HandleTypeDef *hi2c)
{
    uint8_t id = 0;
    //唤醒MPU，退出休眠
    if(MPU6050_WriteReg(hi2c, MPU_PWR_MGMT_1, 0x00))
    {
        mpu_read_id = 0;
        return 1; //写唤醒寄存器失败
    }
    HAL_Delay(100);
    if(MPU6050_ReadReg(hi2c, MPU_WHO_AM_I, &id, 1))
    {
        mpu_read_id = 0;
        return 2; //读ID失败
    }
    mpu_read_id = id;
    if(id != 0x68)
    {
        return 3; //ID不匹配
    }
    return 0;
}

void MPU6050_ReadData(SoftIIC_HandleTypeDef *hi2c, MPU_DataTypeDef *dat)
{
    uint8_t buf[14];
    MPU6050_ReadReg(hi2c, MPU_ACCEL_XOUT_H, buf,14);
    dat->ax = (int16_t)((buf[0] <<8) | buf[1]);
    dat->ay = (int16_t)((buf[2] <<8) | buf[3]);
    dat->az = (int16_t)((buf[4] <<8) | buf[5]);
    dat->gx = (int16_t)((buf[8] <<8) | buf[9]);
    dat->gy = (int16_t)((buf[10]<<8) | buf[11]);
    dat->gz = (int16_t)((buf[12]<<8) | buf[13]);
}