/*
 * main.c
 *
 *  Created on: Oct 18, 2022
 *      Author: User
 */

#include "../HAL/ultrasonic.h"
#include "../HAL/lcd.h"
#include "avr/io.h" /* To use the IO Ports Registers */
#include <util/delay.h> /* For the delay functions */


int main(void){
	LCD_init();
	SREG |= (1<<7);

	Ultrasonic_init();
	LCD_displayString("Distance =");
	while(1){
		uint16 distance =Ultrasonic_readDistance();
		LCD_moveCursor(0,11);
		LCD_intgerToString(distance);
		LCD_displayString("cm");

	}

}
