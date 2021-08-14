/* 
 * File:   pwm_control_firmware_12f675.c
 * Author: Liyanage Kalana Perera.
 *
 * Created on December 4, 2020, 7:17 PM
 */

// PIC12F675 Configuration Bit Settings

/*
 Updates :- Yellow Fade-In and Fade-Out added.
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
/*
 * 
 */
#define darksensor_input GPIObits.GPIO0
#define infrared_input GPIObits.GPIO1
#define signal_out GPIObits.GPIO2

signed int check = 0;
signed int check_lock = 0;
void main()
{
// OSCCALbits.CAL = 0xFF;// Set Maximum Oscillator frequency.
 ANSEL = 0x00;
 CMCONbits.CM = 0x07;
 TRISIObits.TRISIO0 = 1;
 TRISIObits.TRISIO2 = 1;
 TRISIObits.TRISIO2 = 0;
 GPIO = 0x00;
 __delay_ms(1000);
 while(1)
   {
     START:
      if(infrared_input == 0)
      {
          check_lock = 1;
         __delay_ms(1);
      }
        if(infrared_input == 1 && check_lock == 1)
        {
            check++;
            check_lock=0;
        }
         if(check == 5)
         {
             signal_out = 1;
             __delay_ms(1000);
             signal_out = 0;
             check = 0;
         }
      
  }
}
/*
 * 
  if(infrared_input == 0)
      {
          check_lock = 1;
         __delay_ms(1);
        if(infrared_input == 1 && check_lock == 1)
        {
            check=1;
            check_lock=0;
        }
 if(check == 1)
 {
 signal_out = 1;
 }else{
 signal_out = 0;
 } 
   if(infrared_input == 0)
      {
          check_lock = 1;
         __delay_ms(1);
        if(infrared_input == 1 && check_lock == 1 && check == 1)
        {
            check=0;
            check_lock=0;
        }
 
 */
