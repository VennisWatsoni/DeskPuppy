#ifndef __OLED_H
#define __OLED_H


#define OLED_SCL_PIN GPIO_PIN_15
#define OLED_SCL_PORT GPIOA
#define OLED_SDA_PIN GPIO_PIN_3
#define OLED_SDA_PORT GPIOB
#define OLED_RES_PIN GPIO_PIN_4
#define OLED_RES_PORT GPIOB
#define OLED_DC_PIN GPIO_PIN_5
#define OLED_DC_PORT GPIOB

#define OLED_SCL_LOW() HAL_GPIO_WritePin(OLED_SCL_PORT,OLED_SCL_PIN,GPIO_PIN_RESET)
#define OLED_SCL_HIGH() HAL_GPIO_WritePin(OLED_SCL_PORT,OLED_SCL_PIN,GPIO_PIN_SET)
#define OLED_SDA_LOW() HAL_GPIO_WritePin(OLED_SDA_PORT,OLED_SDA_PIN,GPIO_PIN_RESET)
#define OLED_SDA_HIGH() HAL_GPIO_WritePin(OLED_SDA_PORT,OLED_SDA_PIN,GPIO_PIN_SET)
#define OLED_RES_LOW() HAL_GPIO_WritePin(OLED_RES_PORT,OLED_RES_PIN,GPIO_PIN_RESET)
#define OLED_RES_HIGH() HAL_GPIO_WritePin(OLED_RES_PORT,OLED_RES_PIN,GPIO_PIN_SET)
#define OLED_DC_LOW() HAL_GPIO_WritePin(OLED_DC_PORT,OLED_DC_PIN,GPIO_PIN_RESET)
#define OLED_DC_HIGH() HAL_GPIO_WritePin(OLED_DC_PORT,OLED_DC_PIN,GPIO_PIN_SET)

extern const uint8_t face_img[];
void OLED_Write_Byte(uint8_t dat);
void OLED_Write_Cmd(uint8_t cmd);
void OLED_Write_Data(uint8_t data);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_SetPos(uint8_t x,uint8_t y);
void OLED_ShowChar(uint8_t x,uint8_t y,char ch);
void OLED_ShowString(uint8_t x,uint8_t y,char *str);
void OLED_DrawFullImage(const uint8_t *img);
void OLED_ClearLine(uint8_t page);
void OLED_ClearShowString(uint8_t x,uint8_t y,char *str);


#endif
