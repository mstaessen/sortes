#define __18CXX
#define __SDCC__
#include "Include/HardwareProfile.h"
#include "Include/LCDBlocking.h"

void offsetTMR1(void) 
{
    TMR1H = 0x10000000;
    TMR1L = 0x00000000;
}

void high_isr(void) __interrupt (1) 
{
    if (PIR1bits.TMR1IF) {
        LED0_IO ^= 1; 
        LED1_IO ^= 1; 
        
        offsetTMR1();
        
        // Clear interrupt flag
        PIR1bits.TMR1IF = 0;
    }
}

// initialize board
void configure(void)
{
    // Configure LED0 for output
	LED0_TRIS = 0;
    // Configure LED1 for output
	LED1_TRIS = 0;
    
    // enable interrupts globally
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    
    // enable timer1
	T1CONbits.TMR1ON = 1; 
    // use timer1 as a 16-bit counter
	T1CONbits.RD16 = 1; 
    // use timer1 external clock
	T1CONbits.TMR1CS = 1;
    // use timer1 oscillator @ 32768Hz
    T1CONbits.T1OSCEN = 1;
    // disable timer1 prescaler
	T1CONbits.T1CKPS0 = 0;
    T1CONbits.T1CKPS1 = 0;
    // clear timer1 overflow bit
	PIR1bits.TMR1IF = 0;
    // enable timer1 interrupts
    PIE1bits.TMR1IE = 1;
}

void main()
{
	configure();
    offsetTMR1();
    
    // Turn on LED0
	LED0_IO = 1;
    // Turn off LED1
	LED1_IO = 0;
	
    while (1);
}
