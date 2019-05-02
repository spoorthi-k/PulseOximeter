#include <msp430.h> 
#include <stdbool.h>

// checks that the device is correctly oriented on the person's finger and engaged
bool potentiometer_engaged() {
	int potentiometer_input = P6IN & BIT1; // get potentiometer input
	// conversion to resistance - need to calibrate this using the device, so we don't have a conversion factor at the moment
	if (/*resistance is greater than some specified amount*/) {
		return true;
	}
	return false;
}

// computes the blood oxygen saturation quantity based on the comparative IR and Red light absorbance levels
int calculate_SpO2(IR, Red) {
	// need to figure out exact conversion factors below
	int IR_absorbance = ln(IR)*0.00000094; // convert IR_absorbance from voltage to absorption value
	int Red_absorbance = ln(Red)*0.00000066; // convert Red_absorbance from voltage to absorption value
	return (Red_absorbance/IR_absorbance);
}

// displays measured blood oxygen saturation value onto the screen
void display_to_screen(int) {
	P2OUT |= BIT2;
	P1OUT = int
	// 7-segment display output
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    // INITIALIZE PINS
    /* Pin use:
     * P4.0 - IR LED output
     * P4.3 - Red LED output
     * P2.(2-4) - 3-digit selector for SpO2
     * P1.(2-5) - 4 bit output for display
     * P6.0 - photodiode input
     * P6.1 - potentiometer input
     * */
	P1DIR |= (BIT2 + BIT3 + BIT4 + BIT5); // Declare Pins 2-5 of Port 1 as output
	P2DIR |= (BIT2 + BIT3); // Declare Pins 2-3 of Port 2 as output
	P6DIR &= ~(BIT0 + BIT1); // Declare Pins 0-1 of Port 6 as input

	while (1) {
		if (potentiometer_engaged()) {
			P4OUT |= BIT0; // IR LED on
			int IR_absorbance = P6IN & BIT0; // Collects IR absorbance value
			P4OUT &= ~BIT0; // IR LED off
			P4OUT |= BIT3; // Red LED on
			int Red_absorbance = P6IN & BIT0; // Collects Red light absorbance value
			P4OUT &= ~BIT3; // Red LED off
			int saturation = calculate_SpO2(IR_absorbance, Red_absorbance);
			display_to_screen(saturation);
			__delay_cycles(100000); // need to test clock speed for exact delay, currently an arbitrary number
		}
		else {
			__delay_cycles(100000); // need to test clock speed for exact delay, currently an arbitrary number
		}
	}
}
