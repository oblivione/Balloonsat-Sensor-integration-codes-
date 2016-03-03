
#define USE_I2C
#ifdef USE_I2C
  // The default constructor uses I2C
  Adafruit_L3GD20 gyro;

#endif
float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
void intializeIMU()
{
  accel.begin();
  mag.begin();
  bmp.begin();
  gyro.begin(gyro.L3DS20_RANGE_250DPS);
  //if (!gyro.begin(gyro.L3DS20_RANGE_500DPS))
  //if (!gyro.begin(gyro.L3DS20_RANGE_2000DPS))
  
    
  }
  
  
  
  int detectimusensors();
  
  //////////////////////////////
  String imu_sensor1="";
  String imu_sensor2="";
  ////////////FINAL IMU//////////////////////////
String IMU(){
	
	
  sensors_event_t accel_event;
  sensors_event_t mag_event;
  sensors_event_t bmp_event;
  sensors_vec_t   orientation;
  
  String Imu_start_id="$";
  String Imu_stop_id="#";
  String Imu_Value_separator = "=";
  String Imu_item_separator = ":";
  
  String imu_final="";
  String accx_fs="";
  String accy_fs="";
  String accz_fs="";
  String magx_fs="";
  String magy_fs="";
  String magz_fs="";
  String roll_fs="";
 
  String pitch_fs="";
 
  String heading_fs="";
  
  String wx_fs="";
  
  String wy_fs="";
  
  String wz_fs="";
  String temp_fs="";
  String alt_fs="";
  String pressure_fs="";
  imu_sensor1="";
  imu_sensor2="";
  /* Read the accelerometer and magnetometer */
  accel.getEvent(&accel_event);
  mag.getEvent(&mag_event);

  /* Use the new fusionGetOrientation function to merge accel/mag data */  
  if (dof.fusionGetOrientation(&accel_event, &mag_event, &orientation))
  {
    /* 'orientation' should have valid .roll and .pitch fields */
   
    
    //PITCH ROLL HEADING
    roll_fs=floattostring(orientation.roll);
    pitch_fs=floattostring(orientation.pitch);
    heading_fs=floattostring(orientation.heading);
    
   accx_fs=floattostring(accel_event.acceleration.x);
   accy_fs=floattostring(accel_event.acceleration.y);
   accz_fs=floattostring(accel_event.acceleration.z);
    
    magx_fs=floattostring(mag_event.magnetic.x);
    magy_fs=floattostring(mag_event.magnetic.y);
    magz_fs=floattostring(mag_event.magnetic.z);
  }

  
  //GYRO READINGS
  gyro.read();
  wx_fs=floattostring(gyro.data.x);
  wy_fs=floattostring(gyro.data.y);
  wz_fs=floattostring(gyro.data.z);
  
 
  //GRYOREDAINGS END  
  
  
  
  
  
  /* Calculate the altitude using the barometric pressure sensor */
  //PRESSURE TEMPERATURE ALTITUDE
  bmp.getEvent(&bmp_event);
  if (bmp_event.pressure)
  {
    /* Get ambient temperature in C */
    float temperature;
    float alt;
    float pressure_f;
    
    
    bmp.getTemperature(&temperature);
    /* Convert atmospheric pressure, SLP and temp to altitude */
    
   
                                        
    alt=bmp.pressureToAltitude(seaLevelPressure,bmp_event.pressure,temperature) ;
    pressure_f=bmp_event.pressure;
    temp_fs=floattostring(temperature);
    alt_fs=floattostring(alt);
    pressure_fs=floattostring(pressure_f);
    
  }
  
  
  
 imu_final= Imu_start_id+
 			"R"+Imu_Value_separator+roll_fs+Imu_item_separator+
 		    "P"+Imu_Value_separator+pitch_fs+Imu_item_separator+
			"H"+Imu_Value_separator+heading_fs+Imu_item_separator+
			"X"+Imu_Value_separator+wx_fs+Imu_item_separator+
			"Y"+Imu_Value_separator+ wy_fs+Imu_item_separator+
			"Z"+Imu_Value_separator+wz_fs+Imu_item_separator+
			"T"+Imu_Value_separator+temp_fs+Imu_item_separator+
			"A"+Imu_Value_separator+alt_fs+Imu_item_separator+
			"P"+Imu_Value_separator+pressure_fs+Imu_item_separator+
			"M"+Imu_Value_separator+accx_fs+Imu_item_separator+
			"N"+Imu_Value_separator+accy_fs+Imu_item_separator+
			//
			"O"+Imu_Value_separator+accz_fs+Imu_item_separator+
			"Q"+Imu_Value_separator+magx_fs+Imu_item_separator+
			"S"+Imu_Value_separator+ magy_fs+Imu_item_separator+
			"U"+Imu_Value_separator+ magz_fs+
		    	Imu_stop_id;
		    	
 //Serial.println(imu_final);
  imu_sensor1=Imu_start_id+
 			"R"+Imu_Value_separator+roll_fs+Imu_item_separator+
 		    "P"+Imu_Value_separator+pitch_fs+Imu_item_separator+
			"H"+Imu_Value_separator+heading_fs+Imu_item_separator+
			"X"+Imu_Value_separator+wx_fs+Imu_item_separator+
			"Y"+Imu_Value_separator+ wy_fs+Imu_item_separator+
			"Z"+Imu_Value_separator+wz_fs+Imu_item_separator+
			"T"+Imu_Value_separator+temp_fs+Imu_item_separator+
			"A"+Imu_Value_separator+alt_fs+Imu_item_separator+
			"PR"+Imu_Value_separator+pressure_fs+Imu_item_separator+
			"M"+Imu_Value_separator+accx_fs+Imu_item_separator+
			"N"+Imu_Value_separator+accy_fs+Imu_stop_id;
 imu_sensor2=Imu_start_id+
            "O"+Imu_Value_separator+accz_fs+Imu_item_separator+
			"Q"+Imu_Value_separator+magx_fs+Imu_item_separator+
			"S"+Imu_Value_separator+ magy_fs+Imu_item_separator+
			"U"+Imu_Value_separator+ magz_fs+
		    	Imu_stop_id;;
  return imu_final;
  delay(100);
  


}
////////////////////////////END FINAL IMU/////////////////////////////////////////////////////////////
///////////////////////////Detect IMU Senosrs/////////////////////////////////

int detectimusensors(){
	int d=0;
   Wire.begin();
  for (byte i = 1; i < 120; i++)
  {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
      {
     
      if(i==25){
       // Serial.println("ACC found");
        d++;
  
      }
      if(i==30){
       // Serial.println("gryo found");
        d++;
        
      } if(i==107){
        //Serial.println("magnet found");
        d++;
        
      } if(i==119){
        //Serial.println("pressure found");
        d++;
        
      } 
      // end of good response
     delay (5);  // give devices time to recover
  } // end of for loop
  }
  return d;
}

String GetIMU()
{
	if(detectimusensors()==4)
	return IMU();
	else
	return ("IMU Error");
}

String GetIMUsensor1(){
	
	if(detectimusensors()==4)
	{
		IMU();
		return imu_sensor1;
	}
	else
	return ("IMU Error");
}
String GetIMUsensor2(){

	if(detectimusensors()==4)
	{
		IMU();
		return imu_sensor2;
	}
	else
	return ("IMU Error");
}

