void BSsendPacket()
{
	//initialisations to prevent memory overflows or prevent unstable behaviours //
  	String PACKET_DATA = "";
	GPS_DATA_RAW = "";
	counts_to_update_GPS_DATA =0;  // every measures has been taken for its initialisation inside getGPSdata() but still incase we missed something then here it gets initialised.


	while(BSSerial.available()){BSSerial.read();}  // empty BSSerial read buffer before getting next data // VIMP 

	//initialisations to prevent memory overflows or prevent unstable behaviours //

  unsigned long  WatchdogWindow = 4000 ;  // watchdog window must be atleast twice the time between two successive GPS signal arrivals so that its usr ethat atleat one complete GPS data is received 
											//   --> think why its twice so as to be sure that atleast one packet lies in this interval?
											// NOTICE we made this an unsigned long too, while unsigned int could have done the work for a watchdog less than
											// about 65 seconds but we dint to avoid any problems which could occur due to type cast by compiler optimisatios

  unsigned long  timeout = millis();		// Very Very Imp to make it a unsigned long and not unsigned ingt else will cause error as millis()
											// is unsigned long and arithmetic operations with other kinds of data may cause compiler to optimise 
											// and typecast the data and hence unpredicted behaviours //
 
  while(!(gps.getGPSdata()) && (millis()-timeout)< WatchdogWindow);
  //BSSerial.println(GPS_DATA);
   

 
 
  	
 	PACKET_DATA = PACKET_DATA  +
                                                                                                              

              	                        

              		                                "[" +


                  		                                 
                                                            "{\"SensorName\":\"GPS_Sensor\", \"SensorData\":\"" +GPS_DATA +  "\"},"  +
                                                             "{\"SensorName\":\"IMU_Sensor1\", \"SensorData\":\"" + GetIMUsensor1() +  "\"},"  +
                                                             "{\"SensorName\":\"IMU_Sensor2\", \"SensorData\":\"" + GetIMUsensor2() +  "\"},"   +
                                                             "{\"SensorName\":\"HUMIDITY_Sensor\", \"SensorData\":\"" + GetHumidity() +  "\"},"   +
                                                             "{\"SensorName\":\"TEMPERATURE_Sensor\", \"SensorData\":\"" + GetTemperature() +  "\"}"  +
                                                      
                                                
              		                                 "]"  + "\r\n" 
														 
													      + GPS_DATA_RAW;

                       
                       
                       
                      



   
	 BSSerial.println(PACKET_DATA);

     BSSerial.flush();		// wait until BSSerial output buffer is empty //  VIMP
}