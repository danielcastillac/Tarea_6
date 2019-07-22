/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
#include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#define _XTAL_FREQ 8000000

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned int t_firing = 255; // Time to start output
unsigned int per = 255; // Half-wave period
unsigned int count_up = 0;
unsigned int count_t = 0;
bool inc_t;
bool dec_t;

unsigned int t_delay = 100; // time between counts

extern unsigned int precarga;

/******************************************************************************/
/* Main Program                                                               */

/*****************************************************************************/

void main(void) {
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */

    unsigned int count_press_delay = 15000; // After duration, start decreasing
    unsigned int max_count = 200; // Para que se incremente cada n períodos


    while (1) {
        /* Polling routine */
        __delay_us(t_delay); // Wait before next count

        if (PORTBbits.RB1) {
            count_up += 1;
        } else if (count_up != 0) {
            if (inc_t || dec_t) {
                inc_t = false;
                dec_t = false;
            } else if (count_up > count_press_delay) {
                dec_t = true;
            } else {
                inc_t = true;
            }
            count_up = 0;
        }
        if (inc_t) {
            // Increasing routine
            count_t += 1;

            if (count_t == max_count) {
                if (t_firing < per) {
                    t_firing += 1;
                } else {
                    inc_t = false;
                }
                count_t = 0;


            }
        } else if (dec_t) {
            // Decreasing routine
            count_t += 1;
            if (count_t == max_count) {
                if (t_firing > 0) {
                    t_firing -= 1;
                } else {
                    dec_t = false;
                }
                count_t = 0;
            }
        }
        precarga = per - t_firing; // Update precarga with newest delay
    }

}

