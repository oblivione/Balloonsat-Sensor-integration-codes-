/* 
			Watchdog Reset with Interrupt handler implementation for BallonSat
			
			

			REQUIRES <avr/wdt.h> , the watchdogtimer library from AVR
			
			AUTHOR : ISAsense    DATE : 05/07/14

			Resources : https://www.youtube.com/watch?v=BDsu8YhYn8g 

			*****    USAGE *****	
			1) VERY IMP : Initialise using BSwdtEnable at top of initialissation or setup --> enable before any
			
			2) Define the Interrupt Service Routine as ISR(WDT_vect) // we have only one more WDT timeout left before the WDT overrolls again firing the RESET process 
			   so save everything before this or if more time is needed then wdt_reset() must be called inside this ISR

*/




void BSwdtEnable(void)
{
	wdt_reset();		//reset wdt timer before making anychanges to wdt so as to have sufficient 
						//time to config. the settings so that wdt doesn't timeout halfway in the configuration process 

	wdt_enable(WDTO_8S);  // Setting for 8s watchdog timer
	

	cli();   // disable any interrupt to interrupt the process in half its way

	WDTCSR|= (1<<WDCE) ;  // enable Watchdog Change enable bit (WDCE) so as to get acces to make changes to WDTCR's other bits i.e to change the watchdog config
									// we have 4 clock cycles to make changes to WDTCSR from here

	WDTCSR|=(1<<WDIE);		// enable WDT Interrupt bit (WDIE)// 
	
	sei();			// enable interrupts back 
}


char BSwdtResetFlag(void)
	{
		if( MCUSR & (1<<WDRF))
		{
			MCUSR &= ~(1<<WDIF);   // reset WDIF by writting 0 to it //
			return 1;
		}
		else
			return 0;
	}




	
	

	