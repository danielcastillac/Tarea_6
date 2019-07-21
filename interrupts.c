/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
#include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

bool state = 0;
double count = 0;
/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* High-priority service */

void interrupt high_isr(void) {
    if (INTCONbits.INT0IF) {
        /* Zero-crossing input detection */
        LATBbits.LATB2 = 0; // Turn-off output
        T0CONbits.TMR0ON = 1; // Enable timer0

        INTCONbits.INT0IF = 0; // Restart INT0
    } else if (INTCONbits.TMR0IF) { // DEBO PONER TIMER EN 0
        /* TMR0 overflow to enable output */
        LATBbits.LATB2 = 1; // Turn-on output

        INTCONbits.TMR0IF = 0; // Restart TMR0 interrupt
    }
}

/* Low-priority interrupt routine */

void low_priority interrupt low_isr(void) {
    if (INTCON3bits.INT1IF) {
        /* Software polling for phase selection */
        count++;
        
        
        state = ~state;
        if(state) {
            
        }
        
        INTCON3bits.INT1IF = 0; // Restart INT1
    }
}

