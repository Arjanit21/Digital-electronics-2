/***********************************************************************
WEATHER STATION SIMULATION
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define MOTOR1   PB5    // AVR pin where motor 1 is connected
#define MOTOR2   PB4    // AVR pin where motor 2 is connected
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "gpio.h"           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <stdlib.h>         // C library. Needed for conversion function
#include "uart.h"           // Peter Fleury's UART library
#include "twi.h"            // TWI library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library

/* Variables ---------------------------------------------------------*/
typedef enum {              // FSM declaration
    STATE_IDLE = 1,
    STATE_SEND,
    STATE_RECI
} state_t;

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Use Timer/Counter1 and send I2C (TWI) address every 262 ms.
 *           Send information about scanning process to UART.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Initialize I2C (TWI)
    twi_init();

    // Initialize UART to asynchronous, 8N1, 9600
    uart_init(UART_BAUD_SELECT(9600, F_CPU));
	uart_puts("\r\nScan I2C-bus for devices:\r\n");

    // Configure 16-bit Timer/Counter1 to update FSM
    // Set prescaler to 262 ms and enable interrupt
    TIM1_overflow_262ms();
    TIM1_overflow_interrupt_enable();
	
    lcd_init(LCD_DISP_ON);		    // LCD is ON (without cursor)
    lcd_gotoxy(0,0);
    lcd_puts("Hum:");
    lcd_gotoxy(0,1);
    lcd_puts("Tem:");

    // Enables interrupts by setting the global interrupt mask
    sei();

    
//-------------------------------------------
    // Configure ADC to convert PC0[A0] analog value
    // Set ADC reference to AVcc
    ADMUX |=(1<<REFS0);
    // Set input channel to ADC0
    ADMUX &= ~((1<MUX3) | (1<<MUX2)|| (1<<MUX1)| (1<<MUX0) );
    // Enable ADC module
    ADCSRA |= (1<<ADEN);
    // Enable conversion complete interrupt
    ADCSRA |= (1<<ADIE);    
    // Set clock prescaler to 128    
    ADCSRA |= (1<<ADPS2) | (1<<ADPS1) |(1<<ADPS0) ;
    
//----------------------------------------------------
    // Initialize and set to low motors at port B
    GPIO_config_output(&DDRB, MOTOR1);
    GPIO_write_low(&PORTB, MOTOR1);
    GPIO_config_output(&DDRB, MOTOR2);
    GPIO_write_low(&PORTB, MOTOR2);

    // Infinite loop
    while (1)
    {
		
    }
    // Will never reach this
    return 0;
}



/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Update Finite State Machine and test I2C slave addresses 
 *           to read sensors values.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    static state_t state = STATE_IDLE;     // Current state of the FSM
    static uint8_t addr = 0x5c;            // I2C slave address
    uint8_t result = 1;                    // ACK result from the bus
    char lcd_string[8] = "  ";     
	static uint8_t counter = 0x00;
    	
	switch(state){
		case(STATE_IDLE):
		state=STATE_SEND;
		break;
		
		case(STATE_SEND):
		uart_puts("STATE\n\n");
    
		//Read temperature and humidity     
		result = twi_start((addr<<1) + TWI_WRITE);				//CAMBIAR EL COUNTER !!!!!
		twi_write(counter);  
		counter= counter + (uint8_t)4;
		twi_stop(); 
		state=STATE_RECI;
		break;
		
		case(STATE_RECI):
		result = twi_start((addr<<1) + TWI_READ);
		
		result=twi_read_ack();
		itoa(result,lcd_string,10);   // temperature integer part
		lcd_gotoxy(6,0);
		lcd_puts(lcd_string);
		uart_puts(lcd_string);
		lcd_puts(".")	;
		uart_puts(".");	
		result=twi_read_ack();
		itoa(result,lcd_string,10);  // temperature fractional part
		lcd_puts(lcd_string);
		uart_puts(lcd_string);
		lcd_puts("%");
		uart_puts("%\n"),
		
		result=twi_read_ack();
		itoa(result,lcd_string,10);   // humidity integer part
		lcd_gotoxy(6,1);
		lcd_puts(lcd_string);
		uart_puts(lcd_string);
		lcd_puts(".");	
		uart_puts(".");	
		result=twi_read_nack();
		itoa(result,lcd_string,10);  // humidity fractional part
		lcd_puts(lcd_string);
		uart_puts(lcd_string);
		lcd_puts("C");
		uart_puts("C\n"),
		
		twi_stop();
		
		// Start ADC conversion
		ADCSRA |= (1<<ADSC);
		
		state = STATE_IDLE;
		break;
		
		default:
		state=STATE_IDLE;
		break;	
	}
	
}


/**********************************************************************
 * Function: ADC complete interrupt
 * Purpose:  Read voltage value (light intensity value) from the 
 * photoresistor and move servo motors according to this value.
 **********************************************************************/
ISR(ADC_vect)
{
    // WRITE YOUR CODE HERE
    uint16_t value = 0;
    char lcd_string[4] = "0000";
	
    value=ADC;
    
    //Put light intensity value TO LCD
    itoa(value, lcd_string, 10);  // Convert decimal value (light intensity) to string
    lcd_gotoxy(12,0);
    lcd_puts("    ");
	lcd_gotoxy(12,0);
    lcd_puts(lcd_string);	
	
    // send the same value to UART
	uart_puts(lcd_string);

	//If light intensity is below 300, horizontal motor moves to the left
    if(value>=0 && value<=300)
    {
        GPIO_write_high(&PORTB, MOTOR1);   
        _delay_ms(1);
        GPIO_write_low(&PORTB, MOTOR1) ;
        _delay_ms(19);
    }    
	//If light intensity is between 300 and 600, horizontal motor moves to the middle (front)
     else if(value>300 && value <=600)
     {
        GPIO_write_high(&PORTB, MOTOR1);
        _delay_ms(1.5);
        GPIO_write_low(&PORTB, MOTOR1) ;
        _delay_ms(18.5);         
     }
	 //If light intensity is over 600, horizontal motor moves to the right
     else
     {
        GPIO_write_high(&PORTB, MOTOR1);
        _delay_ms(2);
        GPIO_write_low(&PORTB, MOTOR1) ;
        _delay_ms(18);         
     }
     //If light intensity is below 500, vertical motor moves up
     if(value>0 && value <=500)
     {
         GPIO_write_high(&PORTB, MOTOR2);
         _delay_ms(1.5);
         GPIO_write_low(&PORTB, MOTOR2) ;
         _delay_ms(18.5);
     }
     //If light intensity is over 500, vertical motor moves down
     else
     {
         GPIO_write_high(&PORTB, MOTOR2);
         _delay_ms(2);
         GPIO_write_low(&PORTB, MOTOR2) ;
         _delay_ms(18);
     }
     
}   
