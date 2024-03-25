/*******************************************************************************
* File Name: PulseLengthTimer.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_PulseLengthTimer_H)
#define CY_TIMER_PulseLengthTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 PulseLengthTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define PulseLengthTimer_Resolution                 32u
#define PulseLengthTimer_UsingFixedFunction         0u
#define PulseLengthTimer_UsingHWCaptureCounter      0u
#define PulseLengthTimer_SoftwareCaptureMode        0u
#define PulseLengthTimer_SoftwareTriggerMode        0u
#define PulseLengthTimer_UsingHWEnable              0u
#define PulseLengthTimer_EnableTriggerMode          1u
#define PulseLengthTimer_InterruptOnCaptureCount    1u
#define PulseLengthTimer_RunModeUsed                1u
#define PulseLengthTimer_ControlRegRemoved          0u

#if defined(PulseLengthTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define PulseLengthTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (PulseLengthTimer_UsingFixedFunction)
    #define PulseLengthTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define PulseLengthTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End PulseLengthTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!PulseLengthTimer_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (PulseLengthTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!PulseLengthTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}PulseLengthTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    PulseLengthTimer_Start(void) ;
void    PulseLengthTimer_Stop(void) ;

void    PulseLengthTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   PulseLengthTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define PulseLengthTimer_GetInterruptSource() PulseLengthTimer_ReadStatusRegister()

#if(!PulseLengthTimer_UDB_CONTROL_REG_REMOVED)
    uint8   PulseLengthTimer_ReadControlRegister(void) ;
    void    PulseLengthTimer_WriteControlRegister(uint8 control) ;
#endif /* (!PulseLengthTimer_UDB_CONTROL_REG_REMOVED) */

uint32  PulseLengthTimer_ReadPeriod(void) ;
void    PulseLengthTimer_WritePeriod(uint32 period) ;
uint32  PulseLengthTimer_ReadCounter(void) ;
void    PulseLengthTimer_WriteCounter(uint32 counter) ;
uint32  PulseLengthTimer_ReadCapture(void) ;
void    PulseLengthTimer_SoftwareCapture(void) ;

#if(!PulseLengthTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (PulseLengthTimer_SoftwareCaptureMode)
        void    PulseLengthTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!PulseLengthTimer_UsingFixedFunction) */

    #if (PulseLengthTimer_SoftwareTriggerMode)
        void    PulseLengthTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (PulseLengthTimer_SoftwareTriggerMode) */

    #if (PulseLengthTimer_EnableTriggerMode)
        void    PulseLengthTimer_EnableTrigger(void) ;
        void    PulseLengthTimer_DisableTrigger(void) ;
    #endif /* (PulseLengthTimer_EnableTriggerMode) */


    #if(PulseLengthTimer_InterruptOnCaptureCount)
        void    PulseLengthTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (PulseLengthTimer_InterruptOnCaptureCount) */

    #if (PulseLengthTimer_UsingHWCaptureCounter)
        void    PulseLengthTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   PulseLengthTimer_ReadCaptureCount(void) ;
    #endif /* (PulseLengthTimer_UsingHWCaptureCounter) */

    void PulseLengthTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void PulseLengthTimer_Init(void)          ;
void PulseLengthTimer_Enable(void)        ;
void PulseLengthTimer_SaveConfig(void)    ;
void PulseLengthTimer_RestoreConfig(void) ;
void PulseLengthTimer_Sleep(void)         ;
void PulseLengthTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define PulseLengthTimer__B_TIMER__CM_NONE 0
#define PulseLengthTimer__B_TIMER__CM_RISINGEDGE 1
#define PulseLengthTimer__B_TIMER__CM_FALLINGEDGE 2
#define PulseLengthTimer__B_TIMER__CM_EITHEREDGE 3
#define PulseLengthTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define PulseLengthTimer__B_TIMER__TM_NONE 0x00u
#define PulseLengthTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define PulseLengthTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define PulseLengthTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define PulseLengthTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define PulseLengthTimer_INIT_PERIOD             2399999u
#define PulseLengthTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << PulseLengthTimer_CTRL_CAP_MODE_SHIFT))
#define PulseLengthTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)1u << PulseLengthTimer_CTRL_TRIG_MODE_SHIFT))
#if (PulseLengthTimer_UsingFixedFunction)
    #define PulseLengthTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << PulseLengthTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)1 << PulseLengthTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define PulseLengthTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << PulseLengthTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)1 << PulseLengthTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << PulseLengthTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (PulseLengthTimer_UsingFixedFunction) */
