/* University of Washington
 * ECE/CSE 474,  [11/9/2022]
 *
 *   [Robyn Jung 1976925]
 *   [Margot Enright-Down 1776361]
 *      
 *   [Lab 4][Task 1]
 *   [Header File]
 */

#ifndef _TASK1_HEADER_H_
#define _TASK1_HEADER_H_


/**************************************************************
 *                  REGISTER DEFINITIONS
 **************************************************************/
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))
#define RCGCADC (*((volatile uint32_t *)0x400FE638))
   
 // LCD
#define GPIODIR_D (*((volatile uint32_t *)0x4005B400))
#define GPIODEN_D (*((volatile uint32_t *)0x4005B51C))
#define GPIOAFSEL_D (*((volatile uint32_t *)0x4005B420))
#define GPIODIR_K (*((volatile uint32_t *)0x40061400))
#define GPIOAFSEL_K (*((volatile uint32_t *)0x40061420))
#define GPIODEN_K (*((volatile uint32_t *)0x4006151C))
#define GPIODIR_M (*((volatile uint32_t *)0x40063400))
#define GPIOAFSEL_M (*((volatile uint32_t *)0x40063420))
#define GPIODEN_M (*((volatile uint32_t *)0x4006351C))
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))
#define GPIOAFSEL_N (*((volatile uint32_t *)0x40064420))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODIR_P (*((volatile uint32_t *)0x40065400))
#define GPIOAFSEL_P (*((volatile uint32_t *)0x40065420))
#define GPIODEN_P (*((volatile uint32_t *)0x4006551C))
#define GPIODIR_Q (*((volatile uint32_t *)0x40066400))
#define GPIOAFSEL_Q (*((volatile uint32_t *)0x40066420))
#define GPIODEN_Q (*((volatile uint32_t *)0x4006651C))

 // Onboard Switches
   //Port J for SW 1 and 2
#define GPIODIR_J (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC)) 
#define GPIOLOCK_J (*((volatile uint32_t *)0x40060520))         //enables editing GPIOCR
#define GPIOCR_J (*((volatile uint32_t *)0x40060524))           //determines the bits to CR
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))          //enables pull-up resister
#define GPIOIS_J (*((volatile uint32_t *)0x40060404))           //edge sensitive on
#define GPIOIBE_J (*((volatile uint32_t *)0x40060408))          //trigger is controlled by IEV
#define GPIOIEV_J (*((volatile uint32_t *)0x4006040C))          //falling edge trigger
#define GPIOICR_J (*((volatile uint32_t *) 0x4006041C))         //Clear interrupt
#define GPIOMIS_J (*((volatile uint32_t *) 0x40060418)) //Masked Interrupt Status (checks if the interrupt has triggered)
   
 // Interrupt
#define NVIC_EN1 (*((volatile uint32_t *)0xE000E104))   //                      Port J(51)
#define PORTJ_IM (*((volatile uint32_t *)0x40060410))   //Port Interrupt Mask (triggered interrupt can be sent to interrupt controller)
#define PRI12 (*((volatile uint32_t *)0xE000E430))      //for interrupt 51 priority
   
 // ADC
#define ADCCC_0 (*((volatile uint32_t *)0x40038FC8))            //1160 Controls the clock source for ADC modules
#define GPIODEN_E (*((volatile uint32_t *)0x4005C51C))          //value 0 for digital function disable
#define GPIOAMSEL_E (*((volatile uint32_t *)0x4005C528))        //value 1 for analog function enable
#define GPIOAFSEL_E (*((volatile uint32_t *)0x4005C420))        //value 1 for signal controlled by alternate hardware func
#define ADCACTSS_0 (*((volatile uint32_t *)0x40038000))         //SS ASEN3 disable
#define ADCEMUX_0 (*((volatile uint32_t *)0x40038014))          //Event Mux selector    Timer trigger must be enabled with TnOTE bit in GPTMCTL
#define ADCSSEMUX3_0 (*((volatile uint32_t *)0x400380B8))       //Select AIN0
#define ADCSSCTL3 (*((volatile uint32_t *)0x400380A4))           //Config info for sample 
#define ADCIM_0 (*((volatile uint32_t *)0x40038008))              //ADC Interrupt mask
#define NVIC_EN0 (*((volatile uint32_t *)0xE000E100)) 
#define GPTMADCEV (*((volatile uint32_t *)0x40030070))
#define ADCRIS (*((volatile uint32_t *)0x40038004)) 
#define ADC_FLAG (*((volatile uint32_t *)0x4003800C))           //p1058 ADCISC bit3 interr status clear
#define ADCSSFIFO3 (*((volatile uint32_t *)0x400380A8)) 
#define ADCPSSI_0 (*((volatile uint32_t *)0x40038028))
#define ADCSSMUX3_0 (*((volatile uint32_t *)0x400380A0))
#define ADCSSTSH3 (*((volatile uint32_t *)0x400380BC))
   
 // Timer 0A
#define GPTMCTL_0 (*((volatile uint32_t *)0x4003000C)) //p986 0 is disable for timer0 A
#define GPTMCFG_0 (*((volatile uint32_t *)0x40030000)) //p976
#define GPTMTAMR_0 (*((volatile uint32_t *)0x40030004)) //p977
#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028)) //1004
#define GPTMRIS_0 (*((volatile uint32_t *)0x4003001C)) //p996 TATORIS bit is the last bit
#define GPTMICR_0 (*((volatile uint32_t *)0x40030024)) //p1002 TATOCINT is the last bit
   

#define HARDFAULT (*((volatile uint32_t *) 0xE000ED2C))

/**************************************************************
 *                    GLOBAL VARIABLES
 *************************************************************/
static volatile unsigned short delay = 0;

/**************************************************************
 *                     ADDITIONAL MACROS
 **************************************************************/
#define ADC_INPUT_1 0x8         //PE3
#define SW1  0x1                //PJ0
#define SW2  0x2                //PJ1

#endif