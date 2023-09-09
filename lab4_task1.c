/* University of Washington
 * ECE/CSE 474,  [11/3/2022]
 *
 *   [Robyn Jung 1976925]
 *   [Margot Enright-Down 1776361]
 *      
 *   [Lab 4][Task 1]
 *   
 */

#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"
#include "task1_header.h"
#include "Lab4_Task1_Inits.h"
#include <stdint.h>
#include <stdio.h>

uint32_t ADC_value;
enum frequency freq;
float temp_C, temp_F;
unsigned long touchVal_X;
unsigned long touchVal_Y;

int main(void) {
  
  freq = PRESET2;                       // Select system clock frequency preset
  PLL_Init(freq);                       // Set system clock frequency
  Switch_Init();                        // Initialize the 2 onboard switchs (GPIO)
  LCD_Init();
  Touch_Init();
  ADCReadPot_Init();                    // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init();                // Initialize Timer0A to trigger ADC0
//  buttonDisplay();
  // x, y, width, height, color(cyan 3)
  LCD_DrawFilledRect(64, 120, 64, 30, Color4[3]);
  LCD_DrawFilledRect(192, 120, 64, 30, Color4[3]);
  LCD_SetCursor(79, 130);
  LCD_Printf("120");
  LCD_SetCursor(207, 130);
  LCD_Printf("12");
  
  
  while(1) {
    
  //Task 1a
  //LCD_ColorFill(Color4[3]);
    
  temp_C = 147.5 - ((202.5 * ADC_value)/4096);
  temp_F = (temp_C * 1.8) + 32;

  LCD_Goto(0, 0);
  LCD_Printf("The current temperature is ");
  LCD_PrintFloat(temp_C);
  LCD_Printf(" C, ");
  LCD_PrintFloat(temp_F);
  LCD_Printf(" F.");
  
  LCD_Goto(0, 1);
  LCD_Printf("The current clock frequency is ");
  LCD_PrintInteger(freq);
  LCD_Printf(" MHz.");
  
    touchVal_Y = Touch_ReadY();
  touchVal_X = Touch_ReadX();
  
  // if touch is within Y range
  if ((touchVal_Y > 1060) && (touchVal_Y < 1170)) {
    // check the X range and set to corresponding frequency
    if ((touchVal_X > 1000) && (touchVal_X < 1500)) {
      freq = PRESET1;
    } else if ((touchVal_X > 1760) && (touchVal_X < 2000 )) {
      freq = PRESET3;
    } else {
      freq = freq;
    }
  } else {
    freq = freq;
  }

    // Check value on Terminal I/O
    printf("%lf | %lf\n", temp_C, temp_F);
//  printf("%d \t", touchVal_X);
//  printf("%d\n", touchVal_Y);
  }
  
  return 0;
}


void ADC0SS3_Handler(void) {
  ADC_FLAG = 0x8;                       // Clear ADC1 SS3 interrupt flag
  ADC_value = ADCSSFIFO3;
  //ADC_value &= 0xFFF;
}

 //SW1 pressed > high freq 120
 //SW2 pressed > low freq 12
void PortJ_Handler() {
  
  if ((GPIOMIS_J & SW1)) {
    GPIOICR_J |= SW1;                   //clear interrupt for SW1
    GPTMCTL_0 |= 0x1;                   //enable timer0A
    freq = PRESET1;
    PLL_Init(freq);

      printf("button 1 pressed");
  }
  if ((GPIOMIS_J & SW2)) {
    GPIOICR_J |= SW2;                   //clear interrupt for SW2
    GPTMCTL_0 |= 0x1;                   //enable timer0A
    freq = PRESET3;
    PLL_Init(freq);

     printf("button 2 pressed");
  }
  
  GPIOICR_J |= 0x3;
}
