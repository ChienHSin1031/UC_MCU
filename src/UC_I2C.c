

#include "HT67F5660.h"
#include "UC_I2C.h"

u8 ACK = 0;
static u8 CheckStateSCL = 0;
static u8 CheckStateSDA = 0;

//Init I2C SDA SCL 
void i2c_init(void)
{
	SDAC = 0;	   //SDA Set Output
	SDA = 1; 	   
	SCLC = 0;	   //SCL Set Output
	SCL = 1;     
    GCC_DELAY(3);
}

//Start Signal SCL = 1, SDA HIGH TO DOWN
void i2c_start(void)
{

	
	SDA = 1;    //SDA Set to HIGH
	GCC_DELAY(1);
	SCL = 1;    //SCL Set to High 
	GCC_DELAY(1);
	SDA = 0;    //Set SDA HIGH to LOW  I2C start condition
	GCC_DELAY(1);
}

//Stop Signal SCL = 1, SDA 0 to 1
void i2c_stop(void)  
{
	SCLC = 0;
	SDAC = 0;
	GCC_DELAY(1);
	SCL = 0;
	GCC_DELAY(1);
	SDA = 0;
	GCC_DELAY(1);
	SDA = 1;
	GCC_DELAY(1);
	SCL = 1;
	GCC_DELAY(1);
	
}

u8 i2c_read_ACK(void)
{	
	SDAC  = 1;  //SET TO INPUT
	SDAPU = 1;  //PULL HIGH Enable
	SCL = 1;
	ACK = SDA;
	GCC_DELAY(10);
	SCL = 0;
	GCC_DELAY(10);
	return ACK;
	
}
//bug scl didn't go to low 
void i2c_write(u8 i2c_buffer)
{
	ACK = 1;
	u8 i =8;
	//SCLC = 0;   //SCL Set Output
	//SDAC = 0;	//SDA Set Output
	while(i--)
	{
		SCLC = 1;
		SCL = 0;     //problem here
		CheckStateSCL = SCL;
		GCC_DELAY(5);	
		
		if(i2c_buffer & 0x80) 
			SDA = 1;
		else
			SDA = 0;
		CheckStateSDA = SDA;
		SCL = 1;
		CheckStateSCL = SCL;
		GCC_DELAY(5);
		i2c_buffer = i2c_buffer<<1; 		
	}
	
	SCL = 0;
	GCC_DELAY(5);
	
}