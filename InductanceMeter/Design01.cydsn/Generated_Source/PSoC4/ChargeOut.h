/*******************************************************************************
* File Name: ChargeOut.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ChargeOut_H) /* Pins ChargeOut_H */
#define CY_PINS_ChargeOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ChargeOut_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} ChargeOut_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   ChargeOut_Read(void);
void    ChargeOut_Write(uint8 value);
uint8   ChargeOut_ReadDataReg(void);
#if defined(ChargeOut__PC) || (CY_PSOC4_4200L) 
    void    ChargeOut_SetDriveMode(uint8 mode);
#endif
void    ChargeOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   ChargeOut_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void ChargeOut_Sleep(void); 
void ChargeOut_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(ChargeOut__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define ChargeOut_DRIVE_MODE_BITS        (3)
    #define ChargeOut_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ChargeOut_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the ChargeOut_SetDriveMode() function.
         *  @{
         */
        #define ChargeOut_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define ChargeOut_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define ChargeOut_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define ChargeOut_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define ChargeOut_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define ChargeOut_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define ChargeOut_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define ChargeOut_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define ChargeOut_MASK               ChargeOut__MASK
#define ChargeOut_SHIFT              ChargeOut__SHIFT
#define ChargeOut_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ChargeOut_SetInterruptMode() function.
     *  @{
     */
        #define ChargeOut_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define ChargeOut_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define ChargeOut_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define ChargeOut_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(ChargeOut__SIO)
    #define ChargeOut_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(ChargeOut__PC) && (CY_PSOC4_4200L)
    #define ChargeOut_USBIO_ENABLE               ((uint32)0x80000000u)
    #define ChargeOut_USBIO_DISABLE              ((uint32)(~ChargeOut_USBIO_ENABLE))
    #define ChargeOut_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define ChargeOut_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define ChargeOut_USBIO_ENTER_SLEEP          ((uint32)((1u << ChargeOut_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << ChargeOut_USBIO_SUSPEND_DEL_SHIFT)))
    #define ChargeOut_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << ChargeOut_USBIO_SUSPEND_SHIFT)))
    #define ChargeOut_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << ChargeOut_USBIO_SUSPEND_DEL_SHIFT)))
    #define ChargeOut_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(ChargeOut__PC)
    /* Port Configuration */
    #define ChargeOut_PC                 (* (reg32 *) ChargeOut__PC)
#endif
/* Pin State */
#define ChargeOut_PS                     (* (reg32 *) ChargeOut__PS)
/* Data Register */
#define ChargeOut_DR                     (* (reg32 *) ChargeOut__DR)
/* Input Buffer Disable Override */
#define ChargeOut_INP_DIS                (* (reg32 *) ChargeOut__PC2)

/* Interrupt configuration Registers */
#define ChargeOut_INTCFG                 (* (reg32 *) ChargeOut__INTCFG)
#define ChargeOut_INTSTAT                (* (reg32 *) ChargeOut__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define ChargeOut_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(ChargeOut__SIO)
    #define ChargeOut_SIO_REG            (* (reg32 *) ChargeOut__SIO)
#endif /* (ChargeOut__SIO_CFG) */

/* USBIO registers */
#if !defined(ChargeOut__PC) && (CY_PSOC4_4200L)
    #define ChargeOut_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define ChargeOut_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define ChargeOut_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define ChargeOut_DRIVE_MODE_SHIFT       (0x00u)
#define ChargeOut_DRIVE_MODE_MASK        (0x07u << ChargeOut_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins ChargeOut_H */


/* [] END OF FILE */
