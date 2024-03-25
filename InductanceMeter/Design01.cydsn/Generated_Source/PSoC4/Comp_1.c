/*******************************************************************************
* File Name: Comp_1.c
* Version 1.20
*
* Description:
*  This file provides the source code to the API for the Comparator component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Comp_1.h"

uint8 Comp_1_initVar = 0u; /* Defines if component was initialized */
static uint32 Comp_1_internalSpeed = 0u; /* Defines component Speed value */


/*******************************************************************************
* Function Name: Comp_1_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure 
*  dialog settings. It is not necessary to call Init() because the Start() API 
*  calls this function and is the preferred method to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Comp_1_Init(void)
{
    uint8 enableInterrupts;
    
    Comp_1_internalSpeed = Comp_1_POWER;
    Comp_1_CTB_CTRL_REG = Comp_1_DEFAULT_CTB_CTRL;
    Comp_1_OA_RES_CTRL_REG = Comp_1_DEFAULT_OA_RES_CTRL;
    
    enableInterrupts = CyEnterCriticalSection();
    Comp_1_INTR_MASK_REG |= Comp_1_INTR_MASK_REG_DEFAULT;
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Comp_1_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins the component operation. It is not necessary to 
*  call Enable() because the Start() API calls this function, which is the 
*  preferred method to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Comp_1_Enable(void)
{
    Comp_1_OA_RES_CTRL_REG |= Comp_1_internalSpeed | \
                                        Comp_1_OA_PUMP_EN;
}


/*******************************************************************************
* Function Name: Comp_1_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the component and enables 
*  power to the block. The first time the routine is executed, the speed/power 
*  level, and hysteresis are set. When called to restart the comparator 
*  following a Stop() call, the current component parameter settings are retained.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Comp_1_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Comp_1_Start(void)
{
    if( 0u == Comp_1_initVar)
    {
        Comp_1_Init();
        Comp_1_initVar = 1u;
    }
    Comp_1_Enable();
}


/*******************************************************************************
* Function Name: Comp_1_Stop
********************************************************************************
*
* Summary:
*  Turns off the comparator block.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Does not affect the comparator speed settings.
*
*******************************************************************************/
void Comp_1_Stop(void)
{
    Comp_1_OA_CTRL_REG &= ((uint32)~(Comp_1_OA_PWR_MODE_MASK | \
                                               Comp_1_OA_PUMP_EN));
}


/*******************************************************************************
* Function Name: Comp_1_SetSpeed
********************************************************************************
*
* Summary:
*  Sets the speed to one of three settings: slow, medium, or fast.
*
* Parameters:
*  speed: Enumerated speed mode value.
*   Comp_1_SLOW_SPEED  - Slow speed
*   Comp_1_MED_SPEED   - Medium speed
*   Comp_1_FAST_SPEED  - Fast speed
*
* Return:
*  None
*
*******************************************************************************/
void Comp_1_SetSpeed(uint32 speed)
{
    uint32 tmp;
    
    Comp_1_internalSpeed = Comp_1_GET_OA_PWR_MODE(speed);
    tmp = Comp_1_OA_RES_CTRL_REG & \
           (uint32)~Comp_1_OA_PWR_MODE_MASK;
    Comp_1_OA_RES_CTRL_REG = tmp | Comp_1_internalSpeed;
}


/*******************************************************************************
* Function Name: Comp_1_ZeroCal
********************************************************************************
*
* Summary:
*  Performs custom calibration of the input offset to minimize the error for a 
*  specific set of conditions: the comparator reference voltage, supply voltage, 
*  and operating temperature. A reference voltage in the range at which the 
*  comparator will be used must be applied to the Negative and Positive inputs 
*  of the comparator while the offset calibration is performed. This can be done 
*  external to the device or by using an internal analog mux on the positive input 
*  that selects between the positive input signal for normal operation and the 
*  negative input signal for calibration.
*
* Parameters:
*  None
*
* Return:
*  (uint32): The value from the comparator trim register after the offset 
*  calibration is complete. This value has the same format as the input parameter 
*  for the LoadTrim() API routine.
*
*
* Side Effects:
*  During the calibration procedure, the comparator output may behave erratically. 
*  The comparator output should be ignored during calibration.
*
*******************************************************************************/
uint32 Comp_1_ZeroCal(void)
{
    uint32 cmpOut;
    uint32 i;
    
    /* Clear trim registers before trimming */
    Comp_1_OA_OFFSET_TRIM_REG       = 0u;
    Comp_1_OA_SLOPE_OFFSET_TRIM_REG = 0u;
    
    /* Check comparator's output state */
    cmpOut = Comp_1_GetCompare();
    
    /* Connect the outputs of trim IDACs to the positive
    * output leg of the folded cascade 
    */
    if(cmpOut == 0u)
    {
        Comp_1_OA_OFFSET_TRIM_REG       = ((uint32) 1u << Comp_1_COMP_TRIM_SIGN_SHIFT);
        Comp_1_OA_SLOPE_OFFSET_TRIM_REG = ((uint32) 1u << Comp_1_COMP_TRIM_SIGN_SHIFT);
    }
        
    /* Searching offset trim setting, 
    * that flips comparator output 
    */
    for(i = Comp_1_COMP_TRIM_MAX_VALUE; i != 0u; i--)
    {
        Comp_1_OA_OFFSET_TRIM_REG++;
        CyDelayUs(Comp_1_COMP_CALIBRATION_DELAY);
        if(cmpOut != Comp_1_GetCompare())
        {
            break;
        }
    }
    
    /* Returns offset trim value */
    return (Comp_1_OA_OFFSET_TRIM_REG);
}


