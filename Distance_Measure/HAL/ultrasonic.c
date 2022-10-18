 /******************************************************************************
 *
 * Module: UltraSonic
 *
 * File Name: ultrasonic.h
 *
 * Description: Source file for the  UltraSonic driver
 *
 * Author: Zyad Hassan
 *
 *******************************************************************************/


#include <util/delay.h> /* For the delay functions */

#include "../MCAL/icu.h"
#include "ultrasonic.h"
#include "../MCAL/gpio.h"


uint16 g_TIMER_VALUE = -1;
uint8 g_edges=0;

void Ultrasonic_init(void){
	GPIO_setupPinDirection(ultrasonic_trig_port,ultrasonic_trig_pin,PIN_OUTPUT);
	GPIO_setupPinDirection(ultrasonic_echo_port,ultrasonic_echo_pin,PIN_INPUT);
	Icu_ConfigType config = {F_CPU_8,RISING};
	Icu_init(&config);
	Icu_setCallBack(Ultrasonic_edgeProcessing);

}
void Ultrasonic_Trigger(void){
	GPIO_writePin(ultrasonic_trig_port,ultrasonic_trig_pin,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ultrasonic_trig_port,ultrasonic_trig_pin,LOGIC_LOW);

}
uint16 Ultrasonic_readDistance(void){
	Ultrasonic_Trigger();
	Icu_setEdgeDetectionType(RISING);
	while(g_TIMER_VALUE < 0);
	uint16 distance= (uint16)((uint64)17000 * ((double)g_TIMER_VALUE) * ((double)F_CPU/F_divide));
	 g_TIMER_VALUE = -1;
	 return distance;
}
void Ultrasonic_edgeProcessing(void){

	if(g_edges==0){
	Icu_clearTimerValue();
	Icu_setEdgeDetectionType(FALLING);
	g_edges++;
	}
	else if (g_edges==1){
		g_TIMER_VALUE=Icu_getInputCaptureValue();
		Icu_setEdgeDetectionType(RISING);
		g_edges=0;

	}

}
