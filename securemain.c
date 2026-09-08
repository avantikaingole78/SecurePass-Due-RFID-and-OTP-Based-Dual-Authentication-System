#include<stdio.h>
#include<lpc21xx.h>
#include<string.h>
#include "lcd.h"
#include "rtc.h"
#include "uart_interuppt.h"
#include "gsm.h"
#include "kpm.h"
#include "delay.h"

char vaildtag[]="12538224";
char otp[5];
char enter_otp[5];
int attempts;
void generate_otp(void);
int check_otp(void);
void send_otp(void);
int validate_otp(void);
s32 hour,min,sec;
s32 date,month,year,day;	
s32 otp_time;
s32 now_time;
							 
int main()
{
	IODIR0|=1<<12;
 	InitUART0();
 	InitUART1();
 	InitLCD();
 	RTC_Init();
 	gsm_init();
 	InitKPM();
 	enable_ent1();
    while(1)
    {
		r_flag=0;
		do
		{
	    	GetRTCTimeInfo(&hour,&min,&sec);
        	GetRTCDateInfo(&date,&month,&year);
        	GetRTCDay(&day);
	    	DisplayRTCTime(hour,min,sec);
        	DisplayRTCDate(date,month,year);
        	DisplayRTCDay(day);
		}while(r_flag1!=2); 
	 	CmdLCD(0x01);
	 	StrLCD("RFID TAG:");
	 	CmdLCD(0xc0);
	 	StrLCD(buff1);
	 	delay_ms(2000);
	 	CmdLCD(0x01);
	 	r_flag1=0;
	 	CmdLCD(0x01);
	 	if (strcmp(vaildtag,buff1)==0)
	 	{
	 		CmdLCD(0x01);
	 		StrLCD("valid Tag");
	 		delay_ms(1000);
     		generate_otp();  
	 		send_otp(); 
    		attempts=0;
			while(attempts<3)
			{	
			    int ret=validate_otp(); 
	 			
				if(ret==1)
	 			{
	 				CmdLCD(0x01);
	 				StrLCD("Acess Granted");
	 				delay_ms(1000);
				
					CmdLCD(0x01);
	 				StrLCD("Door open");
	 				IOSET0=1<<12;
	 				delay_s(2);
				
					CmdLCD(0x01);
					StrLCD("Door close"); 
	 				IOCLR0=1<<12;
	 				delay_s(2);

	 				break;
				}
	 			else if(ret==0)
	 			{
					CmdLCD(0x01);
	 	 			StrLCD("OTP EXPIRED");
		 			delay_s(2);
		 			break;
	 			}
	 			else 
	 			{
       				attempts++;

	   				CmdLCD(0x01);
	   				StrLCD("WRONG OTP");
	   				delay_ms(1000);
	   				if(attempts >=3)			   
       				{
	   					CmdLCD(0x01);
						StrLCD("acesses denied");
						delay_ms(2000); 
	 	  			}
				}
	 	 	}
		}
	 	else 
	 	{
	 		CmdLCD(0x01);
	 		StrLCD("Invalid card");
	 		delay_s(1);
	 	}
	 	CmdLCD(0x01);
   	}	                      
}

void generate_otp(void)
{
	otp[0]= ((hour%10)+'0');
	otp[1]= ((min%10)+'0');
	otp[2]= ((sec%10)+'0');
	otp[3]= (((hour+min+sec)%10)+'0');
	otp[4]=  '\0';
}

void send_otp(void)
{
	if(gsm_flag==1)
	{
		UART0_Str("AT+CMGS=\"9307249581\"\r\n");
		delay_ms(1000);
		UART0_Str("YOUR OTP IS:");
		UART0_Str(otp);
		UART0_Str("Valid for 3 mins");
		UART0_Tx(0x1A);
		delay_ms(1000);
	}						   
}

int validate_otp(void)
{
	int i=0;
	int remaining;
	char buf[5];
	u8 key;

	CmdLCD(0x01);
	CmdLCD(0x80);
	StrLCD("ENTER OTP");
	CmdLCD(0xc0);

	GetRTCTimeInfo(&hour,&min,&sec);
	otp_time= (hour*3600)+(min*60)+sec;

	
	while(1)
	{		
		GetRTCTimeInfo(&hour,&min,&sec);
		now_time=(hour*3600)+(min*60)+(sec);

		remaining=180-(now_time-otp_time);			
		if(remaining<=0)
			return 0;
		 sprintf(buf,"%03d",remaining);
		 CmdLCD(0x8D);
		 StrLCD(buf);

		/*while(remaining>=0)
		{
			sprintf(buf,"%03d",remaining);
			CmdLCD(0x8D);
			StrLCD(buf);
		  */
			if(ColScan()==0)
			{
				key=KeyScan();
				
				if(key>=0 && key<=9)
				{
					enter_otp[i]=key+48;
					CmdLCD(0XC0+i);
					CharLCD(key+48);
					i++;
				
				
					if(i==4)
					{
						enter_otp[4]='\0';
	                    if(strcmp(otp,enter_otp)==0)
	                    return 1;
						else
	                    return -1;
					}
				}
}	
    delay_ms(50);
				

}
       
}


/*int check_otp()
{
	GetRTCTimeInfo(&hour,&min,&sec);
	now_time=(hour*3600)+(min*60)+sec;
	if((now_time - otp_time) > 180)
		return 0;
 	return 1;
}*/
