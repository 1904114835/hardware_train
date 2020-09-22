/*                      单片机温度控制装置                            */
#include<stm32f10x.h>
#include<string.h>
#include "main.h"
#include<stdio.h>
#include <stdarg.h>



void delay_ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  
      while(i--) ;    
   }
}


void yq(int direc)
{
	if(direc >0){
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
	}
	else{
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	}
}
void yh(int direc)
{
	if(direc >0){
		GPIO_SetBits(GPIOA,GPIO_Pin_6);
	}
	else{
		GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	}
}
void zq(int direc)
{
	if(direc >0){
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	}
	else{
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
	}
}
void zh(int direc)
{
	if(direc >0){
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
	}
	else{
		GPIO_SetBits(GPIOA,GPIO_Pin_7);
	}
}
void forward(int time_run)
{
	zq(1);
	zh(1);
	yq(1);
	yh(1);
	delay_ms(time_run);
}
void backward(int time_run)
{
	zq(0);
	zh(0);
	yq(0);
	yh(0);
	delay_ms(time_run);
}
void turnLeft(int time_run)
{
	zq(1);
	zh(1);
	yq(0);
	yh(0);
	delay_ms(time_run);
}
void turnRight(int time_run)
{
	zq(0);
	zh(0);
	yq(1);
	yh(1);
	delay_ms(time_run);
}
int main()
{
	//stm32 pa0-3 is pwm in,which connect to car's VaVbVcVd,
	//stm32 pa4-7 is dereciton control, which connect to car's DaDbDcDd
	//PA IS ST , TO ST.
	GPIO_int_init();
	TIM_int_init();
	uart1_init(9600);
	while(1){}
	
	/*
	*/

}
