#include "main.h"
#include "i2c.h"
static void SoftIIC_Delay_us(uint32_t t)
{
	uint32_t i;
	while(t--)
		for(i=0;i<72;i++);
}

void SoftIIC_Init(SoftIIC_HandleTypeDef *hi2c)
{
	// IIC总线上有4.7K上拉电阻，建议引脚设为推挽输出
	HAL_GPIO_WritePin(hi2c->sda_port, hi2c->sda_pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_SET);
}
void SoftIIC_Start(SoftIIC_HandleTypeDef *hi2c)
{
	HAL_GPIO_WritePin(hi2c->sda_port, hi2c->sda_pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_SET);
	SoftIIC_Delay_us(2);
	HAL_GPIO_WritePin(hi2c->sda_port, hi2c->sda_pin, GPIO_PIN_RESET);
	SoftIIC_Delay_us(2);
	HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_RESET);
}
void SoftIIC_Stop(SoftIIC_HandleTypeDef *hi2c)
{
	HAL_GPIO_WritePin(hi2c->sda_port, hi2c->sda_pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_RESET);
	SoftIIC_Delay_us(2);
	HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_SET);
	SoftIIC_Delay_us(2);
	HAL_GPIO_WritePin(hi2c->sda_port, hi2c->sda_pin, GPIO_PIN_SET);
}

uint8_t SoftIIC_Write_Byte(SoftIIC_HandleTypeDef *hi2c, uint8_t dat)
{
	uint8_t i,ack;
	for(i=0;i<8;i++)
	{
		HAL_GPIO_WritePin(hi2c->sda_port, hi2c->sda_pin, (dat&0x80)?GPIO_PIN_SET:GPIO_PIN_RESET);
		dat <<= 1;
		SoftIIC_Delay_us(2);
		HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_SET);
		SoftIIC_Delay_us(2);
		HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_RESET);
	}
	// 读取ACK
	HAL_GPIO_WritePin(hi2c->sda_port, hi2c->sda_pin, GPIO_PIN_SET);
	SoftIIC_Delay_us(2);
	HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_SET);
	SoftIIC_Delay_us(2);
	ack = HAL_GPIO_ReadPin(hi2c->sda_port, hi2c->sda_pin);
	HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_RESET);
	return ack;
}
uint8_t SoftIIC_Read_Byte(SoftIIC_HandleTypeDef *hi2c, uint8_t ack)
{
	uint8_t i, dat = 0;

	// SDA 设置为输入
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = hi2c->sda_pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(hi2c->sda_port, &GPIO_InitStruct);

	for(i = 0; i < 8; i++)
	{
		dat <<= 1;
		SoftIIC_Delay_us(2);
		HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_SET);
		SoftIIC_Delay_us(2);
		if(HAL_GPIO_ReadPin(hi2c->sda_port, hi2c->sda_pin))
		{
			dat |= 0x01;
		}
		HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_RESET);
	}

	// 发送ACK/NACK
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(hi2c->sda_port, &GPIO_InitStruct);

	if(ack)
	{
		HAL_GPIO_WritePin(hi2c->sda_port, hi2c->sda_pin, GPIO_PIN_SET); // NACK
	}
	else
	{
		HAL_GPIO_WritePin(hi2c->sda_port, hi2c->sda_pin, GPIO_PIN_RESET); // ACK
	}
	SoftIIC_Delay_us(2);
	HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_SET);
	SoftIIC_Delay_us(2);
	HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(hi2c->sda_port, hi2c->sda_pin, GPIO_PIN_SET);

	return dat;
}