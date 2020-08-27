/**
  ******************************************************************************
  * @file HT8_it.c
  * @brief This file provides all the interrupt firmware functions.
  * @author Holtek Semiconductor Inc.
  * @version V1.0.0
  * @date 2019-05-27
  ******************************************************************************
  * @attention
  *
  * Firmware Disclaimer Information
  *
  * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
  *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
  *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
  *    other intellectual property laws.
  *
  * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
  *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
  *    other than HOLTEK and the customer.
  *
  * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
  *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
  *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
  *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
  *
  * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
  ************************************************************************************************************/


#include "HT8_it.h"

/**
  * @brief external Interruption 0 routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x04))) INT0_ISR(void)
{
	/* user define */
}

/**
  * @brief external Interruption 1 routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x08))) INT1_ISR(void)
{
	/* user define */
}

/**
  * @brief timer0 Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x0c))) Timer0_ISR(void)
{
	/* user define */
}

/**
  * @brief ADC Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x10))) ADC_ISR(void)
{
	/* user define */
}

/**
  * @brief timebase0 Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x14))) TB0_ISR(void)
{
	/* user define */
}


/**
  * @brief timebase1 Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x18))) TB1_ISR(void)
{
	/* user define */
}


/**
  * @brief LVD, EEPROM, UART and SIM Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x1c))) LVD_EEPROM_UART_SIM_ISR(void)
{
	/* user define */
}


/**
  * @brief I2CTO or timer1 Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x20))) I2CTO_Timer1_ISR(void)
{
	/* user define */
}


/**
  * @brief timer2 or timer3 Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x24))) Timer2_Timer3_ISR(void)
{
	/* user define */
}


/**
  * @brief compare0 Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x28))) COMP0_ISR(void)
{
	/* user define */
}


/**
  * @brief compare1 Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x2c))) COMP1_ISR(void)
{
	/* user define */
}


/**
  * @brief external Interruption 2 routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x30))) INT2_ISR(void)
{
	/* user define */
}


/**
  * @brief external Interruption 3 routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x34))) INT3_ISR(void)
{
	/* user define */
}


/******************* (C) COPYRIGHT 2019 Holtek Semiconductor Inc *****END OF FILE****/