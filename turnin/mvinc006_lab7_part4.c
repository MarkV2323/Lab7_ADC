/*	Author: Mark Vincent
 *  Partner(s) Name: NA
 *	Lab Section: A01
 *	Assignment: Lab #7  Exercise #4
 *	Youtube Link: https://youtu.be/TC8IC6EETxI 
 *  Exercise Description:
 *
 *  Our MAX is 0x78
 *  We need to showcase differnt light levels based on our MAX light level.
 *  If we divide 0x78 by 8 we get differences of 15 int (or FFFF, WOW!)
 *  So our eight light levels will be
 *  0x78 (120) => PORTB: 0xFF
 *  0x69 (105) => PORTB: 0x7F
 *  0x5A (90)  => PORTB: 0x3F
 *  0x4B (75)  => PORTB: 0x1F
 *  0x3C (60)  => PORTB: 0x0F
 *  0x2D (45)  => PORTB: 0x07
 *  0x1E (30)  => PORTB: 0x03
 *  0x0F (15)  => PORTB: 0x01
 *  NOTE: I had to do a bit of tweaking of the values on the lower end to
 *  properly display on the 8 LEDs.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

// States ie, {Start, Init, ... etc}
enum States{start, init, on} state;

// Globals
unsigned int tmpA = 0x00;
unsigned int tmpB = 0x00;
unsigned short photo = 0x0000;

// ADC init function
void ADC_init() {
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

// Tick Function
void tick() {
    
    // READ INPUT
    tmpA = PINA & 0xFF;

    // Transitions
    switch(state) {
        case start:
            state = init;
            break;
        case init:
            state = on;
            break;
        case on:
            state = on;
            break;
        default:
            state = start;
            break;
    }

    // Actions
    switch(state) {
        case start:
            break;
        case init:
            // init output from photo
            photo = ADC;
            // init output for PORTB and PORTD
            PORTB = 0x00;
            break;
        case on:
            // gathers output from potent
            photo = ADC;
            // finds light level
            if (photo >= 0x78) {
                tmpB = 0xFF;
            } else if (photo >= 0x69) {
                tmpB = 0x7F;
            } else if (photo >= 0x5A) {
                tmpB = 0x3F;
            } else if (photo >= 0x4B) {
                tmpB = 0x1F;
            } else if (photo >= 0x3C) {
                tmpB = 0x0F;
            } else if (photo >= 0x2F) {
                tmpB = 0x07;
            } else if (photo >= 0x29) {
                tmpB = 0x03;
            } else if (photo >= 0x0F) {
                tmpB = 0x01;
            } else {
                tmpB = 0x00;
            }
            // Writes output
            PORTB = tmpB;
            break;
        default:
            break;
    }

}

// Main Function using timer.h header
int main(void) {
    
    // PORTS
    DDRA = 0x00; PORTA = 0xFF; // PortA as input
    DDRB = 0xFF; PORTB = 0x00; // PortB as output
    //DDRD = 0xFF; PORTD = 0x00; // PortD as output
    
    // Init ADC
    ADC_init();

    // Sets timer to 50ms, and on
    TimerSet(50);
    TimerOn();
    
    // init state and output
    state = start;
    PORTB = 0x00;

    /* Insert your solution below */
    while (1) {
        
        // tick
        tick();

        // wait 1 sec
        while (!TimerFlag);

        TimerFlag = 0;
    }

    return 1;
}
