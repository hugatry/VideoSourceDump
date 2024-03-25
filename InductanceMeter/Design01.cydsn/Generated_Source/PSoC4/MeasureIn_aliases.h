/*******************************************************************************
* File Name: MeasureIn.h  
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

#if !defined(CY_PINS_MeasureIn_ALIASES_H) /* Pins MeasureIn_ALIASES_H */
#define CY_PINS_MeasureIn_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define MeasureIn_0			(MeasureIn__0__PC)
#define MeasureIn_0_PS		(MeasureIn__0__PS)
#define MeasureIn_0_PC		(MeasureIn__0__PC)
#define MeasureIn_0_DR		(MeasureIn__0__DR)
#define MeasureIn_0_SHIFT	(MeasureIn__0__SHIFT)
#define MeasureIn_0_INTR	((uint16)((uint16)0x0003u << (MeasureIn__0__SHIFT*2u)))

#define MeasureIn_INTR_ALL	 ((uint16)(MeasureIn_0_INTR))


#endif /* End Pins MeasureIn_ALIASES_H */


/* [] END OF FILE */
