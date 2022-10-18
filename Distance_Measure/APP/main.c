/*
 * main.c
 *
 *  Created on: Oct 18, 2022
 *      Author: User
 */

#include "../HAL/ultrasonic.h"
#include "../HAL/lcd.h"

#include <util/delay.h> /* For the delay functions */


int main(void){
	LCD_init();
	Ultrasonic_init();
	LCD_displayString("Distance =       cm");
	while(1){
		uint16 distance =Ultrasonic_readDistance();
		LCD_moveCursor(0,11);
		LCD_intgerToString(distance);
		if (distance <100)LCD_displayStringRowColumn(0,13," ");
		_delay_ms(100);
	}

}
