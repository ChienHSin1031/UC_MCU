#include "HT67F5660.h"

#include "UC_I2C.h"
#include "HT8_TimeBase.h"



void UC_HT16K33();
void UC_Watchdog(bool Watchdog);
void init_HT16K33();
void HT16K33_LED_RAM_Clear();
void show();
void LED_all_TURN_ON();
void LED_COM5_TUR_ON();
void Number9to0();
void displayON();
void displayOFF();
u16 Display_Number(int i);

static u16 display_Buffer[8];

u8 CheckAddressCnt = RETERY_TIMES;
static const u16 numbertable[] = {
	0x3F00, /* 0 */
	0x0600, /* 1 */
	0x5B00, /* 2 */
	0x4F00, /* 3 */
	0x6600, /* 4 */
	0x6D00, /* 5 */
	0x7C00, /* 6 */
	0x0700, /* 7 */
	0x7F00, /* 8 */
	0x6700, /* 9 */
};

void main()
{	
	UC_Watchdog(0);
	//System_Clock_Init();
	//TimeBase_Init();
	TB_DISABLE();
	UC_HT16K33();

	int i = 0, COM0, COM1, COM2, COM3, COM4;
	while(1)
	{
		displayOFF();
		COM0 = i/10000;
		display_Buffer[0] = Display_Number(COM0);
		COM1 = (i/1000)%10;
		display_Buffer[1] = Display_Number(COM1);
		COM2 = (i/100)%10;
		display_Buffer[2] = Display_Number(COM2);
		COM3 = (i/10)%10;
		display_Buffer[3] = Display_Number(COM3);
		COM4 = i%10;
		display_Buffer[4] = Display_Number(COM4);
		i = i+1;
		if(i==99999) i = 0;
		show();
		displayON();
		GCC_DELAY(100000);
		//GCC_DELAY(263690);
	}
	
}

u16 Display_Number(int i)
{
	switch(i)
	{
		case 0:
			return numbertable[0];
		case 1:
			return numbertable[1];
		case 2:
			return numbertable[2];
		case 3:
			return numbertable[3];
		case 4:
			return numbertable[4];
		case 5:
			return numbertable[5];
		case 6:
			return numbertable[6];
		case 7:
			return numbertable[7];
		case 8:
			return numbertable[8];
		case 9:
			return numbertable[9];
		
	}
	
}

void UC_HT16K33()
{

	init_HT16K33();
	GCC_DELAY(3);
	HT16K33_LED_RAM_Clear();
	LED_all_TURN_ON();
	//Number9to0();
	//LED_COM5_TUR_ON();
	//blank();
}

void LED_all_TURN_ON()
{
	display_Buffer[0] = 0x7F01;
	display_Buffer[1] = 0x7F01;
	display_Buffer[2] = 0x7F01;
	display_Buffer[3] = 0x7F01;
	display_Buffer[4] = 0x7F01;
	display_Buffer[5] = 0xFF01;
	show();
	

}

void Number9to0()   //≈„•‹≠Àº∆ 9 to 0
{
	int i;
	for(i=0;i<10;i++)
	{
		int j;
		for(j=0;j<5;j++)
		{
			display_Buffer[j] = numbertable[i];	
		}
		show();	
		GCC_DELAY(263690);
	}
	
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
			
			i2c_write(HT16K33_Select_Row_INT);
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

void displayON()
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

void displayOFF()
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
			
			i2c_write(HT16K33_Display_OFF);
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