/*******************************************************************************
* Function Name: Comp_1_LoadTrim
********************************************************************************
*
* Summary:
*  This function writes a value into the comparator offset trim register.
*
* Parameters:
*  uint32 trimVal: Value to be stored in the comparator offset trim register. 
*  This value has the same format as the parameter returned by the ZeroCal() 
*  routine.
*
* Return:
*  None
*
*******************************************************************************/
void Comp_1_LoadTrim(uint32 trimVal)
{
    Comp_1_OA_OFFSET_TRIM_REG = trimVal;
}


/*******************************************************************************
* Function Name: Comp_1_GetCompare
********************************************************************************
*
* Summary:
*  This function returns a non-zero value when the voltage connected to the positive 
*  input is greater than the negative input voltage. This value is not affected by 
*  the Polarity parameter. This value always reflects a non-inverted state 
*  configuration.
*  This function reads the direct (unflopped) comparator output which can also be 
*  metastable (since it may result in incorrect data).
*
* Parameters:
*   None
*
* Return:
*  The comparator output state. A non-zero value when the positive input voltage is 
*  greater than the negative input voltage; otherwise, the return value is zero.
*
*******************************************************************************/
uint32 Comp_1_GetCompare(void)
{
    return ((uint32)(Comp_1_OA_COMP_STAT_REG >> Comp_1_OA_COMP_SHIFT) & 1u);
}


/*******************************************************************************
* Function Name: Comp_1_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests. This function is for use when using the combined
*  interrupt signal from the global signal reference. This function from either
*  component instance can be used to determine the interrupt source for all the
*  comparator interrupts combined.
*
* Parameters:
*  None
*
* Return:
*  uint32: Interrupt source. Each component instance has a mask value:
*  Comp_1_INTR.
*
*******************************************************************************/
uint32 Comp_1_GetInterruptSource(void)
{
    return (Comp_1_INTR_REG); 
}


/*******************************************************************************
* Function Name: Comp_1_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request. This function is for use when using the
*  combined interrupt signal from the global signal reference. This function
*  from either component instance can be used to clear either or both
*  interrupts.
*
* Parameters:
*  uint32 interruptMask: Mask of interrupts to clear. Each component instance
*  has a mask value: Comp_1_INTR.
*
* Return:
*  None
*
*******************************************************************************/
void Comp_1_ClearInterrupt(uint32 interruptMask)
{   
    Comp_1_INTR_REG = interruptMask;
}


/*******************************************************************************
* Function Name: Comp_1_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request. This function is for use when using the
*  combined interrupt signal from the global signal reference. This function
*  from either component instance can be used to trigger either or both software
*  interrupts.
*
* Parameters:
*  uint32 interruptMask: Mask of interrupts to set. Each component instance has
*  a mask value: Comp_1_INTR_SET.
*
* Return:
*  None
*
*******************************************************************************/
void Comp_1_SetInterrupt(uint32 interruptMask)
{
    uint8 enableInterrupts;
    
    enableInterrupts = CyEnterCriticalSection();
    Comp_1_INTR_SET_REG |= interruptMask;
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Comp_1_SetInterruptMask
********************************************************************************
*
* Summary:
*  Configures the interrupt mask for all comparators in the system.
*
* Parameters:
*  uint32 interruptMask: Bit-mask of interrupt sources to be enabled. Each 
*  component instance has a mask value: Comp_1_INTR_MASK.
*
* Return:
*  None
*
*******************************************************************************/
void Comp_1_SetInterruptMask(uint32 interruptMask)
{
    Comp_1_INTR_MASK_REG = interruptMask;
}


/*******************************************************************************
* Function Name: Comp_1_GetInterruptMask
********************************************************************************
*
* Summary:
*  Returns interrupt mask for all comparators.
*
* Parameters:
*  None
*
* Return:
*  uint32:  Mask of enabled interrupt source. Each component instance 
*  has a mask value: Comp_1_INTR_MASK.
*
*******************************************************************************/
uint32 Comp_1_GetInterruptMask(void)
{
    return (Comp_1_INTR_MASK_REG);
}


/*******************************************************************************
* Function Name: Comp_1_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Returns interrupt request register masked by interrupt mask for all comparators. 
*  Returns the result of bitwise AND operation between corresponding interrupt 
*  request and mask bits.
*
* Parameters:
*  None
*
* Return:
*  uint32: Status of enabled interrupt source. Each component instance 
*  has a mask value: Comp_1_INTR_MASKED.
*
*******************************************************************************/
uint32 Comp_1_GetInterruptSourceMasked(void)
{
    return (Comp_1_INTR_MASKED_REG);
}

/*******************************************************************************
* Function Name: Comp_1_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt edge detect mode.
*
* Parameters:
*  uint32 mode: Enumerated edge detect mode value:
*  Comp_1_INTR_DISABLE - Disable
*  Comp_1_INTR_RISING  - Rising edge detect
*  Comp_1_INTR_FALLING - Falling edge detect
*  Comp_1_INTR_BOTH    - Detect both edges
*
* Return:
*  None
*
*******************************************************************************/
void Comp_1_SetInterruptMode(uint32 mode)
{
    uint32 tmp;

    tmp = Comp_1_OA_RES_CTRL_REG & (uint32)~Comp_1_OA_COMPINT_MASK;
    Comp_1_OA_RES_CTRL_REG = tmp | Comp_1_GET_OA_COMPINT(mode);
}

/*******************************************************************************
* Function Name: Comp_1_DisableInterruptOutput
********************************************************************************
*
* Summary:
*  Disables the interrupt output so that it will not be ORed to the global 
*  Signal CTBmInt with the other comparator interrupt outputs.  
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Comp_1_DisableInterruptOutput(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    Comp_1_INTR_MASK_REG &= ~Comp_1_INTR_MASK;
    CyExitCriticalSection(enableInterrupts);
}


/* [] END OF FILE */
