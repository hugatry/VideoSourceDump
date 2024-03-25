/*******************************************************************************
* File Name: Comp_1.h
* Version 1.20
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Analog Comparator User Module.
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

#if !defined(CY_COMPARATOR_Comp_1_H)
#define CY_COMPARATOR_Comp_1_H

#include "cytypes.h"
#include "CyLib.h"
#include "cyfitter.h"


/***************************************
*       Type Definitions
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} Comp_1_BACKUP_STRUCT;


/**************************************
*        Function Prototypes
**************************************/
void    Comp_1_Init(void);
void    Comp_1_Enable(void);
void    Comp_1_Start(void);
void    Comp_1_Stop(void);
void    Comp_1_SetSpeed(uint32 speed);
uint32  Comp_1_ZeroCal(void);
void    Comp_1_LoadTrim(uint32 trimVal);
void    Comp_1_Sleep(void);
void    Comp_1_Wakeup(void);
void    Comp_1_SaveConfig(void);
void    Comp_1_RestoreConfig(void);
uint32  Comp_1_GetCompare(void);
uint32  Comp_1_GetInterruptSource(void);
void    Comp_1_ClearInterrupt(uint32 interruptMask);
void    Comp_1_SetInterrupt(uint32 interruptMask);
void    Comp_1_SetInterruptMask(uint32 interruptMask);
uint32  Comp_1_GetInterruptMask(void);
uint32  Comp_1_GetInterruptSourceMasked(void);
void    Comp_1_SetInterruptMode(uint32 mode);
void    Comp_1_DisableInterruptOutput(void);

#define Comp_1_EnableInterruptOutput(void)     Comp_1_SetInterruptMask(Comp_1_GetInterruptMask() | Comp_1_INTR_MASK)
#define Comp_1_GetInterruptOutputStatus(void)  ((0u == (Comp_1_GetInterruptSourceMasked() & Comp_1_INTR_MASKED)) ? 0u : 1u)
#define Comp_1_ClearInterruptOutput(void)      Comp_1_ClearInterrupt(Comp_1_INTR)
#define Comp_1_SetInterruptOutput(void)        Comp_1_SetInterrupt(Comp_1_INTR_MASK)

/**************************************
*           API Constants
**************************************/

/* Power constants for SetSpeed() function */
#define Comp_1_SLOW_SPEED     (0x01u)
#define Comp_1_MED_SPEED      (0x02u)
#define Comp_1_HIGH_SPEED     (0x03u)

/* Trim defines for ZeroCal() function */
#define Comp_1_COMP_TRIM_SIGN_SHIFT   (5u)
#define Comp_1_COMP_TRIM_MAX_VALUE    (32u)
#define Comp_1_COMP_CALIBRATION_DELAY (10u)

/* Constants for Comp_1_SetInterruptMode(), mode parameter */
#define Comp_1_INTR_DISABLE       (0x00u)
#define Comp_1_INTR_RISING        (0x01u)
#define Comp_1_INTR_FALLING       (0x02u)
#define Comp_1_INTR_BOTH          (0x03u)

/* Constants for Comp_1_GetInterruptSource() and 
* Comp_1_ClearInterrupt(), interruptMask parameter 
*/
#define Comp_1_INTR_SHIFT         (Comp_1_cy_psoc4_abuf__INTR_SHIFT)
#define Comp_1_INTR               ((uint32)0x01u << Comp_1_INTR_SHIFT)

/* Constants for Comp_1_SetInterrupt(), interruptMask parameter */
#define Comp_1_INTR_SET_SHIFT     (Comp_1_cy_psoc4_abuf__INTR_SET_SHIFT)
#define Comp_1_INTR_SET           ((uint32)0x01u << Comp_1_INTR_SHIFT)

/* Constants for Comp_1_GetInterruptMask() and 
* Comp_1_SetInterruptMask(), interruptMask parameter 
*/
#define Comp_1_INTR_MASK_SHIFT    (Comp_1_cy_psoc4_abuf__INTR_MASK_SHIFT)
#define Comp_1_INTR_MASK          ((uint32)0x01u << Comp_1_INTR_MASK_SHIFT)

/* Constants for Comp_1_GetInterruptSourceMasked() */ 
#define Comp_1_INTR_MASKED_SHIFT  (Comp_1_cy_psoc4_abuf__INTR_MASKED_SHIFT)
#define Comp_1_INTR_MASKED        ((uint32)0x01u << Comp_1_INTR_MASKED_SHIFT)


/***************************************
*   Initial Parameter Constants
****************************************/

