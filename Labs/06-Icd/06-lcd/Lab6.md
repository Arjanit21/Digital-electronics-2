# Lab 6: ARJANIT ISMAJLI

Link to your `Digital-electronics-2` GitHub repository:

[https://github.com/Arjanit21/Digital-electronics-2/edit/main/Labs/06-Icd/06-lcd/Lab6.md](https://github.com/...)


### LCD display module

1. In your words, describe what ASCII table is.
   * ASCII
   * The ASCII table contains letters, numbers, control characters, and other symbols. Each character is assigned a unique 7-bit code. ASCII is an acronym for American Standard Code for Information Interchange.

2. (Hand-drawn) picture of time signals between ATmega328P and LCD keypad shield (HD44780 driver) when transmitting three character data `De2`.

   ![your figure](![WhatsApp Image 2021-11-01 at 20 38 51](https://user-images.githubusercontent.com/91128841/139731151-98d6c332-2449-4335-b40d-0cb0cd88c186.jpeg)
)
)


### Stopwatch

1. Flowchart figure for `TIMER2_OVF_vect` interrupt service routine which overflows every 16&nbsp;ms but it updates the stopwatch LCD approximately every 100&nbsp;ms (6 x 16&nbsp;ms = 100&nbsp;ms). Display tenths of a second and seconds `00:seconds.tenths`. Let the stopwatch counts from `00:00.0` to `00:59.9` and then starts again. The image can be drawn on a computer or by hand. Use clear descriptions of the individual steps of the algorithms.

   ![your figure](![WhatsApp Image 2021-11-01 at 20 28 17](https://user-images.githubusercontent.com/91128841/139729839-7b0e2954-bba4-43f2-bf17-36ec9b4debf8.jpeg)
)


### Custom characters

1. Code listing with syntax highlighting of two custom character definition:

```c
/* Variables ---------------------------------------------------------*/
// Custom character definition
uint8_t customChar[16] = {
    // WRITE YOUR CODE HERE
    uint8_t customChar[16] = {
    0b01100,
    0b01110,
    0b01010,
    0b01010,
    0b01010,
    0b00110,
    0b10001,
    0b01110,
    0b01100,
    0b01110,
    0b01010,
    0b01010,
    0b01010,
    0b00110,
    0b10001,
    0b01110
};

};
```


### Kitchen alarm

Consider a kitchen alarm with an LCD, one LED and three push buttons: start, +1 minute, -1 minute. Use the +1/-1 minute buttons to increment/decrement the timer value. After pressing the Start button, the countdown starts. The countdown value is shown on the display in the form of mm.ss (minutes.seconds). At the end of the countdown, the LED will start blinking.

1. Scheme of kitchen alarm; do not forget the supply voltage. The image can be drawn on a computer or by hand. Always name all components and their values.

   ![your figure](![WhatsApp Image 2021-11-01 at 23 06 19](https://user-images.githubusercontent.com/91128841/139748359-29492c71-5950-474a-8e3f-3e4e8710a8bf.jpeg)
)
)
