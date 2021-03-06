# Lab 7: ARJANIT ISMAJLI

Link to this file in your GitHub repository:

[https://github.com/Arjanit21/Digital-electronics-2/edit/main/Labs/07uart/07uart/Lab7.md](https://github.com/Arjanit21/Digital-electronics-2/edit/main/Labs/07uart/07uart/Lab7.md)


### Analog-to-Digital Conversion

1. Complete table with voltage divider, calculated, and measured ADC values for all five push buttons.

   | **Push button** | **PC0[A0] voltage** | **ADC value (calculated)** | **ADC value (measured)** |
   | :-: | :-: | :-: | :-: |
   | Right  | 0&nbsp;V | 0   | 0023 |
   | Up     | 0.495&nbsp;V | 101 | 9903 |
   | Down   |   1.203V    |   246  |2563  |
   | Left   |   1.970V    |  403   | 4093 |
   | Select |    3.182V  |  651   |6393  |
   | none   |    5V   |   1023  | 1023 |

2. Code listing of ACD interrupt service routine for sending data to the LCD/UART and identification of the pressed button. Always use syntax highlighting and meaningful comments:

```c
/**********************************************************************
 * Function: ADC complete interrupt
 * Purpose:  Display value on LCD and send it to UART.
 **********************************************************************/
ISR(ADC_vect)
{
    uint16_t value = 0;
    char lcd_string[4] = "0000";

    value = ADC;                  // Copy ADC result to 16-bit variable
    itoa(value, lcd_string, 10);  // Convert decimal value to string

    // WRITE YOUR CODE HERE
  //Clear previous value
    lcd_gotoxy(8,0);
    lcd_puts("    ");
    //Put new value TO LCD
    itoa(value, lcd_string, 10);  // Convert decimal value to string
    lcd_gotoxy(8,0);
    lcd_puts(lcd_string);
    // send the same value to UART
     uart_puts(lcd_string);
     uart_puts(" ");
     
     
    //Clear previous value
    lcd_gotoxy(13,0);
    lcd_puts("    ");
    //Put new value to LCD
    
    //display value in hexa
    itoa(value, lcd_string, 16);  // Convert decimal value to string
    lcd_gotoxy(13,0);
    lcd_puts(lcd_string);
    
    //display what button was pressed
     lcd_gotoxy(8,1);
     lcd_puts("    ");
     lcd_gotoxy(12,1);
     lcd_puts("    ");
    
    
     lcd_gotoxy(8, 1);
     itoa(value, lcd_string, 10);
     if (value>1000) { lcd_puts("none");}
         if ((value>600)&&(value<1000)) { lcd_puts("select");}
              if ((value>350)&&(value<450)) { lcd_puts("left");}
                   if ((value>200)&&(value<270)) { lcd_puts("down");}
                        if ((value>5)&&(value<120)) { lcd_puts("up");}
                             if (value==0) { lcd_puts("right");}
             
     // lcd_puts(lcd_string);
;
}
```


### UART communication

1. (Hand-drawn) picture of UART signal when transmitting three character data `De2` in 4800 7O2 mode (7 data bits, odd parity, 2 stop bits, 4800&nbsp;Bd).

   ![your figure](![WhatsApp Image 2021-11-02 at 20 28 38](https://user-images.githubusercontent.com/91128841/139937469-67d17d6d-575e-479f-84db-3a0d4bbe9641.jpeg)
)

2. Flowchart figure for function `get_parity(uint8_t data, uint8_t type)` which calculates a parity bit of input 8-bit `data` according to parameter `type`. The image can be drawn on a computer or by hand. Use clear descriptions of the individual steps of the algorithms.

   ![your figure]()


### Temperature meter

Consider an application for temperature measurement and display. Use temperature sensor [TC1046](http://ww1.microchip.com/downloads/en/DeviceDoc/21496C.pdf), LCD, one LED and a push button. After pressing the button, the temperature is measured, its value is displayed on the LCD and data is sent to the UART. When the temperature is too high, the LED will start blinking.

1. Scheme of temperature meter. The image can be drawn on a computer or by hand. Always name all components and their values.

   ![your figure](![WhatsApp Image 2021-11-08 at 22 00 21 (1)](https://user-images.githubusercontent.com/91128841/140817511-d49b2d56-633d-49a0-a7e0-4ebd39573281.jpeg)
)
