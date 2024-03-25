/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdlib.h>
uint8_t ring = 0;
uint8_t ringPrevious = 0;
uint32_t pulseLength = 0;

//Measured capacitance, 465.E-9 = 465*10^-9 = 465nF
float C = 465.E-9;
// 1/(4*pi^2*f^2*C)

CY_ISR(pulseISR)
{
        //If interrupt was caused by capture-signal and therefore pulse length was measured
        if(PulseLengthTimer_GetInterruptSource() & PulseLengthTimer_STATUS_CAPTURE)
        {
            // Timer counts DOWN from the timer's period set in the configuration.
            // Pulse length measured in clock cycles is (Timer's Period - Captured Value)
            pulseLength = PulseLengthTimer_ReadPeriod()-PulseLengthTimer_ReadCapture();
        }else //Other reason for interrupt = Pulse reading wasn't completed. No valid reading available.
        {
            pulseLength = 0;
        }
        //Indicate that interrupt has updated the value
        ring = !ringPrevious;
        PulseLengthTimer_ClearFIFO();
        //Stop the timer, first input cycle is all we need
        PulseLengthTimer_Stop();
}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    PulseLengthTimer_Start();
    LCD_Start();
    PulseInterrupt_StartEx(pulseISR);
    Comp_1_Start();
    for(;;)
    {
        /* Place your application code here. */

        //Charge the LC tank circuit
        ChargeOut_Write(1);
        CyDelay(50);
        //Enable timer and release LC tank circuit
        PulseLengthTimer_Start();
        ChargeOut_Write(0);
        //Wait 300ms. This should be enough to let LC tank oscillate and timer see the incoming signal
        CyDelay(300); 
        // At this time interrupt service routine should have updated the pulseLength variable
        // ISR also flips a bit to indicate new reading is available
        
        // If variable wasn't changed in interrupt, pulse wasn't detected.
        // No inductor connected?
        if(ring == ringPrevious)
        {
            pulseLength = 0;
        }
        
        //If pulse length is 0, set inductance to 0, otherwise do the calculation L = 1 / (4 * pi^2 * C * f^2)
        uint32_t inductance = pulseLength==0 ? (0) : (uint32_t)(1000000/(4*CY_M_PI*CY_M_PI*C*(24000000/(pulseLength))*(24000000/(pulseLength))));
        
        //Print valid inductance value
        if(inductance < 1.E6 && inductance > 1)
        {
            LCD_ClearDisplay();
            LCD_PrintU32Number(inductance);
            LCD_PrintString(" uh");
        }else //Don't print any value, if out of range
        {
            LCD_ClearDisplay();
            LCD_PrintString("------- uH");
        }
            
        // Set variable to indicate no new reading since last main loop iteration
        ringPrevious = ring;
    }
}

/* [] END OF FILE */
