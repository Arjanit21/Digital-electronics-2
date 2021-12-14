# WEATHER STATION WITH 2-AXIS SOLAR TRACKING SYSTEM

### Team members

* Member 1: Arjanit Ismajli
* Member 2: Francisco Abelardo García Avilés
* Member 3: Gonzalo Docal Saiz
* Member 4: Mario Golbano Corzo

Link to this file in your GitHub repository:

https://github.com/Arjanit21/Digital-electronics-2/tree/main/Project/weatherStation...)

### Table of contents

* [Project objectives](#objectives)
* [Hardware description](#hardware)
* [Libraries description](#libs)
* [Video/Animation](#circ)
* [Flowchart](#flowchart)
* [Main application](#main)
* [Video](#video)
* [References](#references)

<a name="objectives"></a>

## Project objectives

Our project is weather station with 2-axis solar tracking system, we had to show the information about the temperature, humidity and light intensity in an LCD keypad shield.
To show the temperature, humidity, we used DHT12 humidity and temperature sensor to measure thos magnitudes, which we connected in the Arduino and we read the data directly in the LCD keypad shield.
To show the light intensity we used a photo resistor, connected it to the Arduino and read the data directly in the LCD keypad shield. The values ​​were from 0 to 1000, and by changing the values ​in the photoresistor, we let both motros move.
The motors were connected directly in Arduino and they were SG-90 micro servo. A servo motor can usually only turn 90° in either direction for a total of 180° movement  One made horizontal movement, and always moved when the values ​​between 0 to 300 or 300 to 600 or 600 to 1000 in three different directions.
The second motor moved vertically. When the light intensity was less than 500 it has moved down and when it was more than 500 the value of light intensity has moved up. By moving the motors, it was possible to move the panel and to orientate towards more light.

![WhatsApp Image 2021-12-08 at 15 50 50](https://user-images.githubusercontent.com/91128841/145907199-c83b277a-3898-4224-a4f9-dac4cf089ded.jpeg)


<a name="hardware"></a>

## Hardware description
We used the following components:
* [Arduino Uno + breadboard](#objectives)
* [LCD keypad shield](#objectives)
* [photoresistor](#objectives)
* [SG-90 micro servo](#objectives)
* [DHT12 humidity and temperature sensor](#objectives)
* [1kOhm resistor](#objectives)



<a name="libs"></a>
## Libraries description
These are the different libraries we used, all of them from the Course Labs:
* [weatherStation.cproj](https://github.com/Arjanit21/Digital-electronics-2/blob/main/Project/weatherStation/weatherStation/weatherStation/weatherStation.cproj)
*  [weatherStation.componentinfo.xml](https://github.com/Arjanit21/Digital-electronics-2/blob/main/Project/weatherStation/weatherStation/weatherStation/weatherStation.componentinfo.xml)
* [uart.h](https://github.com/Arjanit21/Digital-electronics-2/blob/main/Project/weatherStation/weatherStation/weatherStation/uart.h)
* [uart.c](https://github.com/Arjanit21/Digital-electronics-2/blob/main/Project/weatherStation/weatherStation/weatherStation/uart.c)
* [twi.h](https://github.com/Arjanit21/Digital-electronics-2/blob/main/Project/weatherStation/weatherStation/weatherStation/twi.h)
* [twi.c](https://github.com/Arjanit21/Digital-electronics-2/blob/main/Project/weatherStation/weatherStation/weatherStation/twi.c)
* [timer.h](https://github.com/Arjanit21/Digital-electronics-2/blob/main/Project/weatherStation/weatherStation/weatherStation/timer.h)
* [main.c](https://github.com/Arjanit21/Digital-electronics-2/blob/main/Project/weatherStation/weatherStation/weatherStation/main.c)
* [lcd_definitons.h](https://github.com/Arjanit21/Digital-electronics-2/blob/main/Project/weatherStation/weatherStation/weatherStation/lcd_definitions.h)
* [lcd.h](https://github.com/Arjanit21/Digital-electronics-2/blob/main/Project/weatherStation/weatherStation/weatherStation/lcd.h)
* [lcd.c](https://github.com/Arjanit21/Digital-electronics-2/blob/main/Project/weatherStation/weatherStation/weatherStation/lcd.c)
* [gpio.h](https://github.com/Arjanit21/Digital-electronics-2/blob/main/Project/weatherStation/weatherStation/weatherStation/gpio.h)
* [gpio.c](https://github.com/Arjanit21/Digital-electronics-2/blob/main/Project/weatherStation/weatherStation/weatherStation/gpio.c)

<a name="circ"></a>
 ## Video/Animation
Here we can see the animation of the project. It shows how the project should work, moving the axis motors accoirding to he light intensity, as we can see through the LCD. This LCD also shows the temperature and humidity.

![ezgif-6-83386f36faec](https://user-images.githubusercontent.com/91128841/146003177-af843eda-d794-4752-a4a5-aac580b80def.gif)

 
 
<a name="flowchart"></a>
 ## Flowchart
 Flowchart of main function:
 
 ![Flowchart Main + FMS](https://user-images.githubusercontent.com/91128841/145999916-b52b00a9-62be-406b-8112-80eaec97f4b3.jpeg)

Flowchart of ISR-Timer/Counter1

 ![ISR(TIMER1_OVF_vect)](https://user-images.githubusercontent.com/91128841/145999831-e19390e6-b583-47c8-913d-96369482885e.jpeg)
 
 Flowchart of ISR-ADconverter
 ![ISR (ADC_vect)](https://user-images.githubusercontent.com/91128841/145999863-2d8f4215-1411-48d1-a17e-2fc0a0b1bd03.jpeg)
 



<a name="main"></a>
## Main application
Here is the link to the main.c document we used fot the project.
[main.c](https://github.com/Arjanit21/Digital-electronics-2/blob/main/Project/weatherStation/weatherStation/weatherStation/main.c)

<a name="video"></a>

## Video
Here is a little video-explication of how the actual circuit worked in the Lab with our code.

https://www.youtube.com/watch?v=dNLS92pq2vg&ab_channel=arjanitismajli


<a name="references"></a>

## References
* [sg90_datasheet.pdf](http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf)
* [ATmega328P_Datasheet.pdf](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
* [LCD_KeyPad_Shield_For_Arduino](https://wiki.dfrobot.com/LCD_KeyPad_Shield_For_Arduino_SKU__DFR0009)
* [Libraries](https://github.com/tomas-fryza/Digital-electronics-2/tree/master/Labs)
* [Photoresistor](https://create.arduino.cc/projecthub/MisterBotBreak/how-to-use-a-photoresistor-46c5eb)
* [Variable Pulse width control servo position](https://www.jameco.com/Jameco/workshop/Howitworks/how-servo-motors-work.html)

