#include "HT67F5660.h"

#include "UC_I2C.h"
#include "HT8_TimeBase.h"


void UC_HT16K33();
void UC_Watchdog(bool Watchdog);
void init_HT16K33();
void HT16K33_LED_RAM_Clear();
void show();
void blank();
void LED_all_TURN_ON();
void LED_COM5_TUR_ON();
static u16  display_Buffer[8];

u8 CheckAddressCnt = RETERY_TIMES;

void main()
{	
	System_Clock_Init();
	UC_Watchdog(0);
	//TimeBase_Init();
	TB_DISABLE();
	UC_HT16K33();
	
}

void UC_HT16K33()
{

	init_HT16K33();
	GCC_DELAY(3);
	HT16K33_LED_RAM_Clear();
	LED_all_TURN_ON();
	LED_COM5_TUR_ON();
	blank();
}

void LED_all_TURN_ON()
{
	display_Buffer[0] = 0xEF01;
	display_Buffer[1] = 0xEF01;
	display_Buffer[2] = 0xEF01;
	display_Buffer[3] = 0xEF01;
	display_Buffer[4] = 0xEF01;
	display_Buffer[5] = 0xFF01;
	
	//show();
	//blank();
}

void LED_COM5_TUR_ON()
{
	CheckAddressCnt = RETERY_TIMES;
	while(CheckAddressCnt > 0)
	{	
		i2c_start();
		i2c_write(HT16K33_write);    //Tx 16k33 address
		if(i2c_read_ACK() == 0) 
		{
			i2c_write(0x0A);
			if(i2c_read_ACK() == 0)
			{			
				i2c_write(display_Buffer[5] >> 8);
				if(i2c_read_ACK() == 0)
				{
					i2c_write(display_Buffer[5] & 0xFF);
					if(i2c_read_ACK() == 0)
					{
			
						i2c_stop();
						return;	
						
					}else{
						i2c_stop();
						GCC_DELAY(10);
						CheckAddressCnt--;
						break;
					}
					
				}else{
					i2c_stop();
					GCC_DELAY(10);
					CheckAddressCnt--;
					break;
				}
			}else{
				i2c_stop();
				GCC_DELAY(10);
				CheckAddressCnt--;
				continue;
			}
						
		}else{
			i2c_stop();
			GCC_DELAY(10);
			CheckAddressCnt--;
			continue;
		}
		
	}
	
}


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
					break;   //return bug
				}else{
					CheckAddressCnt--;
					i2c_stop();
					GCC_DELAY(10);
					continue;
				}				
		}else{
			i2c_stop();
			GCC_DELAY(10);
			CheckAddressCnt--;
			continue;
		}
	}
	GCC_DELAY(10);
	
	CheckAddressCnt = RETERY_TIMES;
	//SET to ROW output 0xA1
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
				CheckAddressCnt--;
				continue;
			}
				
		}else{
			i2c_stop();
			GCC_DELAY(10);
			CheckAddressCnt--;
			continue;
		}
		
	}
	GCC_DELAY(10);
	
	
	CheckAddressCnt = RETERY_TIMES;
	//SET to HT16K33_Set_duty_16t 0xEF
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
				CheckAddressCnt--;
				continue;
			}
				
		}else{
			i2c_stop();
			GCC_DELAY(10);
			CheckAddressCnt--;
			continue;
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
				CheckAddressCnt--;
				continue;
			}
				
		}else{
			i2c_stop();
			GCC_DELAY(10);
			CheckAddressCnt--;
			continue;
		}
		
	}
	GCC_DELAY(10);		
			
}
	
void HT16K33_LED_RAM_Clear()//HT16K33 init RAM all set to 0
{	
	int i;
	for(i=0 ; i<8 ; i++)
	{
		display_Buffer[i] = 0;	
	}
	
	show();
	
	
}

void show()  //Tx HT16K33 COM0 to COM7 Data
{
	CheckAddressCnt = RETERY_TIMES;
	while(CheckAddressCnt > 0)
	{
		
		i2c_start();
		i2c_write(HT16K33_write);    //Tx 16k33 address
		if(i2c_read_ACK() == 0) 
		{
			i2c_write(0x00);
			if(i2c_read_ACK() == 0)
			{
				int i;
				for(i=0; i<8 ; i++)
				{
					i2c_write(display_Buffer[i] >> 8);
					if(i2c_read_ACK() == 0)
					{
						i2c_write(display_Buffer[i] & 0xFF);
						if(i2c_read_ACK() == 0)
						{
							if(i == 7)     
							{
								i2c_stop();
								return;	
							}
							continue;
												
						}else{
							i2c_stop();
							GCC_DELAY(10);
							CheckAddressCnt--;
							break;
						}
						
					}else{
						i2c_stop();
						GCC_DELAY(10);
						CheckAddressCnt--;
						break;
					}
				
				}
			}else{
				i2c_stop();
				GCC_DELAY(10);
				CheckAddressCnt--;
				continue;
			}
						
		}else{
			i2c_stop();
			GCC_DELAY(10);
			CheckAddressCnt--;
			continue;
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
				i2c_stop();
				break;
			}else{
				i2c_stop();
				GCC_DELAY(10);
				CheckAddressCnt--;
				continue;
			}
				
		}else{
			i2c_stop();
			GCC_DELAY(10);
			CheckAddressCnt--;
			continue;
		}
		
	}
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