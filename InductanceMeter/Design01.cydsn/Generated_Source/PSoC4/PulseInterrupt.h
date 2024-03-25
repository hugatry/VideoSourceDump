/*******************************************************************************
* File Name: PulseInterrupt.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_PulseInterrupt_H)
#define CY_ISR_PulseInterrupt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void PulseInterrupt_Start(void);
void PulseInterrupt_StartEx(cyisraddress address);
void PulseInterrupt_Stop(void);

CY_ISR_PROTO(PulseInterrupt_Interrupt);

void PulseInterrupt_SetVector(cyisraddress address);
cyisraddress PulseInterrupt_GetVector(void);

void PulseInterrupt_SetPriority(uint8 priority);
uint8 PulseInterrupt_GetPriority(void);

void PulseInterrupt_Enable(void);
uint8 PulseInterrupt_GetState(void);
void PulseInterrupt_Disable(void);

void PulseInterrupt_SetPending(void);
void PulseInterrupt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the PulseInterrupt ISR. */
#define PulseInterrupt_INTC_VECTOR            ((reg32 *) PulseInterrupt__INTC_VECT)

/* Address of the PulseInterrupt ISR priority. */
#define PulseInterrupt_INTC_PRIOR             ((reg32 *) PulseInterrupt__INTC_PRIOR_REG)

/* Priority of the PulseInterrupt interrupt. */
#define PulseInterrupt_INTC_PRIOR_NUMBER      PulseInterrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable PulseInterrupt interrupt. */
#define PulseInterrupt_INTC_SET_EN            ((reg32 *) PulseInterrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the PulseInterrupt interrupt. */
#define PulseInterrupt_INTC_CLR_EN            ((reg32 *) PulseInterrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the PulseInterrupt interrupt state to pending. */
#define PulseInterrupt_INTC_SET_PD            ((reg32 *) PulseInterrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the PulseInterrupt interrupt. */
#define PulseInterrupt_INTC_CLR_PD            ((reg32 *) PulseInterrupt__INTC_CLR_PD_REG)



#endif /* CY_ISR_PulseInterrupt_H */


/* [] END OF FILE */
