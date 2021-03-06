
# Lab 5: ARJANIT ISMAJLI

Link to your `Digital-electronics-2` GitHub repository:

   [https://github.com/Arjanit21/Digital-electronics-2/edit/main/Labs/05segment/05segment/Lab5.md](https://github.com/Arjanit21/Digital-electronics-2/edit/main/Labs/05segment/05segment/Lab5.md)


### 7-segment library

1. In your words, describe the difference between Common Cathode and Common Anode 7-segment display.
   * CC SSD
   * CA SSD
   * The difference between the two displays is the common cathode has all the cathodes of the 7-segments connected directly together and the common anode has all the anodes of the 7-segments connected together.

2. Code listing with syntax highlighting of two interrupt service routines (`TIMER0_OVF_vect`, `TIMER0_OVF_vect`) from counter application with at least two digits, ie. values from 00 to 59:

```c
static uint8_t pos = 0;
static uint8_t val0=0;
static uint8_t val1=0;
ISR(TIMER1_OVF_vect)
{
    //static uint8_t val0 = 0;  // This line will only run the first time
    // WRITE YOUR CODE HERE
   // static uint8_t val1=0;  
    val0++;
	
    if(val0 > 9){
		val0 = 0;
		val1++;
		if(val1>5){
			val1=0;
		}
	}
	SEG_update_shift_regs(val0, 0);
	
}
ISR(TIMER0_OVF_vect)
{
	
	pos++;
	if (pos>1){
		pos=0;
		SEG_update_shift_regs(val0,pos);
	}
	
	else {
		SEG_update_shift_regs(val1,pos);
	}
	

	// WRITE YOUR CODE HERE

}
```

```c
/**********************************************************************
 * Function: Timer/Counter0 overflow interrupt
 * Purpose:  Display tens and units of a counter at SSD.
 **********************************************************************/
ISR(TIMER0_OVF_vect)
{
    static uint8_t pos = 0;

    // WRITE YOUR CODE HERE

}
```

3. Flowchart figure for function `SEG_clk_2us()` which generates one clock period on `SEG_CLK` pin with a duration of 2&nbsp;us. The image can be drawn on a computer or by hand. Use clear descriptions of the individual steps of the algorithms.

   ![your figure]()![WhatsApp Image 2021-10-26 at 00 07 03](https://user-images.githubusercontent.com/91128841/138777751-2c02df84-8a80-4adb-8a66-9881f0853b42.jpeg)



### Kitchen alarm

Consider a kitchen alarm with a 7-segment display, one LED and three push buttons: start, +1 minute, -1 minute. Use the +1/-1 minute buttons to increment/decrement the timer value. After pressing the Start button, the countdown starts. The countdown value is shown on the display in the form of mm.ss (minutes.seconds). At the end of the countdown, the LED will start blinking.

1. Scheme of kitchen alarm; do not forget the supply voltage. The image can be drawn on a computer or by hand. Always name all components and their values.

   ![your figure]()![Lab5]![WhatsApp Image 2021-10-26 at 10 52 11](https://user-images.githubusercontent.com/91128841/138844973-a84db5de-6983-428a-b843-1e61c535ff3d.jpeg)


