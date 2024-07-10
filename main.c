/*
 * main.c
 *
 *  Created on: Oct 14, 2022
 *      Author: DELL
 */


#include "MCAL/Dio/Dio.h"
#include "HAL/LCD/lcd.h"
#include "HAL/Seven_Segment/SevSegment.h"
#include "HAL/KEYPAD/KeyPad.h"
#include "MCAL/EXIT_interrupts/EXIT_interrupts.h"
#include "MCAL/ADC/adc.h"
#include "MCAL/Timer0/timer0.h"
#include "MCAL/Timer1/Timer1.h"
#include "MCAL/USART/USART.h"
#include "MCAL/SPI/spi.h"
#include <util/delay.h>
void do_operation (void);

char pressed_button ='\0';                       //stores the button pressed by the lcd if it a char
int pressed_button_num;                           //stores the button pressed by the lcd if it a num
unsigned char password [16] = {'?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?'};   //stores the real password
unsigned char  check_password_num [16];             //stores the password you write
int size_password = 0;
int size_password_check = 0;
char operation;
int first_num [16];
int second_num [16];
int size_firstnum_operation = 0;
int size_secondnum_operation = 0;
int result = 0 ;

void set_password (void){

/*
	if ((password[0]!='?') && (password [1]!='?') && (password[2]!='?') && (password[3]!='?')){
		return 1 ;
	}
*/

	LCD_Send_String_Pos ("set  password", 1, 1);

	int x = 1;      // to make a space when writing on lcd.
    while (1){
    	pressed_button = '\0';

    	do{
            pressed_button = KP_GetPressed();

    	}while (pressed_button == '\0');


    	if (pressed_button == 'A'){
    		_delay_ms (1000);
    			break;
    	}
    	password[size_password] = pressed_button;

    	//password[size_password] = pressed_button;
    	LCD_Send_Number_Pos (pressed_button , 2 , x);
    	_delay_ms (1000);
    	LCD_Send_Char_Pos('*',2,x);
    	size_password  += 1 ;
    	x += 1  ;
    }

}

//function to check if password is correct
void check_password (void){
	// preparing for checking the password
	for (int x = 0 ; x < size_password_check ; x++){
		check_password_num[x]='\0';
	}
	size_password_check = 0;
	LCD_Send_Command (_LCD_CLEAR);
	pressed_button ='\0';

	LCD_Send_String_Pos ("check passowrd", 1 , 1);

    int x_pos = 1;     // to make a space when writing on lcd.

    while (1){
    	pressed_button = '\0';
    	do{
           pressed_button = KP_GetPressed();
    	}while (pressed_button == '\0');

    	if (pressed_button == 'A'){
    			break;
    	};

        //storing the checked password in a variable
    	check_password_num[size_password_check ] = pressed_button;
    	LCD_Send_Number_Pos ( pressed_button , 2 , x_pos);
    	_delay_ms (500);
    	LCD_Send_Char_Pos('*',2,x_pos);
    	size_password_check  += 1 ;
    	x_pos +=1;
    }

    //checking equality

    int pass;     // increments index value and makes check the equality
    int equal_nums = 0;   // stores the number of equal numbers in the real password and the one you write
    if (size_password_check == size_password){
		for (pass = 0 ; pass <= size_password_check ; pass++){

				if (password [pass] == check_password_num [pass]){
					equal_nums += 1;
				}
		}
		if (equal_nums == size_password_check ){
			    // means all elements in password are equivalent to the elements in check password
			LCD_Send_Command (_LCD_CLEAR);
			LCD_Send_String_Pos ("welcome to calc", 1 , 1);
            _delay_ms (1000);
		}
		else{
			check_password();
		}
    }
    else{
    	check_password();
    }

}


void firstnum_operation (void){
	LCD_Send_Command (_LCD_CLEAR);
	//LCD_Send_String_Pos ("hello world", 1 , 1);
    operation = '\0';
	int x = 0 ;
	LCD_Send_Command (_LCD_CLEAR);
    while (1){
	do{
	         pressed_button = KP_GetPressed();
	  }while (pressed_button =='\0');

	if (pressed_button == 'A'){
	    			break;
	}

	if (pressed_button == '-' || pressed_button == '+' ||  pressed_button == '/' ||  pressed_button == '*' ){
		 operation = pressed_button ;
		 LCD_Send_Char_Pos (operation , 1 , size_firstnum_operation );
		 size_firstnum_operation ++;

	}
	else if (pressed_button == 0 || pressed_button == 1 || pressed_button == 2 || pressed_button == 3 || pressed_button == 4 || pressed_button == 5 || pressed_button == 6 || pressed_button == 7 || pressed_button == 8 ||pressed_button == 9){
		first_num [x] = pressed_button;
		LCD_Send_Number_Pos (pressed_button , 1,size_firstnum_operation );
		size_firstnum_operation ++ ;
        x++;
	}
}
}

void secondnum (void){

	while (1){
		do{
			pressed_button = KP_GetPressed();
		}while (pressed_button =='\0');

			if (pressed_button == 'A'){
							break;
			}
            if (pressed_button == '='){
            	LCD_Send_Char_Pos ('=' , 1 , size_secondnum_operation + size_firstnum_operation);
            	do_operation ();
            	break ;
            }
			if (pressed_button == 0 || pressed_button == 1 || pressed_button == 2 || pressed_button == 3 || pressed_button == 4 || pressed_button == 5 || pressed_button == 6 || pressed_button == 7 || pressed_button == 8 ||pressed_button == 9){
				second_num [size_secondnum_operation] = pressed_button;

				LCD_Send_Number_Pos (pressed_button , 1,size_firstnum_operation + size_secondnum_operation);
				size_secondnum_operation ++;

			}
	}
}



void do_operation (void){
	int multiplier = 1 ;
	int m;
	int first_num_real = 0;
	int second_num_real = 0;

	for (m = size_firstnum_operation - 2 ; m > 0 ; m--){
		first_num_real = first_num_real + first_num [m] * multiplier ;
		multiplier = multiplier * 10 ;
	}
	multiplier = 1 ;
	for (m = size_secondnum_operation-1 ; m > 0 ; m--){
		second_num_real = second_num_real + second_num [m] * multiplier ;
		multiplier = multiplier * 10 ;
	}
	if (operation == '+'){
		result = first_num_real + second_num_real ;
		LCD_Send_Number_Pos (result , 1, size_firstnum_operation + size_secondnum_operation);
	}
	if (operation == '-'){
			result = first_num_real - second_num_real ;
			LCD_Send_Number_Pos (result , 1, size_firstnum_operation + size_secondnum_operation);
		}
	if (operation == '*'){
			result = first_num_real *  second_num_real ;
			LCD_Send_Number_Pos (result , 1, size_firstnum_operation + size_secondnum_operation);
		}
	if (operation == '/'){
			result = first_num_real / second_num_real ;
			LCD_Send_Number_Pos (result , 1, size_firstnum_operation + size_secondnum_operation);
		}



}

void calculator (void){
	set_password () ;
	check_password ();

	 firstnum_operation();
	 secondnum ();
	 // do_operation ();


}


int main(){


	Dio_init();
	LCD_Init();
	//calculator ();
	set_password();
	check_password();
	firstnum_operation();
	secondnum ();

}

