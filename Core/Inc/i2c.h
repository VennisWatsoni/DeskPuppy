#ifndef _I2C_H_
#define _I2C_H_
typedef struct
{
	GPIO_TypeDef *sda_port;
	uint16_t      sda_pin;
	GPIO_TypeDef *scl_port;
	uint16_t      scl_pin;
} SoftIIC_HandleTypeDef;
extern SoftIIC_HandleTypeDef si2c_OLED;
extern SoftIIC_HandleTypeDef hi2c_sw2;
extern SoftIIC_HandleTypeDef hi2c_sw3;
void SoftIIC_Init(SoftIIC_HandleTypeDef *hi2c);
void SoftIIC_Start(SoftIIC_HandleTypeDef *hi2c);
void SoftIIC_Stop(SoftIIC_HandleTypeDef *hi2c);
uint8_t SoftIIC_Write_Byte(SoftIIC_HandleTypeDef *hi2c, uint8_t dat);
uint8_t SoftIIC_Read_Byte(SoftIIC_HandleTypeDef *hi2c, uint8_t ack);
#endif