# Project Name：DeskPuppy
### function 1: pwm 
| PIN | DIRECTION | CHANNEL |LOCATION|
| ---- | ---- | ---- | --- |
| PA4 | + | 0 |Upper Left|
| PA5 | + | 1 |Bottom Left|
| PA6 | + | 2 |Upper Right|
| PA7 | + | 3 |Upper Right|

 PIN MODE :OUT_PP PULL DOWN HIGHTSPEED <br>
### function 2: 0.96 inch OLED
OLED_SCL    PA15<br>
OLED_SDA    PB3<br>
OLED_DC     PB5<br>
OLED_RES    PB4<br>
### function 3: aht20
si2c_aht20
### function 4: uart2 
Baud: 115200<br>
USART1 TX DMA1 CH4<br>
USART1 RX DMA1 CH5<br>
USART1 RX DMA1 CH6<br>
### function 5: ADC1 
LM358DR2G ADC1 INT0