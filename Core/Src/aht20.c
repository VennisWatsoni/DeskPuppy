#include "stm32f1xx_hal.h"
#include "i2c.h"
#include "aht20.h"

uint8_t AHT20_Init(SoftIIC_HandleTypeDef *hi2c)
{
    uint8_t ack;
    uint8_t buf[3];
    //AHT20 初始化命令
    SoftIIC_Start(hi2c);
    ack = SoftIIC_Write_Byte(hi2c, AHT20_ADDR_WRITE);
    if(ack != 0)
    {
        SoftIIC_Stop(hi2c);
        return 1;
    }
    SoftIIC_Write_Byte(hi2c,0xBE);
    SoftIIC_Write_Byte(hi2c,0x08);
    SoftIIC_Write_Byte(hi2c,0x00);
    SoftIIC_Stop(hi2c);
    HAL_Delay(20);

    //读取状态字，检查校准位bit3
    SoftIIC_Start(hi2c);
    SoftIIC_Write_Byte(hi2c,AHT20_ADDR_WRITE);
    SoftIIC_Stop(hi2c);
    SoftIIC_Start(hi2c);
    SoftIIC_Write_Byte(hi2c,AHT20_ADDR_READ);
    buf[0] = SoftIIC_Read_Byte(hi2c,1);
    SoftIIC_Stop(hi2c);

    if( (buf[0] & (1<<3)) == 0 )
    {
        return 2; //校准失败
    }
    return 0;
}

uint8_t AHT20_ReadData(SoftIIC_HandleTypeDef *hi2c, AHT20_DataDef *data)
{
    uint8_t ack,i;
    uint8_t buf[6];
    uint32_t raw_hum, raw_temp;

    //发送测量触发命令
    SoftIIC_Start(hi2c);
    ack = SoftIIC_Write_Byte(hi2c,AHT20_ADDR_WRITE);
    if(ack !=0)
    {
        SoftIIC_Stop(hi2c);
        return 1;
    }
    SoftIIC_Write_Byte(hi2c,0xAC);
    SoftIIC_Write_Byte(hi2c,0x33);
    SoftIIC_Write_Byte(hi2c,0x00);
    SoftIIC_Stop(hi2c);
    HAL_Delay(80); //等待转换

    //读取6字节数据
    SoftIIC_Start(hi2c);
    ack = SoftIIC_Write_Byte(hi2c,AHT20_ADDR_READ);
    if(ack !=0)
    {
        SoftIIC_Stop(hi2c);
        return 1;
    }
    for(i=0;i<6;i++)
    {
        if(i == 5) //最后一个字节 NACK
        {
            buf[i] = SoftIIC_Read_Byte(hi2c,1);
        }
        else
        {
            buf[i] = SoftIIC_Read_Byte(hi2c,0);
        }
    }
    SoftIIC_Stop(hi2c);

    if(buf[0] & 0x80)
    {
        return 2; //传感器忙
    }

    raw_hum  = ((uint32_t)buf[1] << 12) | ((uint32_t)buf[2] <<4)|(buf[3]>>4);
    raw_temp = ((uint32_t)(buf[3]&0x0F)<<16)| ((uint32_t)buf[4]<<8)|buf[5];

    data->hum  = raw_hum * 100.0f / (1UL << 20);
    data->temp = raw_temp * 200.0f/(1UL << 20) - 50.0f;
    for(int k=0;k<6;k++)
    {
        buf_dump[k] = buf[k];
    }
    return 0;
}

