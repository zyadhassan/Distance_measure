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
#include "../std_types.h"
#include "../common_macros.h"

#include "../MCAL/icu.h"
#include "ultrasonic.h"
#include "../MCAL/gpio.h"
#include "lcd.h"


uint16 g_TIMER_VALUE ;
uint32 volatile g_edges;


void Ultrasonic_init(void){
	Icu_ConfigType config = {F_CPU_8,RISING};
	Icu_init(&config);
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(ultrasonic_trig_port,ultrasonic_trig_pin,PIN_OUTPUT);
//	GPIO_setupPinDirection(ultrasonic_echo_port,ultrasonic_echo_pin,PIN_INPUT);


}
void Ultrasonic_Trigger(void){
	GPIO_writePin(ultrasonic_trig_port,ultrasonic_trig_pin,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ultrasonic_trig_port,ultrasonic_trig_pin,LOGIC_LOW);

}
uint16 Ultrasonic_readDistance(void){
	uint16 distance;
	Ultrasonic_Trigger();
	while(g_edges != 2);
	 distance= ((float)(g_TIMER_VALUE)/58.8);

	g_edges=0;
	 return distance;
}
void Ultrasonic_edgeProcessing(void){
	g_edges++;
	if(g_edges==1){
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(FALLING);
	}
	else if (g_edges==2){
		g_TIMER_VALUE=Icu_getInputCaptureValue();
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(RISING);


	}

}