#define PulseLengthTimer_INIT_CAPTURE_COUNT      (2u)
#define PulseLengthTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << PulseLengthTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (PulseLengthTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define PulseLengthTimer_STATUS         (*(reg8 *) PulseLengthTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define PulseLengthTimer_STATUS_MASK    (*(reg8 *) PulseLengthTimer_TimerHW__SR0 )
    #define PulseLengthTimer_CONTROL        (*(reg8 *) PulseLengthTimer_TimerHW__CFG0)
    #define PulseLengthTimer_CONTROL2       (*(reg8 *) PulseLengthTimer_TimerHW__CFG1)
    #define PulseLengthTimer_CONTROL2_PTR   ( (reg8 *) PulseLengthTimer_TimerHW__CFG1)
    #define PulseLengthTimer_RT1            (*(reg8 *) PulseLengthTimer_TimerHW__RT1)
    #define PulseLengthTimer_RT1_PTR        ( (reg8 *) PulseLengthTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define PulseLengthTimer_CONTROL3       (*(reg8 *) PulseLengthTimer_TimerHW__CFG2)
        #define PulseLengthTimer_CONTROL3_PTR   ( (reg8 *) PulseLengthTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define PulseLengthTimer_GLOBAL_ENABLE  (*(reg8 *) PulseLengthTimer_TimerHW__PM_ACT_CFG)
    #define PulseLengthTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) PulseLengthTimer_TimerHW__PM_STBY_CFG)

    #define PulseLengthTimer_CAPTURE_LSB         (* (reg16 *) PulseLengthTimer_TimerHW__CAP0 )
    #define PulseLengthTimer_CAPTURE_LSB_PTR       ((reg16 *) PulseLengthTimer_TimerHW__CAP0 )
    #define PulseLengthTimer_PERIOD_LSB          (* (reg16 *) PulseLengthTimer_TimerHW__PER0 )
    #define PulseLengthTimer_PERIOD_LSB_PTR        ((reg16 *) PulseLengthTimer_TimerHW__PER0 )
    #define PulseLengthTimer_COUNTER_LSB         (* (reg16 *) PulseLengthTimer_TimerHW__CNT_CMP0 )
    #define PulseLengthTimer_COUNTER_LSB_PTR       ((reg16 *) PulseLengthTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define PulseLengthTimer_BLOCK_EN_MASK                     PulseLengthTimer_TimerHW__PM_ACT_MSK
    #define PulseLengthTimer_BLOCK_STBY_EN_MASK                PulseLengthTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define PulseLengthTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define PulseLengthTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define PulseLengthTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define PulseLengthTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define PulseLengthTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define PulseLengthTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << PulseLengthTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define PulseLengthTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define PulseLengthTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << PulseLengthTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define PulseLengthTimer_CTRL_MODE_SHIFT                 0x01u
        #define PulseLengthTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << PulseLengthTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define PulseLengthTimer_CTRL_RCOD_SHIFT        0x02u
        #define PulseLengthTimer_CTRL_ENBL_SHIFT        0x00u
        #define PulseLengthTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define PulseLengthTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << PulseLengthTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define PulseLengthTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << PulseLengthTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define PulseLengthTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << PulseLengthTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define PulseLengthTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << PulseLengthTimer_CTRL_RCOD_SHIFT))
        #define PulseLengthTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << PulseLengthTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define PulseLengthTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define PulseLengthTimer_RT1_MASK                        ((uint8)((uint8)0x03u << PulseLengthTimer_RT1_SHIFT))
    #define PulseLengthTimer_SYNC                            ((uint8)((uint8)0x03u << PulseLengthTimer_RT1_SHIFT))
    #define PulseLengthTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define PulseLengthTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << PulseLengthTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define PulseLengthTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << PulseLengthTimer_SYNCDSI_SHIFT))

    #define PulseLengthTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << PulseLengthTimer_CTRL_MODE_SHIFT))
    #define PulseLengthTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << PulseLengthTimer_CTRL_MODE_SHIFT))
    #define PulseLengthTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << PulseLengthTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define PulseLengthTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define PulseLengthTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define PulseLengthTimer_STATUS_TC_INT_MASK_SHIFT        (PulseLengthTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define PulseLengthTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (PulseLengthTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define PulseLengthTimer_STATUS_TC                       ((uint8)((uint8)0x01u << PulseLengthTimer_STATUS_TC_SHIFT))
    #define PulseLengthTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << PulseLengthTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define PulseLengthTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << PulseLengthTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define PulseLengthTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << PulseLengthTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define PulseLengthTimer_STATUS              (* (reg8 *) PulseLengthTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define PulseLengthTimer_STATUS_MASK         (* (reg8 *) PulseLengthTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define PulseLengthTimer_STATUS_AUX_CTRL     (* (reg8 *) PulseLengthTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define PulseLengthTimer_CONTROL             (* (reg8 *) PulseLengthTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(PulseLengthTimer_Resolution <= 8u) /* 8-bit Timer */
        #define PulseLengthTimer_CAPTURE_LSB         (* (reg8 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define PulseLengthTimer_CAPTURE_LSB_PTR       ((reg8 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define PulseLengthTimer_PERIOD_LSB          (* (reg8 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define PulseLengthTimer_PERIOD_LSB_PTR        ((reg8 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define PulseLengthTimer_COUNTER_LSB         (* (reg8 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define PulseLengthTimer_COUNTER_LSB_PTR       ((reg8 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
    #elif(PulseLengthTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define PulseLengthTimer_CAPTURE_LSB         (* (reg16 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define PulseLengthTimer_CAPTURE_LSB_PTR       ((reg16 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define PulseLengthTimer_PERIOD_LSB          (* (reg16 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define PulseLengthTimer_PERIOD_LSB_PTR        ((reg16 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define PulseLengthTimer_COUNTER_LSB         (* (reg16 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define PulseLengthTimer_COUNTER_LSB_PTR       ((reg16 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define PulseLengthTimer_CAPTURE_LSB         (* (reg16 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define PulseLengthTimer_CAPTURE_LSB_PTR       ((reg16 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define PulseLengthTimer_PERIOD_LSB          (* (reg16 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define PulseLengthTimer_PERIOD_LSB_PTR        ((reg16 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define PulseLengthTimer_COUNTER_LSB         (* (reg16 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
            #define PulseLengthTimer_COUNTER_LSB_PTR       ((reg16 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(PulseLengthTimer_Resolution <= 24u)/* 24-bit Timer */
        #define PulseLengthTimer_CAPTURE_LSB         (* (reg32 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define PulseLengthTimer_CAPTURE_LSB_PTR       ((reg32 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define PulseLengthTimer_PERIOD_LSB          (* (reg32 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define PulseLengthTimer_PERIOD_LSB_PTR        ((reg32 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define PulseLengthTimer_COUNTER_LSB         (* (reg32 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define PulseLengthTimer_COUNTER_LSB_PTR       ((reg32 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define PulseLengthTimer_CAPTURE_LSB         (* (reg32 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define PulseLengthTimer_CAPTURE_LSB_PTR       ((reg32 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define PulseLengthTimer_PERIOD_LSB          (* (reg32 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define PulseLengthTimer_PERIOD_LSB_PTR        ((reg32 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define PulseLengthTimer_COUNTER_LSB         (* (reg32 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define PulseLengthTimer_COUNTER_LSB_PTR       ((reg32 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define PulseLengthTimer_CAPTURE_LSB         (* (reg32 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define PulseLengthTimer_CAPTURE_LSB_PTR       ((reg32 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define PulseLengthTimer_PERIOD_LSB          (* (reg32 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define PulseLengthTimer_PERIOD_LSB_PTR        ((reg32 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define PulseLengthTimer_COUNTER_LSB         (* (reg32 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
            #define PulseLengthTimer_COUNTER_LSB_PTR       ((reg32 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define PulseLengthTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) PulseLengthTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
    
    #if (PulseLengthTimer_UsingHWCaptureCounter)
        #define PulseLengthTimer_CAP_COUNT              (*(reg8 *) PulseLengthTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define PulseLengthTimer_CAP_COUNT_PTR          ( (reg8 *) PulseLengthTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define PulseLengthTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) PulseLengthTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define PulseLengthTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) PulseLengthTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (PulseLengthTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define PulseLengthTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define PulseLengthTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define PulseLengthTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define PulseLengthTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define PulseLengthTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define PulseLengthTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << PulseLengthTimer_CTRL_INTCNT_SHIFT))
    #define PulseLengthTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << PulseLengthTimer_CTRL_TRIG_MODE_SHIFT))
    #define PulseLengthTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << PulseLengthTimer_CTRL_TRIG_EN_SHIFT))
    #define PulseLengthTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << PulseLengthTimer_CTRL_CAP_MODE_SHIFT))
    #define PulseLengthTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << PulseLengthTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define PulseLengthTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define PulseLengthTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define PulseLengthTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define PulseLengthTimer_STATUS_TC_INT_MASK_SHIFT       PulseLengthTimer_STATUS_TC_SHIFT
    #define PulseLengthTimer_STATUS_CAPTURE_INT_MASK_SHIFT  PulseLengthTimer_STATUS_CAPTURE_SHIFT
    #define PulseLengthTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define PulseLengthTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define PulseLengthTimer_STATUS_FIFOFULL_INT_MASK_SHIFT PulseLengthTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define PulseLengthTimer_STATUS_TC                      ((uint8)((uint8)0x01u << PulseLengthTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define PulseLengthTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << PulseLengthTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define PulseLengthTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << PulseLengthTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define PulseLengthTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << PulseLengthTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define PulseLengthTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << PulseLengthTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define PulseLengthTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << PulseLengthTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define PulseLengthTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << PulseLengthTimer_STATUS_FIFOFULL_SHIFT))

    #define PulseLengthTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define PulseLengthTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define PulseLengthTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define PulseLengthTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define PulseLengthTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define PulseLengthTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_PulseLengthTimer_H */


/* [] END OF FILE */
