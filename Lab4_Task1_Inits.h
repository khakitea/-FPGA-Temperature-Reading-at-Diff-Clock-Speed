/* University of Washington
 * ECE/CSE 474,  [11/3/2022]
 *
 *   [Robyn Jung 1976925]
 *   [Margot Enright-Down 1776361]
 *      
 *   [Lab 4][Task 1]
 *   Function Content
 */

#ifndef _LAB4_TASK1_INITS_H_
#define _LAB4_TASK1_INITS_H_

// Preset frequency for 120 MHZ, 60 MHZ, and 12 MHZ clock
// Pass in the preset to Timer1_Init and PLL_Init to configure
// the system clock to specified frequency
enum frequency {PRESET1 = 120, PRESET2 = 60, PRESET3 = 12};

// Initializes the PLL module and generates a system clock frequency
// that equal to the frequency preset.
// Returns 1 if configured successfully, -1 if you select a non-exist preset.
int PLL_Init(enum frequency freq);

// Initializes ADC Module 0 Sample Sequencer 3. The module is triggered by
// Timer module 0 subtimer A at 1 HZ. The interupt of ADC0 SS3 will be
// generated whenever the A/D conversion is done.
void ADCReadPot_Init(void);

// Initializes the 2 onboard switches.
void Switch_Init(void);

// Initializes Timer 0A to trigger ADC0 at 1 HZ.
void TimerADCTriger_Init(void);

#endif