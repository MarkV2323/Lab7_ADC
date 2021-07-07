/*	Author: Mark Vincent
 *  Partner(s) Name: NA
 *	Lab Section: A01
 *	Assignment: Lab #7  Exercise #1
 *	Youtube Link: 
 *  Exercise Description:
 *
 *  
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
enum States{start, init} state;

// Globals
unsigned int tmpA = 0x00;
unsigned int tmpB = 0x00;
unsigned int tmpD = 0x00;
unsigned short potent = 0x0000;

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
    DDRD = 0xFF; PORTD = 0x00; // PortD as output
    
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
