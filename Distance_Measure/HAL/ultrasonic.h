 /******************************************************************************
 *
 * Module: UltraSonic
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the  UltraSonic driver
 *
 * Author: Zyad Hassan
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "../std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ultrasonic_trig_port    PORTB_ID
#define ultrasonic_trig_pin     PIN5_ID

//#define ultrasonic_echo_port    PORTD_ID
//#define ultrasonic_echo_pin     PIN6_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 *
 • Description
➢ Initialize the ICU driver as required.
➢ Setup the ICU call back function.
➢ Setup the direction for the trigger pin as output pin through the GPIO driver.
• Inputs: None
• Return: None
 *
 *
 */

void Ultrasonic_init(void);

/*
• Description
➢ Send the Trigger pulse to the ultrasonic.
• Inputs: None
• Return: None
 *
 */

void Ultrasonic_Trigger(void);


/*
 * Description
➢ Send the trigger pulse by using Ultrasonic_Trigger function.
➢ Start the measurements by the ICU from this moment.
• Inputs: None
• Return: The measured distance in Centimeter.
 *
 *
 */
uint16 Ultrasonic_readDistance(void);


/*
 * Description
➢ This is the call back function called by the ICU driver.
➢ This is used to calculate the high time (pulse time) generated by the ultrasonic sensor.
• Inputs: None
• Return: None
 */
void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */
