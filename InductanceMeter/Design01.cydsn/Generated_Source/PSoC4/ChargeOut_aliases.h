/*******************************************************************************
* File Name: ChargeOut.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ChargeOut_ALIASES_H) /* Pins ChargeOut_ALIASES_H */
#define CY_PINS_ChargeOut_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ChargeOut_0			(ChargeOut__0__PC)
#define ChargeOut_0_PS		(ChargeOut__0__PS)
#define ChargeOut_0_PC		(ChargeOut__0__PC)
#define ChargeOut_0_DR		(ChargeOut__0__DR)
#define ChargeOut_0_SHIFT	(ChargeOut__0__SHIFT)
#define ChargeOut_0_INTR	((uint16)((uint16)0x0003u << (ChargeOut__0__SHIFT*2u)))

#define ChargeOut_INTR_ALL	 ((uint16)(ChargeOut_0_INTR))


#endif /* End Pins ChargeOut_ALIASES_H */


/* [] END OF FILE */
