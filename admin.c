#include <stdlib.h>
#include "lcd_defines.h"
#include "lcd.h"
#include "kpm.h"
#include "rtc.h"
#include "delay.h"
#include "admin.h"
void rtc_edit()
{
	u8 key1;
    s8 hour;
	u8 minute;
	u8 second;
	u8 date;
	u8 month;
	u32 year;
	u8 week;
 
  	while(1)
    {
		CmdLCD(CLEAR_LCD);
        CmdLCD(GOTO_LINE1_POS0);
        StrLCD("1.H 2.MI 3.S 4.D");
        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("5.M 6.YR 7.W 8.E");
 		key1 = KeyScan();
        switch(key1)
        {
            case 1:   // set hour
                CmdLCD(CLEAR_LCD);
                StrLCD("Enter Hour(0-23)");
                hour = ReadNumber(23); 
				CharLCD(hour);  
				if(hour>=0 && hour<23)      // display hour
                sethour(hour);      // update RTC
                break;

            case 2:   // minute edit placeholder
                CmdLCD(CLEAR_LCD);
                StrLCD("MIN EDIT (0-59)");
				minute = ReadNumber(59);
                setminute(minute);	// display hour 
                break;

            case 3:   // second edit placeholder
                CmdLCD(CLEAR_LCD);
                StrLCD("SEC EDIT(0-59)");
				second= ReadNumber(59);
				setsecond(second);
                delay_ms(1000);
                break;
				
			case 4:   // date edit placeholder
                CmdLCD(CLEAR_LCD);
                StrLCD("DATE EDIT(0-31)");
				date = ReadNumber(31);
				setdate(date);
                delay_ms(1000);
                break;
			case 5:   // second edit placeholder
                CmdLCD(CLEAR_LCD);
                StrLCD("MONTH EDIT(0-12)");
				month = ReadNumber(12);
				setmonth(month);
                delay_ms(1000);
                break;
			case 6:   // second edit placeholder
                CmdLCD(CLEAR_LCD);
                StrLCD("YEAR EDIT");
				year = Read4Number(4095);
				setyear(year);
                delay_ms(1000);
                break;
				
			case 7:   // second edit placeholder
                CmdLCD(CLEAR_LCD);
                StrLCD("WEEK EDIT(0-6)");
				week = ReadNumber(6);
				SetRTCDay(week);
                delay_ms(1000);
                break;

            case 8:  // exit RTC menu
                CmdLCD(CLEAR_LCD);
				return;
								
			default : StrLCD("INVALID CHOICE");								
        }
    }
}

void adminmode()
{
	u8 key;

    while(1)
    {
    	CmdLCD(CLEAR_LCD);
    	CmdLCD(GOTO_LINE1_POS0);
    	StrLCD("1.RTC 2.EXIT");
    	// CmdLCD(GOTO_LINE2_POS0);
    	//StrLCD("3.EXIT");
		delay_ms(100);  
		key = KeyScan();
		
		switch(key)
    	{
			case 1:
    	         CmdLCD(CLEAR_LCD);
    	         StrLCD("RTC EDIT");
    	         delay_ms(200);
    	         rtc_edit();
    	         break;
    	        
			case 2:
    	         CmdLCD(CLEAR_LCD);
    	         delay_ms(200);
    	         return;
   	    }
  	}
}
