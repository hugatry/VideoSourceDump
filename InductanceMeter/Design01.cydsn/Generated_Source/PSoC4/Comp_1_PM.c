/*******************************************************************************
* File Name: Comp_1_PM.c
* Version 1.20
*
* Description:
*  This file provides the power management source code APIs for the
*  Comparator.
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

#if(!Comp_1_CHECK_DEEPSLEEP_SUPPORT)
    static Comp_1_BACKUP_STRUCT Comp_1_backup =
    {
        0u, /* enableState */
    };
#endif /* (Comp_1_CHECK_DEEPSLEEP_SUPPORT) */


/*******************************************************************************
* Function Name: Comp_1_SaveConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Comp_1_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: Comp_1_RestoreConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None
*
* Return:
*  None
*
********************************************************************************/
void Comp_1_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: Comp_1_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. The Sleep() API 
*  saves the current component state. Call the Comp_Sleep() function before 
*  calling the CySysPmDeepSleep() or the CySysPmHibernate() functions.
*  The "Deep sleep operation" option has an influence on this function
*  implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Comp_1_Sleep(void)
{
#if(!Comp_1_CHECK_DEEPSLEEP_SUPPORT)
    if(Comp_1_CHECK_PWR_MODE_OFF)
    {
        Comp_1_backup.enableState = 1u;
        Comp_1_Stop();
    }
    else /* Component is disabled */
    {
        Comp_1_backup.enableState = 0u;
    }
#endif /* (Comp_1_CHECK_DEEPSLEEP_SUPPORT) */
}


/*******************************************************************************
* Function Name: Comp_1_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when Sleep() 
*  was called. The Wakeup() function will also re-enable the component. 
*  The "Deep sleep operation" option has an influence on this function
*  implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Comp_1_Wakeup(void)
{
#if(!Comp_1_CHECK_DEEPSLEEP_SUPPORT)
    if(0u != Comp_1_backup.enableState)
    {
        /* Enable Comp's operation */
        Comp_1_Enable();
    } /* Do nothing if Comp was disabled before */
#endif /* (Comp_1_CHECK_DEEPSLEEP_SUPPORT) */
}


/* [] END OF FILE */

