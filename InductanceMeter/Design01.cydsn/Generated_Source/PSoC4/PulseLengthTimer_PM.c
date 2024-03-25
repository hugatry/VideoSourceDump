/*******************************************************************************
* File Name: PulseLengthTimer_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "PulseLengthTimer.h"

static PulseLengthTimer_backupStruct PulseLengthTimer_backup;


/*******************************************************************************
* Function Name: PulseLengthTimer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  PulseLengthTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PulseLengthTimer_SaveConfig(void) 
{
    #if (!PulseLengthTimer_UsingFixedFunction)
        PulseLengthTimer_backup.TimerUdb = PulseLengthTimer_ReadCounter();
        PulseLengthTimer_backup.InterruptMaskValue = PulseLengthTimer_STATUS_MASK;
        #if (PulseLengthTimer_UsingHWCaptureCounter)
            PulseLengthTimer_backup.TimerCaptureCounter = PulseLengthTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!PulseLengthTimer_UDB_CONTROL_REG_REMOVED)
            PulseLengthTimer_backup.TimerControlRegister = PulseLengthTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: PulseLengthTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  PulseLengthTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PulseLengthTimer_RestoreConfig(void) 
{   
    #if (!PulseLengthTimer_UsingFixedFunction)

        PulseLengthTimer_WriteCounter(PulseLengthTimer_backup.TimerUdb);
        PulseLengthTimer_STATUS_MASK =PulseLengthTimer_backup.InterruptMaskValue;
        #if (PulseLengthTimer_UsingHWCaptureCounter)
            PulseLengthTimer_SetCaptureCount(PulseLengthTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!PulseLengthTimer_UDB_CONTROL_REG_REMOVED)
            PulseLengthTimer_WriteControlRegister(PulseLengthTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: PulseLengthTimer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  PulseLengthTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void PulseLengthTimer_Sleep(void) 
{
    #if(!PulseLengthTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(PulseLengthTimer_CTRL_ENABLE == (PulseLengthTimer_CONTROL & PulseLengthTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            PulseLengthTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            PulseLengthTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    PulseLengthTimer_Stop();
    PulseLengthTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: PulseLengthTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  PulseLengthTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PulseLengthTimer_Wakeup(void) 
{
    PulseLengthTimer_RestoreConfig();
    #if(!PulseLengthTimer_UDB_CONTROL_REG_REMOVED)
        if(PulseLengthTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                PulseLengthTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
