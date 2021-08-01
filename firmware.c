/*
 * File:   staircase_shift_lights firmware.c
 * Author: Liyanage Kalana Perera
 *
 * Created on August 1, 2021, 8:05 AM
 */
// 'C' source line config statements

// CONFIG
//#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High speed crystal/resonator on GP4/OSC2/CLKOUT and GP5/OSC1/CLKIN)
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = ON          // Code Protection bit (Program Memory code protection is enabled)
#pragma config CPD = ON         // Data Code Protection bit (Data memory code protection is enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 4000000

/* Defining Parameters */
#define SRCLK GPIObits.GPIO0
#define SER GPIObits.GPIO1
#define RCLK GPIObits.GPIO2
#define inputA GPIObits.GPIO4
#define inputB GPIObits.GPIO5
//--------------------------------- Intializing Registers.
void shift_init()
{
 //--------------------------------- Powering/Initializing Registers.
 //--------------------------------- Enabling Registers.
 //---------------------
 SER = 1;
 SRCLK = 1;
 __delay_ms(1);
 SRCLK = 0;
 __delay_ms(1);
 RCLK = 1;
 __delay_ms(10);
 RCLK = 0;
 SER = 0;
 for(int i=0;i<8;i++)
  {
    SRCLK = 1;
    __delay_ms(1);
    SRCLK = 0;
    __delay_ms(1);
    RCLK = 1;
    __delay_ms(1);
    RCLK = 0;
    __delay_ms(100);
  }
 //--------------------------------- Disabling Registers.
 //---------------------
}
//--------------------------------- Custom Function to reset Registers.
void shift_reset()
{
 SER = 0;
 for(int i=0;i<8;i++)
    {
      SRCLK = 1;
      __delay_ms(1);
      SRCLK = 0;
      __delay_ms(1);
    }
    RCLK = 1;
    __delay_ms(1);
    RCLK = 0;
}
//------------------------------------------ Custom Function to display Registers.
void shift_lights()
{
    for(int i=0;i<9;i++)
        {
          SRCLK = 1;
          __delay_ms(1);
          SRCLK = 0;
          __delay_ms(1);
          SER = 1;
        }
      RCLK = 1;
      __delay_ms(1);
      RCLK = 0;
      __delay_ms(100);
      //--------------------------------- Enabling Registers.
     //---------------------  
}
void main()
{
// OSCCALbits.CAL = 0xFF;// Set Maximum Oscillator frequency.
 ANSEL = 0x00;
 CMCONbits.CM = 0x07;
 TRISIO = 0x00;
 GPIO = 0x00;
 while(1)
   {
     // When go downstairs.
     if(inputA == 1 && inputB == 0)
     {
       shift_lights();
       __delay_ms(10000);
       shift_reset();
     }
     // When go Upstairs.
     if(inputA == 0 && inputB == 1)
     {
       shift_lights();
       __delay_ms(10000);
       shift_reset();
     }
     // When default.
     if(inputA == 1 && inputB == 1)
     {
       shift_reset();
     }
     // When default.
     if(inputA == 0 && inputB == 0)
     {
       shift_reset();
     }
  }
}