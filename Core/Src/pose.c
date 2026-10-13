#include "pose.h"
void Puppy_Stand(void)
{
	Servo_SetAngle(SERVO_CH0, 90);
	Servo_SetAngle(SERVO_CH1, 90);
	Servo_SetAngle(SERVO_CH2, 90);
	Servo_SetAngle(SERVO_CH3, 90);
	HAL_Delay(800);
}
void Puppy_Sit(void)
{
	Servo_SetAngle(SERVO_CH0, 90);
	Servo_SetAngle(SERVO_CH1, 30);
	Servo_SetAngle(SERVO_CH2, 90);
	Servo_SetAngle(SERVO_CH3, 30);
	HAL_Delay(800);
}
void Puppy_ShakeAss(void)
{
	Servo_SetAngle(SERVO_CH0, 90);
	Servo_SetAngle(SERVO_CH2, 90);
    int i=3;
    do{
        Servo_SetAngle(SERVO_CH1, 80);
        Servo_SetAngle(SERVO_CH3, 80);
        HAL_Delay(200);
        Servo_SetAngle(SERVO_CH1, 90);
        Servo_SetAngle(SERVO_CH3, 90);
        HAL_Delay(200);
    }while(i-- > 0);
	HAL_Delay(800);
}
void Puppy_StepLeft(void)
{
	Servo_SetAngle(SERVO_CH0, 60);
	Servo_SetAngle(SERVO_CH1, 60);
	Servo_SetAngle(SERVO_CH2, 90);
	Servo_SetAngle(SERVO_CH3, 90);
	HAL_Delay(450);
}

void Puppy_StepRight(void)
{
	Servo_SetAngle(SERVO_CH0, 90);
	Servo_SetAngle(SERVO_CH1, 90);
	Servo_SetAngle(SERVO_CH2, 60);
	Servo_SetAngle(SERVO_CH3, 60);
	HAL_Delay(450);
}
void Puppy_StepFront(void)
{
    Servo_SetAngle(SERVO_CH0, 50);
    Servo_SetAngle(SERVO_CH1, 90);
    Servo_SetAngle(SERVO_CH2, 50);
    Servo_SetAngle(SERVO_CH3, 90);
    HAL_Delay(450);
}
void Puppy_StepBack(void)
{
    Servo_SetAngle(SERVO_CH0, 90);
    Servo_SetAngle(SERVO_CH1, 50);
    Servo_SetAngle(SERVO_CH2, 90);
    Servo_SetAngle(SERVO_CH3, 50);
    HAL_Delay(450);
}
void Puppy_WriggleOnce(void)
{
    Puppy_StepFront();
    Puppy_StepBack();
    Puppy_Stand();
}
void Puppy_WalkOnce(void)
{
	Puppy_StepLeft();
	Puppy_Stand();
	Puppy_StepRight();
	Puppy_Stand();
}
void walk3sitdown(void)
{
    Puppy_WalkOnce();
    Puppy_WalkOnce();
    Puppy_WalkOnce();
    Puppy_Sit();
}
void Puppy_Wriggle3sitdown(void)
{
    Puppy_WriggleOnce();
    Puppy_WriggleOnce();
    Puppy_WriggleOnce();
    Puppy_Sit();
}