#define Comp_1_HYSTERESIS         (1u)
#define Comp_1_POWER              (3u)
#define Comp_1_DEEPSLEEP_SUPPORT  (0u)
#define Comp_1_INTERRUPT_EN       (0u)
#define Comp_1_INTERRUPT          (0u)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint8  Comp_1_initVar;


/**************************************
*             Registers
**************************************/

#ifdef CYIPBLOCK_m0s8pass4b_VERSION
    #define Comp_1_CTB_CTRL_REG       (*(reg32 *) Comp_1_cy_psoc4_abuf__CTB_CTB_CTRL)
    #define Comp_1_CTB_CTRL_PTR       ( (reg32 *) Comp_1_cy_psoc4_abuf__CTB_CTB_CTRL)
#else
    #define Comp_1_CTB_CTRL_REG       (*(reg32 *) Comp_1_cy_psoc4_abuf__CTBM_CTB_CTRL)
    #define Comp_1_CTB_CTRL_PTR       ( (reg32 *) Comp_1_cy_psoc4_abuf__CTBM_CTB_CTRL)
#endif /* CYIPBLOCK_m0s8pass4b_VERSION */

#define Comp_1_OA_RES_CTRL_REG            (* (reg32 *) Comp_1_cy_psoc4_abuf__OA_RES_CTRL)
#define Comp_1_OA_RES_CTRL_PTR            (  (reg32 *) Comp_1_cy_psoc4_abuf__OA_RES_CTRL)

#define Comp_1_OA_COMP_STAT_REG           (* (reg32 *) Comp_1_cy_psoc4_abuf__COMP_STAT)
#define Comp_1_OA_COMP_STAT_PTR           (  (reg32 *) Comp_1_cy_psoc4_abuf__COMP_STAT)

#define Comp_1_OA_OFFSET_TRIM_REG         (* (reg32 *) Comp_1_cy_psoc4_abuf__OA_OFFSET_TRIM)
#define Comp_1_OA_OFFSET_TRIM_PTR         (  (reg32 *) Comp_1_cy_psoc4_abuf__OA_OFFSET_TRIM)

#define Comp_1_OA_SLOPE_OFFSET_TRIM_REG   (* (reg32 *) Comp_1_cy_psoc4_abuf__OA_SLOPE_OFFSET_TRIM)
#define Comp_1_OA_SLOPE_OFFSET_TRIM_PTR   (  (reg32 *) Comp_1_cy_psoc4_abuf__OA_SLOPE_OFFSET_TRIM)

#define Comp_1_OA_COMP_SHIFT              (Comp_1_cy_psoc4_abuf__COMP_STAT_SHIFT)

#define Comp_1_INTR_REG       (*(reg32 *)Comp_1_cy_psoc4_abuf__INTR)
#define Comp_1_INTR_PTR       ( (reg32 *)Comp_1_cy_psoc4_abuf__INTR)

#define Comp_1_INTR_SET_REG   (*(reg32 *)Comp_1_cy_psoc4_abuf__INTR_SET)
#define Comp_1_INTR_SET_PTR   ( (reg32 *)Comp_1_cy_psoc4_abuf__INTR_SET)

#define Comp_1_INTR_MASK_REG    (*(reg32 *)Comp_1_cy_psoc4_abuf__INTR_MASK) 
#define Comp_1_INTR_MASK_PTR    ( (reg32 *)Comp_1_cy_psoc4_abuf__INTR_MASK) 

#define Comp_1_INTR_MASKED_REG  (*(reg32 *)Comp_1_cy_psoc4_abuf__INTR_MASKED) 
#define Comp_1_INTR_MASKED_PTR  ( (reg32 *)Comp_1_cy_psoc4_abuf__INTR_MASKED)

/***************************************
*        Registers Constants
***************************************/

/* Comp_1_CTB_CTRL_REG */
#define Comp_1_CTB_CTRL_DEEPSLEEP_ON_SHIFT    (30u)   /* [30] Selects behavior CTB IP in the DeepSleep power mode */
#define Comp_1_CTB_CTRL_ENABLED_SHIFT         (31u)   /* [31] Enable of the CTB IP */

#define Comp_1_CTB_CTRL_DEEPSLEEP_ON          ((uint32) 0x01u << Comp_1_CTB_CTRL_DEEPSLEEP_ON_SHIFT)
#define Comp_1_CTB_CTRL_ENABLED               ((uint32) 0x01u << Comp_1_CTB_CTRL_ENABLED_SHIFT)

