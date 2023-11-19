/*
 * main.c
 *
 *  Created on: Aug 8, 2023
 *      Author: Amr-a
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "util/delay.h"
#include "MDIO_interface.h"
#include "HKeyPad_interface.h"
#include "HLCD_interface.h"
#include "HStpper_interface.h"

int main(void){

	//initializing ports
	Port_voidInit();

	HLCD_voidInit();
	HLCD_voidSendString("1:MCW,2:MCC,3:MS");
	HLCD_voidSetCursorPosition(2,1);
	HLCD_voidSendString("4:SCW,5:SCC,6:SS");


	while(1){
		u8 pressedKey = HKeyPad_u8GetKey();
		if (pressedKey=='1' || pressedKey=='2' || pressedKey=='3' || pressedKey=='4' || pressedKey=='5' || pressedKey=='6')
		{
			// DC motor CW
			if (pressedKey == '1'){
				MDIO_ErrorS_SetPinValue(DIO_PORTD,DIO_PIN3,DIO_HIGH);
				MDIO_ErrorS_SetPinValue(DIO_PORTD,DIO_PIN4,DIO_LOW);
			}
			// DC motor ACW
			else if (pressedKey == '2'){
				MDIO_ErrorS_SetPinValue(DIO_PORTD,DIO_PIN3,DIO_LOW);
				MDIO_ErrorS_SetPinValue(DIO_PORTD,DIO_PIN4,DIO_HIGH);
			}
			// DC motor stop
			else if (pressedKey == '3'){
				MDIO_ErrorS_SetPinValue(DIO_PORTD,DIO_PIN3,DIO_LOW);
				MDIO_ErrorS_SetPinValue(DIO_PORTD,DIO_PIN4,DIO_LOW);
			}

			// Stepper motor CW
			else if (pressedKey == '4'){
				Hstepper_rotate_CW(40);
				Hstepper_stop();

			}
			// Stepper motor ACW
			else if (pressedKey == '5'){
				Hstepper_rotate_ACW(40);
				Hstepper_stop();


			}
			// Stepper motor Stop
			else if (pressedKey == '6'){
				Hstepper_stop();

			}



		}

	}
}

