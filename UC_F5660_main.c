#include "HT67F5660.h"

#include "UC_I2C.h"
#include "HT8_TimeBase.h"


void UC_HT16K33();
void UC_Watchdog(bool Watchdog);
void init_HT16K33();
void HT16K33_LED_ON();


void main()
{	

	UC_Watchdog(0);
	
	TimeBase_Init();
	//TB_ENABLE();
	
	UC_HT16K33();
	
}


void UC_HT16K33()
{
	init_HT16K33();
	GCC_DELAY(20);
	//HT16K33_LED_ON();
}


void init_HT16K33(void)
{
	i2c_init();
	
	//Turn ON Display
	i2c_start();
	i2c_write(HT16K33_write);    //Tx 16k33 address
	if(i2c_read_ACK() == 0) 
	{
		
		i2c_write(HT16K33_Display_ON);
		if(i2c_read_ACK() == 0)
		{
			i2c_stop();
		}
			
	}
	//SET to ROW output
	i2c_start();
	i2c_write(HT16K33_write);
	if(i2c_read_ACK() == 0)
	{
		i2c_write(HT16K33_Set_Row_Output);
		if(i2c_read_ACK() == 0)
		{
			i2c_stop();
		}
	}
	
	i2c_start();
	i2c_write(HT16K33_write);
	if(i2c_read_ACK() == 0)
	{	
		i2c_write(HT16K33_Set_duty_16);
		if(i2c_read_ACK() == 0)
		{
			i2c_stop();
		}		
	}
	
	
	i2c_start();
	i2c_write(HT16K33_write);
	if(i2c_read_ACK() == 0)
	{
			i2c_write(HT16K33_Display_OFF);
			if(i2c_read_ACK() == 0)
			{
				i2c_stop();
			}	
	}
	
	i2c_start();
	i2c_write(HT16K33_write);
	if(i2c_read_ACK() == 0)
	{
		i2c_write(HT16K33_RAM);
		if(i2c_read_ACK() == 0)
		{
			int i =0;
			for(i=0;i<12;i++)
			{
				if(i2c_read_ACK() == 1)
				{
					GCC_DELAY(100);
				}
				else
				{
					i2c_write(0xFF);
				}
			} 
			i2c_stop();
				
		}
		
	}
	
	i2c_start();
	i2c_write(HT16K33_write);
	if(i2c_read_ACK() == 0)
	{
			i2c_write(HT16K33_Display_ON);
			if(i2c_read_ACK() == 0)
			{
				i2c_stop();
			}	
	}
	
}

				
			
				

void HT16K33_LED_ON()
{

	i2c_start();
	i2c_write(HT16K33_write);
	if(i2c_read_ACK() == 0)
	{
		i2c_write(0x00);
		if(i2c_read_ACK() == 0)
		{
			u8 i;
			for(i=0;i<6;i++)
			{
				i2c_write(0xFF);
				if(i2c_read_ACK() == 0)
				{
					i2c_write(0x03);
				}	
			}
		}
			
	}
	
	i2c_start();
	i2c_write(HT16K33_write);
	if(i2c_read_ACK() == 0) 
	{
		i2c_write(HT16K33_Display_ON_OFF);
		if(i2c_read_ACK() == 0)
		{
			i2c_write(HT16K33_Display_ON);
			if(i2c_read_ACK() == 0)
			{
				i2c_stop();
			}
		}
		
	}
	
	
}

void UC_Watchdog(bool Watchdog)
{   // 1:enable  0:disable 
	
	if(Watchdog == TRUE){  //enable 
		_we4 = 0;
		_we3 = 1;
		_we2 = 0;
		_we1 = 1;
		_we0 = 0;
		
		// ws: WDT time-out period selection 
		_ws2 = 0;
		_ws1 = 0;
		_ws0 = 0;
		return ;
		
	}else{
		
		_wdtc = 0b10101000;  //disable Watchdog 
		return ;
	}
	
}