/* Comp_1_OA_RES_CTRL_REG */
#define Comp_1_OA_PWR_MODE_SHIFT          (0u)    /* [1:0]    Power level */
#define Comp_1_OA_COMP_EN_SHIFT           (4u)    /* [4]      Comparator enable */
#define Comp_1_OA_HYST_EN_SHIFT           (5u)    /* [5]      Hysteresis enable (10mV) */
#define Comp_1_OA_BYPASS_DSI_SYNC_SHIFT   (6u)    /* [6]      Bypass comparator output synchronization for DSI (trigger) output */
#define Comp_1_OA_COMPINT_SHIFT           (8u)    /* [9:8]    Sets Interrupt mode */
#define Comp_1_OA_PUMP_EN_SHIFT           (11u)   /* [11]     Pump enable */

#define Comp_1_OA_PWR_MODE                ((uint32) 0x02u << Comp_1_OA_PWR_MODE_SHIFT)
#define Comp_1_OA_PWR_MODE_MASK           ((uint32) 0x03u << Comp_1_OA_PWR_MODE_SHIFT)
#define Comp_1_OA_COMP_EN                 ((uint32) 0x01u << Comp_1_OA_COMP_EN_SHIFT)
#define Comp_1_OA_HYST_EN                 ((uint32) 0x01u << Comp_1_OA_HYST_EN_SHIFT)
#define Comp_1_OA_BYPASS_DSI_SYNC         ((uint32) 0x01u << Comp_1_OA_BYPASS_DSI_SYNC_SHIFT)
#define Comp_1_OA_COMPINT_MASK            ((uint32) 0x03u << Comp_1_OA_COMPINT_SHIFT)
#define Comp_1_OA_PUMP_EN                 ((uint32) 0x01u << Comp_1_OA_PUMP_EN_SHIFT)


/***************************************
*       Init Macros Definitions
***************************************/

#define Comp_1_GET_DEEPSLEEP_ON(deepSleep)    ((0u != (deepSleep)) ? (Comp_1_CTB_CTRL_DEEPSLEEP_ON) : (0u))
#define Comp_1_GET_OA_HYST_EN(hyst)           ((0u != (hyst)) ? (Comp_1_OA_HYST_EN) : (0u))
#define Comp_1_GET_OA_PWR_MODE(mode)          ((mode) & Comp_1_OA_PWR_MODE_MASK)
#define Comp_1_CHECK_PWR_MODE_OFF             (0u != (Comp_1_OA_RES_CTRL_REG & \
                                                                Comp_1_OA_PWR_MODE_MASK))
#define Comp_1_GET_OA_COMPINT(intType)        ((uint32) ((((uint32)(intType) << Comp_1_OA_COMPINT_SHIFT)) & \
                                                        Comp_1_OA_COMPINT_MASK))

#define Comp_1_GET_INTR_MASK(mask)            ((0u != (mask)) ? (Comp_1_INTR_MASK) : (0u))

/* Returns true if component available in Deep Sleep power mode*/ 
#define Comp_1_CHECK_DEEPSLEEP_SUPPORT        (0u != Comp_1_DEEPSLEEP_SUPPORT) 

#define Comp_1_DEFAULT_CTB_CTRL (Comp_1_GET_DEEPSLEEP_ON(Comp_1_DEEPSLEEP_SUPPORT) | \
                                           Comp_1_CTB_CTRL_ENABLED)

#define Comp_1_DEFAULT_OA_RES_CTRL (Comp_1_OA_COMP_EN | \
                                              Comp_1_GET_OA_HYST_EN(Comp_1_HYSTERESIS)  | \
                                              Comp_1_GET_OA_COMPINT(Comp_1_INTERRUPT) |\
                                              Comp_1_OA_BYPASS_DSI_SYNC)

#define Comp_1_INTR_MASK_REG_DEFAULT  (Comp_1_GET_INTR_MASK(Comp_1_INTERRUPT_EN))


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

/* Power constants for SetSpeed() function */
#define Comp_1_SLOWSPEED      (Comp_1_SLOW_SPEED)
#define Comp_1_MEDSPEED       (Comp_1_MED_SPEED)
#define Comp_1_HIGHSPEED      (Comp_1_HIGH_SPEED)

#define Comp_1_OA_CTRL_REG        (Comp_1_OA_RES_CTRL_REG)
#define Comp_1_OA_COMPSTAT_REG    (Comp_1_OA_COMP_STAT_REG)
#define Comp_1_OA_COMPSHIFT       (Comp_1_OA_COMP_SHIFT)

#define Comp_1_OA_CTB_EN_SHIFT    (Comp_1_CTB_CTRL_ENABLED_SHIFT)
#define Comp_1_OA_PWR_MODE_HIGH   (Comp_1_HIGH_SPEED) 
#define Comp_1_OA_BYPASS_SHIFT    (Comp_1_OA_BYPASS_DSI_SYNC_SHIFT)

#endif /*  CY_COMPARATOR_Comp_1_H */


/* [] END OF FILE */
