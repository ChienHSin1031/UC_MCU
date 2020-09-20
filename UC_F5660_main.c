#include "HT67F5660.h"

#include "UC_I2C.h"
#include "HT8_TimeBase.h"


void UC_HT16K33();
void UC_Watchdog(bool Watchdog);
void init_HT16K33();
void HT16K33_LED_ON();
void clear();
void show();
void blank();

u16  display_Buffer[8];
u8 CheckAddressCnt = RETERY_TIMES;

void main()
{	
	
	UC_Watchdog(0);
	
	TimeBase_Init();
	TB_fsub();
	TB_ENABLE();
	UC_HT16K33();
	
	while(1)
	{
		HT16K33_LED_ON();		
	}
	
	
}


void UC_HT16K33()
{
	init_HT16K33();
	GCC_DELAY(20);
}

//
void init_HT16K33(void)
{
	i2c_init();
	u8 CheckAddressCnt = RETERY_TIMES;
	
	//Turn ON Display 0x21
	while(CheckAddressCnt > 0)
	{
		//Turn ON Display
		i2c_start();
		i2c_write(HT16K33_write);    //Tx 16k33 address
		if(i2c_read_ACK() == 0) 
		{
			
			i2c_write(HT16K33_Turn_ON);
			if(i2c_read_ACK() == 0)
				{
					i2c_stop();
					break;
				}else{
					i2c_stop();
					GCC_DELAY(10);
					return;
				}				
		}else{
			i2c_stop();
			GCC_DELAY(10);
			CheckAddressCnt--;
		}
	}
	GCC_DELAY(10);
	
	
	CheckAddressCnt = RETERY_TIMES;
	//SET to ROW output 0xA0
	while(CheckAddressCnt > 0)
	{
		//SET to ROW output
		i2c_start();
		i2c_write(HT16K33_write);    //Tx 16k33 address
		if(i2c_read_ACK() == 0) 
		{
			
			i2c_write(HT16K33_Set_duty_16);
			if(i2c_read_ACK() == 0)
			{
				i2c_stop();
				break;
			}else{
				i2c_stop();
				GCC_DELAY(10);
				return;
			}
				
		}else{
			i2c_stop();
			GCC_DELAY(10);
			CheckAddressCnt--;
		}
		
	}
	GCC_DELAY(10);
	
	CheckAddressCnt = RETERY_TIMES;
	//SET to ROW output 0xA0
	while(CheckAddressCnt > 0)
	{
		//SET to ROW output
		i2c_start();
		i2c_write(HT16K33_write);    //Tx 16k33 address
		if(i2c_read_ACK() == 0) 
		{
			
			i2c_write(HT16K33_Set_Row_Output);
			if(i2c_read_ACK() == 0)
			{
				i2c_stop();
				break;
			}else{
				i2c_stop();
				GCC_DELAY(10);
				return;
			}
				
		}else{
			i2c_stop();
			GCC_DELAY(10);
			CheckAddressCnt--;
		}
		
	}
	GCC_DELAY(10);
	
	
	CheckAddressCnt = RETERY_TIMES;
	//Display ON 0x81
	while(CheckAddressCnt > 0)
	{
		//SET to ROW output
		i2c_start();
		i2c_write(HT16K33_write);    //Tx 16k33 address
		if(i2c_read_ACK() == 0) 
		{
			
			i2c_write(HT16K33_Display_ON);
			if(i2c_read_ACK() == 0)
			{
				i2c_stop();
				break;
			}else{
				i2c_stop();
				GCC_DELAY(10);
				return;
			}
				
		}else{
			i2c_stop();
			GCC_DELAY(10);
			CheckAddressCnt--;
		}
		
	}
	GCC_DELAY(10);		
			
}
	

				
			
				

void HT16K33_LED_ON()
{	
	int i=0;
	for(i=0;i<8;i++)
	{
		int k=0;
		for(k=0 ; k<16; k++)
		{
			display_Buffer[i] = 1 << k;	
			show();
			GCC_DELAY(10);
		}		
		clear();
	}
	
	i = 0;
	for(i=0; i<8;i++)
	{
		int k=0;
		for(k=0 ; k<16 ; k++)
		{
			display_Buffer[i] |= 1 << k;
			show();
			GCC_DELAY(10);	
		}
	}
	
	blank();
}


void clear()
{
	int i;
	for(i=0 ; i<8 ; i++)
	{
		display_Buffer[i] = 0;	
	} 	
	
}


//show break error
void show()
{
	CheckAddressCnt = RETERY_TIMES;
	//Display OFF 0x81
	while(CheckAddressCnt > 0)
	{
		//SET to ROW output
		i2c_start();
		i2c_write(HT16K33_write);    //Tx 16k33 address
		if(i2c_read_ACK() == 0) 
		{
			int i;
			for(i=0; i<8 ; i++)
			{
				i2c_write(display_Buffer[i] & 0xFF);
				if(i2c_read_ACK() == 0)
				{
					i2c_write(display_Buffer[i] >> 8);
					if(i2c_read_ACK() == 0)
					{
						i2c_stop();
						return;						
					}else{
						i2c_stop();
						GCC_DELAY(10);
						return;
					}
					
				}else{
					i2c_stop();
					GCC_DELAY(10);
					return;
				}
			
			}		
		}else{
			i2c_stop();
			GCC_DELAY(10);
			CheckAddressCnt--;
		}
		
	}
	GCC_DELAY(10);
}
	
	
void blank()
{
	CheckAddressCnt = RETERY_TIMES;
	//Display ON 0x81
	while(CheckAddressCnt > 0)
	{
		//SET to ROW output
		i2c_start();
		i2c_write(HT16K33_write);    //Tx 16k33 address
		if(i2c_read_ACK() == 0) 
		{
			
			i2c_write(HT16K33_Display_ON);
			if(i2c_read_ACK() == 0)
			{
				break;
			}else{
				i2c_stop();
				GCC_DELAY(10);
				return;
			}
				
		}else{
			i2c_stop();
			GCC_DELAY(10);
			CheckAddressCnt--;
		}
		
	}
	i2c_stop();
	GCC_DELAY(10);
	
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