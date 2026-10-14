#include "main.h"
#include "i2c.h"
void SoftIIC_Delay_us(uint32_t us)
{
	HAL_Delay(1);
   /* uint32_t ticks = us * (SystemCoreClock / 1000000U);
    uint32_t start = SysTick->VAL;
    while((start - SysTick->VAL) < ticks);*/
}
void SoftIIC_Init(SoftIIC_HandleTypeDef *hi2c)
{
    HAL_GPIO_WritePin(hi2c->sda_port, hi2c->sda_pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_SET);
}

void SoftIIC_Start(SoftIIC_HandleTypeDef *hi2c)
{
    HAL_GPIO_WritePin(hi2c->sda_port, hi2c->sda_pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_SET);
    SoftIIC_Delay_us(4);
    HAL_GPIO_WritePin(hi2c->sda_port, hi2c->sda_pin, GPIO_PIN_RESET);
    SoftIIC_Delay_us(4);
    HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_RESET);
}

void SoftIIC_Stop(SoftIIC_HandleTypeDef *hi2c)
{
    HAL_GPIO_WritePin(hi2c->sda_port, hi2c->sda_pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_SET);
    SoftIIC_Delay_us(4);
    HAL_GPIO_WritePin(hi2c->sda_port, hi2c->sda_pin, GPIO_PIN_SET);
    SoftIIC_Delay_us(4);
}

uint8_t SoftIIC_Write_Byte(SoftIIC_HandleTypeDef *hi2c, uint8_t dat)
{
    uint8_t i,ack;
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    for(i=0;i<8;i++)
    {
        HAL_GPIO_WritePin(hi2c->sda_port, hi2c->sda_pin, (dat&0x80)?GPIO_PIN_SET:GPIO_PIN_RESET);
        dat <<= 1;
        SoftIIC_Delay_us(4);
        HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_SET);
        SoftIIC_Delay_us(4);
        HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_RESET);
    }
    // ========= 读ACK：SDA切换浮空输入 =========
    GPIO_InitStruct.Pin = hi2c->sda_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(hi2c->sda_port, &GPIO_InitStruct);
    SoftIIC_Delay_us(4);
    HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_SET);
    SoftIIC_Delay_us(4);
    ack = HAL_GPIO_ReadPin(hi2c->sda_port, hi2c->sda_pin);
    HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_RESET);
    // ========= 读完ACK，切回开漏输出 =========
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(hi2c->sda_port, &GPIO_InitStruct);
    HAL_GPIO_WritePin(hi2c->sda_port, hi2c->sda_pin, GPIO_PIN_SET);
    return ack;
}

uint8_t SoftIIC_Read_Byte(SoftIIC_HandleTypeDef *hi2c, uint8_t ack)
{
    uint8_t i, dat = 0;
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    // SDA 设置为输入，无内部上拉，PCB带4.7K外部上拉
    GPIO_InitStruct.Pin = hi2c->sda_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(hi2c->sda_port, &GPIO_InitStruct);

    for(i = 0; i < 8; i++)
    {
        dat <<= 1;
        SoftIIC_Delay_us(4);
        HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_SET);
        SoftIIC_Delay_us(4);
        if(HAL_GPIO_ReadPin(hi2c->sda_port, hi2c->sda_pin))
        {
            dat |= 0x01;
        }
        HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_RESET);
    }
    // 发送ACK/NACK，切回开漏输出 OD
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
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
    SoftIIC_Delay_us(4);
    HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_SET);
    SoftIIC_Delay_us(4);
    HAL_GPIO_WritePin(hi2c->scl_port, hi2c->scl_pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(hi2c->sda_port, hi2c->sda_pin, GPIO_PIN_SET);
    return dat;
}