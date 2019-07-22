/******************************************************************************/
/* Files to Include                                                           */
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

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void) {
    /* TODO Initialize User Ports/Peripherals/Project here */
    PORTB = 0; // Clean port B
    LATB = 0;
    /* Setup analog functionality and port direction */
    ADCON1 = 0x0F; // All digital ports
    /* Initialize peripherals */
    TRISBbits.RB0 = 1; // Zero-crossing input (INT0)
    TRISBbits.RB1 = 1; // Push-button input
    TRISBbits.RB2 = 0; // Opto-triac control pin
    LATBbits.LATB2 = 0; // Initialize in zero
    PORTBbits.RB0 = 0; // By default, RB0=0 in
    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */
    RCONbits.IPEN = 0; // Enable interrupt priorities
    /* Enable interrupts */
    INTCONbits.GIE = 1; // Global interrupt enable
    INTCONbits.PEIE = 1; // Enable peripheral interrupts
    INTCONbits.INT0IE = 1; // Enable INT0
    INTCONbits.INT0IF = 0; // Clear INT0 flag
    INTCON2bits.INTEDG0 = 0; // INT0 on falling edge
    //INTCON3bits.INT1IE = 1; // Enable INT1
    //INTCON3bits.INT1IF = 0; // Clear INT1 flag
    //INTCON2bits.INTEDG1 = 1; // INT1 on rising edge
    /* Timmer0 configuration */
    INTCONbits.TMR0IE = 1; // Enable timer0 interrupt
    INTCONbits.TMR0IF = 0; // Clear TMR0 interrupt flag
    INTCON2bits.TMR0IP = 1; // TMR0 interrupt High priority
    T0CONbits.T08BIT = 1; // 8bits
    T0CONbits.T0CS = 0; // Internal instruction cycle clock source
    T0CONbits.PSA = 0; // Prescaler is assigned.
    T0CONbits.T0PS = 0b101; // Prescaler value = 64
    T0CONbits.TMR0ON = 0; // Stops timer by default
    



}

