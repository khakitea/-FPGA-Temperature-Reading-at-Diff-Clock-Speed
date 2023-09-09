/* University of Washington
 * ECE/CSE 474,  [11/9/2022]
 *
 *   [Robyn Jung 1976925]
 *   [Margot Enright-Down 1776361]
 *      
 *   [Lab 4][Task 1]
 *   [Task 1 Inits]
 */

#include "PLL_Header.h"
#include "Lab4_Task1_Inits.h"
#include "task1_header.h"
#include "tm4c1294ncpdt.h"
#include <stdint.h>
#include <stdio.h>



int PLL_Init(enum frequency freq) {
    // Do NOT modify this function.
    MOSCCTL &= ~(0x4);                      // Power up MOSC
    MOSCCTL &= ~(0x8);                      // Enable MOSC
    while ((RIS & 0x100) == 0) {};          // Wait for MOSC to be ready
    RSCLKCFG |= (0x3 << 20);                // Select MOSC as system clock source
    RSCLKCFG |= (0x3 << 24);                // Select MOSC as PLL clock source

    PLLFREQ0 |= 0x60;                       // Set MINT field
    PLLFREQ1 |= 0x4;                        // Set N field

    MEMTIM0 &= ~((0xF << 22) | (0xF << 6));     // Reset FBCHT and EBCHT
    MEMTIM0 &= ~((0xF << 16) | (0xF << 0));     // Reset EWS and FWS
    MEMTIM0 &= ~((0x1 << 21) | (0x1 << 5));     // Reset FBCE and EBCE

    RSCLKCFG &= ~(0x1 << 28);                   // Temporarilly bypass PLL

    switch (freq) {
        case 120:
            MEMTIM0 |= (0x6 << 22) | (0x6 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x5 << 16) | (0x5 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x3;                        // Set PSYSDIV to use 120 MHZ clock
            RSCLKCFG &= ~0x3FC;                     // Update PSYSDIV field
            break;
        case 60:
            MEMTIM0 |= (0x3 << 22) | (0x3 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x2 << 16) | (0x2 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x7;                        // Set PSYSDIV to use 60 MHZ clock
            RSCLKCFG &= ~0x3F8;                     // Update PSYSDIV field
            break;
        case 12:
            MEMTIM0 |= (0x1 << 21) | (0x1 << 5);    // Set FBCE and EBCE
            RSCLKCFG |= 0x27;                       // Set PSYSDIV to use 12 MHZ clock
            RSCLKCFG &= ~0x3D8;                     // Update PSYSDIV field
            break;
        default:
            return -1;
    }

    RSCLKCFG |= (0x1 << 30);                // Enable new PLL settings
    PLLFREQ0 |= (0x1 << 23);                // Power up PLL
    while ((PLLSTAT & 0x1) == 0) {};        // Wait for PLL to lock and stabilize

    RSCLKCFG |= (0x1u << 31) | (0x1 << 28);  // Use PLL and update Memory Timing Register
    return 1;
}

void Switch_Init(void) {

  RCGCGPIO |= 0x100;            // Port J
  delay++; delay++;

  GPIODIR_J = 0x0;              // Set PJ0, 1 to inputs
  GPIODEN_J = 0x3;              // Set PJ0, 1 to digital port
  GPIOLOCK_J = 0x4C4F434B;      //unlock key
  GPIOCR_J = 0x3;               // Enable commit reg
  GPIOPUR_J = 0x3;              // Set pull up reg
  
  //for interrupts
  GPIOIS_J &= ~0x3;
  GPIOIBE_J &= ~0x3;
  GPIOIEV_J = ~0x3;
  GPIOICR_J |= 0x3;
  
  //enable portJ interrupts
  NVIC_EN1 |= 1<<19u;
    //PRI12 = 0x2000;
  PORTJ_IM |= 0x3;      //Enable SW1,2 interrupt mask
}

void ADCReadPot_Init(void) {
  // STEP 2: Initialize ADC0 SS3.
  // 2.1: Enable the ADC0 clock
  RCGCADC |= 0x01;                      // ADC Regi map p1073
  delay++; delay++; delay++;
  
  PLLFREQ0 |= 0x00800000;               // Power up the PLL (if not already)
  while (PLLSTAT != 0x1);               // Wait for the PLL to lock
  
  ADCCC_0 |= 0x1;                       // clock source defined by ALTCLKFG
  RCGCGPIO |= 0x10;                     // AIN0  PE3
  delay++; delay++; delay++;
  
  GPIOAFSEL_E |= ADC_INPUT_1;           // alt func to ADC input pins p770
  GPIODEN_E &= ~ADC_INPUT_1;            // clear GPIODEN bits for ADC input pins
  GPIOAMSEL_E |= ADC_INPUT_1;           // 

  ADCACTSS_0 &= ~ADC_INPUT_1;           // Disable sample sequencer 3
  ADCEMUX_0 |= 0x5000;                  // Timer is the trigger for SS3
  ADCSSMUX3_0 |= 0x0;
  ADCSSEMUX3_0 &= 0x0;                  // Select analog input channel for SS3
  ADCSSCTL3 |= 0x6;                     // Configure ADCSSCTL3 register
  ADCSSCTL3 |= 0xE;
  ADCIM_0 |= 0x8;                         // Set SS3 interrupt mask
      ADCSSTSH3 |= 0x4;

  NVIC_EN0 |= 1<<17u;                  // NVIC_EN0     vector #33 interr #17
  // Enable ADC0 SS3
  ADCACTSS_0 |= 0x8;
  ADCPSSI_0 |= 0x8;
}

void TimerADCTriger_Init(void) {
  // Initialize Timer0A to trigger ADC0 at 1 HZ.
  RCGCTIMER |= 0x1;                     // Enable Timer 0
  delay++;
  delay++;
  //Timer0 A
  GPTMCTL_0 |= 0x0;                     //Timer0A disable
  GPTMCFG_0 |= 0x0;                     //32-bit mode
  GPTMTAMR_0 = 0x2;                     //periodic timer mode
  //GPTMTAMR_0 &= 0xFFEF;               //setting to TACDIR to countdown
  GPTMTAILR_0 = 0xF42400;               //16,000,000 1Hz 62.5ns
  
  //Timer0A triggers ADC
  GPTMCTL_0 |= 0x20;
  GPTMADCEV |= 0x1;
  //Enable Timer
  GPTMCTL_0 |= 0x1;
}