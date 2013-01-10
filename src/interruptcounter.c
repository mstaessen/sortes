#define __18F97J60
#define __SDCC__
#include <HardwareProfile.h>
#include <LCDBlocking.h>
#include <string.h>
#include <stdlib.h>

/*
 * __Intent__
 * Start two timers -- timer0 and timer1 -- at the same time. The clock speed of
 * timer0 is assumed to be 40MHz/4 (an instruction takes 4 up clock cycles). The 
 * clock speed of timer1 is known. According to the PIC documentation, the clock
 * speed of timer1 is equal to 32768Hz when using the built-in oscillator 
 * (T1CONbits.T1OSCEN = 1).
 * When timer1 triggers an overflow interrupt, read the number of ticks of 
 * timer0 and display this on the screen. From this value, one can calculate the 
 * clock speed of timer0.
 *
 * __Flaw__
 * It is impossible to start two timers at the same time since instructions take
 * up a certain time to be executed. As a result, timer1 will lag behind when it
 * is started after timer0.
 * 
 * __Solution__
 * Measure the time between two successive interrupts of timer1 (because it is 
 * the slowest of two). When the first interrupt occurs, immediately enable 
 * timer0. When the second interrupt occurs, imemdiately disable timer1 and 
 * print the time difference on the screen.
 * 
 */
    
unsigned long ticks = 0; 

void LCDDisplay(char *text, BYTE pos)
{
    BYTE length = strlen(text);
    BYTE available = 32 - pos;
    char *d = (char *)&LCDText[pos];
    const char *s = text;
    size_t n = (length < available) ? length : available;
    while (n-- > 0) *d++ = *s++;
    LCDUpdate();
}

void interruptServiceRoutine (void) __interrupt(1)
{
    // timer1 triggered an interrupt
    if (PIR1bits.TMR1IF) {
        // immediately enable or disable timer0 to start/stop incrementing said timer
        T0CONbits.TMR0ON ^= 1;
        LED0_IO ^= 1;
        
        // If timer0 gets disabled, we have a result and need to display it
        if (!T0CONbits.TMR0ON) {
            unsigned short remainder = *(unsigned short *)(&TMR0L);

            // Print the result
            char str[33];
            sprintf(str, "Elapsed ticks:  %lu + %hu", ticks, remainder);
            LCDDisplay(str, 0);
            
            // Reset timer0 and ticks for next measurement
            TMR0L = 0x0;
            ticks = 0;
            
            // Disable timer1
            //T1CONbits.TMR1ON = 0;
        }
        
        // Clear interrupt flag
        PIR1bits.TMR1IF = 0;
    }

    // timer0 triggered an overflow, increase the count
    if (INTCONbits.TMR0IF == 1) {
        ticks += 256;
        // Clear interrupt flag
        INTCONbits.TMR0IF = 0;
    }
}

void main(void)
{
    // 0   Global configuration
    // 0.1 Enable interrupts globally
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    
    LED0_TRIS = 0;
    LED0_IO = 0;
        
    // 1  Disable timer0 and timer1 for setup
    T0CONbits.TMR0ON = 0;
    T1CONbits.TMR1ON = 0;

    // 2   Set up timer0
    // 2.1 Clear the timer value
    TMR0H = 0x00000000;
    TMR0L = 0x00000000;
    // 2.2 Use 8-bit operation
    T0CONbits.T08BIT = 1;
    // 2.3 Use internal instruction cycle clock
    T0CONbits.T0CS = 0;
    // 2.4 Don't use the prescaler
    T0CONbits.PSA = 1;
    // 2.5 Enable interrupts
    INTCONbits.TMR0IE = 1;
    
    // 3   Set up timer1
    // 3.1 Use 16-bit read/write operation
    T1CONbits.RD16 = 1;
    // 3.2 Clear the timer value. One must first set the high byte, as the high 
    //     byte is stored in a temporary buffer and copied along when the low 
    //     byte is set.
    TMR1H = 0x00000000;
    TMR1L = 0x00000000;
    // 3.3 Don't use the prescaler
    T1CONbits.T1CKPS0 = 0;
    T1CONbits.T1CKPS1 = 0;
    // 3.4 Use the built-in oscillator which runs @ 32768Hz
    T1CONbits.T1OSCEN = 1;
    // 3.5 Don't sync clocks
    T1CONbits.T1SYNC = 1;
    // 3.6 Use the external clock source (= oscillator)
    T1CONbits.TMR1CS = 1;
    // 3.7 Enable interrupts
    PIE1bits.TMR1IE = 1;
    
    // 4   Configure the LCD display
    // 4.1 initialize the display
    LCDInit(); 
    // 4.2 Turn on LCD backlight
    LED3_TRIS = 0;
    LED3_IO = 1;
    
    // 5   Start timer1...
    T1CONbits.TMR1ON = 1;
 
    // ... and wait.
    while(1);
}
