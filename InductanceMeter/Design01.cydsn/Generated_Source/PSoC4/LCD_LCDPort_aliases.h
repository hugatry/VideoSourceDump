/*******************************************************************************
* File Name: LCD_LCDPort.h  
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

#if !defined(CY_PINS_LCD_LCDPort_ALIASES_H) /* Pins LCD_LCDPort_ALIASES_H */
#define CY_PINS_LCD_LCDPort_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define LCD_LCDPort_0			(LCD_LCDPort__0__PC)
#define LCD_LCDPort_0_PS		(LCD_LCDPort__0__PS)
#define LCD_LCDPort_0_PC		(LCD_LCDPort__0__PC)
#define LCD_LCDPort_0_DR		(LCD_LCDPort__0__DR)
#define LCD_LCDPort_0_SHIFT	(LCD_LCDPort__0__SHIFT)
#define LCD_LCDPort_0_INTR	((uint16)((uint16)0x0003u << (LCD_LCDPort__0__SHIFT*2u)))

#define LCD_LCDPort_1			(LCD_LCDPort__1__PC)
#define LCD_LCDPort_1_PS		(LCD_LCDPort__1__PS)
#define LCD_LCDPort_1_PC		(LCD_LCDPort__1__PC)
#define LCD_LCDPort_1_DR		(LCD_LCDPort__1__DR)
#define LCD_LCDPort_1_SHIFT	(LCD_LCDPort__1__SHIFT)
#define LCD_LCDPort_1_INTR	((uint16)((uint16)0x0003u << (LCD_LCDPort__1__SHIFT*2u)))

#define LCD_LCDPort_2			(LCD_LCDPort__2__PC)
#define LCD_LCDPort_2_PS		(LCD_LCDPort__2__PS)
#define LCD_LCDPort_2_PC		(LCD_LCDPort__2__PC)
#define LCD_LCDPort_2_DR		(LCD_LCDPort__2__DR)
#define LCD_LCDPort_2_SHIFT	(LCD_LCDPort__2__SHIFT)
#define LCD_LCDPort_2_INTR	((uint16)((uint16)0x0003u << (LCD_LCDPort__2__SHIFT*2u)))

#define LCD_LCDPort_3			(LCD_LCDPort__3__PC)
#define LCD_LCDPort_3_PS		(LCD_LCDPort__3__PS)
#define LCD_LCDPort_3_PC		(LCD_LCDPort__3__PC)
#define LCD_LCDPort_3_DR		(LCD_LCDPort__3__DR)
#define LCD_LCDPort_3_SHIFT	(LCD_LCDPort__3__SHIFT)
#define LCD_LCDPort_3_INTR	((uint16)((uint16)0x0003u << (LCD_LCDPort__3__SHIFT*2u)))

#define LCD_LCDPort_4			(LCD_LCDPort__4__PC)
#define LCD_LCDPort_4_PS		(LCD_LCDPort__4__PS)
#define LCD_LCDPort_4_PC		(LCD_LCDPort__4__PC)
#define LCD_LCDPort_4_DR		(LCD_LCDPort__4__DR)
#define LCD_LCDPort_4_SHIFT	(LCD_LCDPort__4__SHIFT)
#define LCD_LCDPort_4_INTR	((uint16)((uint16)0x0003u << (LCD_LCDPort__4__SHIFT*2u)))

#define LCD_LCDPort_5			(LCD_LCDPort__5__PC)
#define LCD_LCDPort_5_PS		(LCD_LCDPort__5__PS)
#define LCD_LCDPort_5_PC		(LCD_LCDPort__5__PC)
#define LCD_LCDPort_5_DR		(LCD_LCDPort__5__DR)
#define LCD_LCDPort_5_SHIFT	(LCD_LCDPort__5__SHIFT)
#define LCD_LCDPort_5_INTR	((uint16)((uint16)0x0003u << (LCD_LCDPort__5__SHIFT*2u)))

#define LCD_LCDPort_6			(LCD_LCDPort__6__PC)
#define LCD_LCDPort_6_PS		(LCD_LCDPort__6__PS)
#define LCD_LCDPort_6_PC		(LCD_LCDPort__6__PC)
#define LCD_LCDPort_6_DR		(LCD_LCDPort__6__DR)
#define LCD_LCDPort_6_SHIFT	(LCD_LCDPort__6__SHIFT)
#define LCD_LCDPort_6_INTR	((uint16)((uint16)0x0003u << (LCD_LCDPort__6__SHIFT*2u)))

#define LCD_LCDPort_INTR_ALL	 ((uint16)(LCD_LCDPort_0_INTR| LCD_LCDPort_1_INTR| LCD_LCDPort_2_INTR| LCD_LCDPort_3_INTR| LCD_LCDPort_4_INTR| LCD_LCDPort_5_INTR| LCD_LCDPort_6_INTR))


#endif /* End Pins LCD_LCDPort_ALIASES_H */


/* [] END OF FILE */
