/**
 ***************************************************************************************
 * File Name          : PIC12f675 Durga Company Project
 * Description        : Main Project - 2 Output GP0 & GP5 & 4 Input 
 *                       
 * Project Number     : 1
 * Author             : Design - Yogesh Shende  ( 7350350883 ) 
 * Project Details    :
 **************************************************************************************/
/* Code data as per customer details show below > 
1. As soon as the IC is powered on, 5-Volt comes on GP5 and after 60sec it becomes 0-volt
2. If Ground is given on GP4 and 5-Volt on GP5 then it becomes 0-volt immediately. Otherwise it becomes 0-volt after 60sec.
3. Now if there is Ground on GP4 and GP1 also becomes Ground, then 5-Volt will come on GP0 and GP5 becomes 0-Volt immediately.
Now if there is Ground on GP4 and as soon as Ground is removed from GP1, GP0 becomes 0-Volt immediately. Otherwise it becomes 0-volt after 60 sec.
In this way the program continued.
4. Now if we ground GP2 then 5-Volt will come on GP5 for 15sec. If GP3 becomes ground before 15sec, then GP5 becomes 0-volt immediately.      
If GP3 is not ground for 15sec then GP5 becomes 0-volt and GP0 becomes 5-volt for 15sec otherwise GP0 becomes 0-volt after 15 sec.
 */
/****************************************************************************************
                               Include
 ****************************************************************************************/
#include <xc.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
/****************************************************************************************
                               Define Macro
 ****************************************************************************************/
#define Relay1_Out GP5
#define Relay2_Out GP0
#define Sensor1_In GP4 // ground in
#define Sensor2_In GP1 // 
#define Start_Switch_In GP3
#define Stop_Switch_In GP2

/* Define Freq Macro */
#define _XTAL_FREQ 4000000



/****************************************************************************************
                               Flags
 ****************************************************************************************/
int flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;
/***************************************************************************************
                               variable
 *****************************************************************************************/
unsigned long int count = 0UL;
unsigned int i = 0, j = 0, l = 0;


// PIC12F675 Configuration Bit Settings
// 'C' source line config statements
// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = ON          // Code Protection bit (Program Memory code protection is enabled)
#pragma config CPD = ON         // Data Code Protection bit (Data memory code protection is enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

/***************************************************************************************
                                Main Function
 *****************************************************************************************/
void main(void) {
    ANSEL = 0x00; /* Set ports as digital I/O, not analog input */
    ADCON0 = 0x00; /* Shut off the A/D Converter */
    CMCON = 0x07; /* Shut off the Comparator */
    VRCON = 0x00; /* Shut off the Voltage Reference */
    /*76543210*/
    TRISIO = 0b11011110;
    OPTION_REG = 0b00000111;
    GPIO = 0x00; /* Make all pins 0 */
    Relay1_Out = 0;
    Relay2_Out = 0;
    while (1) {
        /**** Start 1st Step ******/

        if (Start_Switch_In == 0) {
            __delay_us(20);
            if (Start_Switch_In == 0) {
                Relay1_Out = 1;
                flag1 = 0;
                 /* wait for 5 sec off the Relay 1 */
                while (count < 4055UL && Stop_Switch_In == 1u && flag1 == 0u) { count++; __delay_ms(1); }
                count = 0u;
                flag1 = 1u;
                Relay1_Out = 0;
            }
        }

        if (Stop_Switch_In == 0u) {
            __delay_us(20);
            if (Stop_Switch_In == 0u) {
                Relay1_Out = 0;
                Relay2_Out = 0;
            }
        }

        /****End 1st Step & Start 2ns step ******/
        
        if (Sensor2_In == 0u && flag1 == 1u) {
             /* wait for 2 sec to check sensor 2 press */
            while (count < 1622UL && Sensor2_In == 0u &&Stop_Switch_In==1u && flag1 == 0u) {count++;__delay_ms(1); }
            if (Sensor2_In == 0u && flag1 == 1u) {
                Relay1_Out = 0;
                Relay2_Out = 1;
                flag1 = 0;
                while (count < 3244UL &&Stop_Switch_In==1u&& flag1 == 0u) {count++; __delay_ms(1);}
                Relay2_Out = 0;
            }
        }

        /* End 2nd step & 3rd start  */

        if (Sensor1_In == 0u && flag1 == 1u) {
            /* wait for 3 sec to check sensor 1 press */
            while (count < 2433UL && Sensor1_In == 0u && Stop_Switch_In==1&&flag1 == 0u) {count++;__delay_ms(1);}
             if (Sensor1_In == 0u && flag1 == 1u) {
                 flag1=0;
                 Relay1_Out=0;
             }}


        }
    }



    /****************1***********************************************************************/
    /*****************************END OF FILE **********************************************/
    /****************************************************************************************
     __ These Program is Design by Yogesh Shende and sale to Mrs. Sandeep Mahajan 
     * all authority at customer to Copy , Edit , modify & sale
     ****************************************************************************************/
