#ifndef __AHT20_H
#define __AHT20_H

#define AHT20_ADDR_WRITE 0x70
#define AHT20_ADDR_READ  0x71
extern uint8_t buf_dump[6];
typedef struct
{
    float temp;
    float hum;
}AHT20_DataDef;

uint8_t AHT20_Init(SoftIIC_HandleTypeDef *hi2c);
uint8_t AHT20_ReadData(SoftIIC_HandleTypeDef *hi2c, AHT20_DataDef *data);

#endif
