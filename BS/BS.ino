#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20.h>
#include <Adafruit_10DOF.h>
#include <dht.h>
#include <OneWire.h>
#include <DallasTemperature.h>


Adafruit_10DOF                dof   = Adafruit_10DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30306);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified       bmp   = Adafruit_BMP085_Unified(18000);


#include <BS_CUSTOM.h>
#include <BS_IMU.h>
#include <BS_HUMIDITY.h>
#include <BS_TEMP.h>


//  DEBUG MODE SETTINGS (DEBUG_MODE=1 for debugging and 0 for main application) //

#define DEBUG_MODE 0

#if DEBUG_MODE
#define BSSerial Serial
#else 
#define BSSerial Serial1
#endif

//  DEBUG MODE SETTINGS  //


#include <nmea.h>
#include <BS_GPS.h>
GPS gps;

#include <BS_PACKET.h>


#include<avr/wdt.h>
#include<BS_WDT.h>



#include<EEPROM.h>  
#define WDT_ERROR_ADDRESS 500  



void setup(){

    BSwdtEnable();  // INITIALISE WDT Timer //
   
   
    wdt_reset();    // reseting wdt clock so tht it doesn't overflow before Initialisations get completed below //
    
    // ************   I N I T I A L I Z A T I O N S   ************* //
    
    BSSerial.begin(9600);
    
    
    if(EEPROM.read(WDT_ERROR_ADDRESS)==0)
    {
      EEPROM.write(WDT_ERROR_ADDRESS,1);
      BSSerial.println("ERROR!.......WDT RESTART SUCCESSFUL");
    }
    
    
  
    
    intializeIMU();
    
    // ************   I N I T I A L I Z A T I O N S   ************* //
    
   
 //pinMode(1,OUTPUT);
 //initializeGPS();
 //detecthumidsensor();   
 //detecttempsensor();
 //detectimusensors();
 
   BSSerial.println("Initialisations successful ---> Starting...");
  
}




void loop()
{
   
        wdt_reset();    // reseting wdt clock so tht it doesn't overflow 
 
  
    //BSSerial.println(gps_final());
    //BSSerial.println("hello");
    //BSSerial.println(GetHumidity());
    //BSSerial.println(GetIMU());
    //BSSerial.println(GetTemperature());
      BSsendPacket();

    

}


ISR(WDT_vect)
{
  EEPROM.write(WDT_ERROR_ADDRESS,0);
  while(1); // wait for another WDT overflow for system restart //
}
