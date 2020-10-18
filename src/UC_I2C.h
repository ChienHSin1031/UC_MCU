#ifndef _UC_I2C_H_
#define _UC_I2C_H_

#include "HT8_Type.h"

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
u8 i2c_read_ACK(void);
void i2c_write(u8 i2c_buffer);
u8 i2c_ACK_check(u8 ctrl_byte);

//HT16K33 Command
#define HT16K33_write 0b11100000  //1
#define HT16K33_Turn_ON_OFF 0x20
#define HT16K33_Turn_ON 0x21


#define HT16K33_Display_OFF 0x80
#define HT16K33_Display_ON 0x81       //1

#define HT16K33_Select_Row_INT 0xA1
#define HT16K33_Set_Row_Output 0xA0

#define HT16K33_Set_duty_16 0xEF

#define HT16K33_RAM 0x00

#define RETERY_TIMES  5;

/***** I2C SCL select PC0 *****/
#define	SCL			_pc0
#define	SCLC		_pcc0
#define	SCLPU		_pcpu0

/***** I2C SDA select PC3 *****/
#define	SDA			_pc3  
#define	SDAC		_pcc3
#define	SDAPU		_pcpu3





#endif