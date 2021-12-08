/***********************************************************************

 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define MOTOR1   PB5    // AVR pin where motor is connected
#define MOTOR2   PB4    // AVR pin where motor is connected
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif
#define DELAY_1 1
#define DELAY_2 2
#define DELAY_15 1.5


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
    STATE_ACK
} state_t;

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Use Timer/Counter1 and send I2C (TWI) address every 33 ms.
 *           Send information about scanning process to UART.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Initialize I2C (TWI)
    twi_init();

    // Initialize UART to asynchronous, 8N1, 9600
    uart_init(UART_BAUD_SELECT(9600, F_CPU));

    // Configure 16-bit Timer/Counter1 to update FSM
    // Set prescaler to 262 ms and enable interrupt
    TIM1_overflow_262ms();
    TIM1_overflow_interrupt_enable();

    // Configure 16-bit Timer/Counter2 to update FSM
    // Set prescaler to 16 ms and enable interrupt for the servomotor
    TIM2_overflow_16ms();
    TIM2_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    
    // Put strings to ringbuffer for transmitting via UART
    uart_puts("\r\nScan I2C-bus for devices:\r\n");
    // Initialize UART to asynchronous, 8N1, 9600
    uart_init(UART_BAUD_SELECT(9600,F_CPU));
    
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
    // MOTOR at port B
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
 *           between 8 and 119.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    static state_t state = STATE_SEND;  // Current state of the FSM
    static uint8_t addr = 0x5c;            // I2C slave address
    uint8_t result = 1;                 // ACK result from the bus
    char uart_string[] = "0000"; // String for converting numbers by itoa()
    static uint8_t number_of_devices=0;
    uint8_t temp_int;
    uint8_t temp_frac;
    uint8_t hum_int;
    uint8_t hum_frac;
    char lcd_string[2] = "  ";     
    
    // Start ADC conversion
    ADCSRA |= (1<<ADSC);

    uart_puts("Reading \r\n");
    
    //Read temperature     
    result = twi_start((addr<<1) + TWI_WRITE);
    twi_write(0x02);
    result = twi_start((addr<<1) + TWI_READ);
    
    temp_int=twi_read_ack();
    temp_frac=twi_read_nack();
    twi_stop();
    lcd_init(LCD_DISP_ON);
    lcd_gotoxy(0,0);
    lcd_puts("Tem: ");
    itoa(temp_int,lcd_string,10); // temp integer part
    lcd_puts(lcd_string);
    lcd_puts(".");
    itoa(temp_frac,lcd_string,10); // temp fractional part
    lcd_puts(lcd_string);
    lcd_puts("C");
//----------------------------------------------
     //Read hum
     result = twi_start((addr<<1) + TWI_WRITE);
     twi_write(0x00);
     result = twi_start((addr<<1) + TWI_READ);

     hum_int=twi_read_ack();
     hum_frac=twi_read_nack();
     twi_stop();
     lcd_gotoxy(0,1);
     lcd_puts("Hum: ");
     itoa(hum_int,lcd_string,10); // hum integer part
     lcd_puts(lcd_string);
     lcd_puts(".");
     itoa(hum_frac,lcd_string,10); // hum fractional part
     lcd_puts(lcd_string);
     lcd_puts("%");
}
/**
ISR(TIMER2_OVF_vect){
        GPIO_toggle(&DDRB, MOTOR);
        _delay_ms(DELAY_15);
        GPIO_toggle(&DDRB, MOTOR);
        _delay_ms(DELAY_15);

}
*/

/**********************************************************************
 * Function: ADC complete interrupt
 * Purpose:  Display value on LCD and send it to UART.
 **********************************************************************/
ISR(ADC_vect)
{
    // WRITE YOUR CODE HERE
    uint16_t value = 0;
    char lcd_string[4] = "0000";
    value=ADC;
    
    //Put new value TO LCD
    itoa(value, lcd_string, 10);  // Convert decimal value to string
    lcd_gotoxy(12,0);
    lcd_puts(lcd_string);
    // send the same value to UART
     uart_puts(lcd_string);
     uart_puts(" ");
    
    if(value>=0 && value<=300)
    {
        GPIO_write_high(&PORTB, MOTOR1);   
        _delay_ms(1);
        GPIO_write_low(&PORTB, MOTOR1) ;
        _delay_ms(19);
    }    
     else if(value>300 && value <=600)
     {
        GPIO_write_high(&PORTB, MOTOR1);
        _delay_ms(1.5);
        GPIO_write_low(&PORTB, MOTOR1) ;
        _delay_ms(18.5);         
     }
     else
     {
        GPIO_write_high(&PORTB, MOTOR1);
        _delay_ms(2);
        GPIO_write_low(&PORTB, MOTOR1) ;
        _delay_ms(18);         
     }
     
     if(value>0 && value <=500)
     {
         GPIO_write_high(&PORTB, MOTOR2);
         _delay_ms(1.5);
         GPIO_write_low(&PORTB, MOTOR2) ;
         _delay_ms(18.5);
     }
     else
     {
         GPIO_write_high(&PORTB, MOTOR2);
         _delay_ms(2);
         GPIO_write_low(&PORTB, MOTOR2) ;
         _delay_ms(18);
     }
     
}   

