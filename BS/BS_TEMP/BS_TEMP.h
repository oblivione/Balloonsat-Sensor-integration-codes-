#define ONE_WIRE_BUS 6
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void intializeTemp(){
	sensors.begin();
}

//////////////////////////////////////temperature sensor///////////////////////////////////////
String temperaturesensor(){
  String temp="";
  //Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  //Serial.println("DONE");
  
  //Serial.print("Temperature for the device 1 (index 0) is: ");
  //Serial.println(sensors.getTempCByIndex(0));   
  temp=floattostring(sensors.getTempCByIndex(0));
  //Serial.println(temp);
  return temp;
}

/////////////////////////detect temperatur sensors///////////////////////////
int detecttempsensor(){
   int d=0;
   int f=0;
  //Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  //Serial.println("DONE");
  
  //Serial.print("Temperature for the device 1 (index 0) is: ");
  if(d==int(sensors.getTempCByIndex(0))){
    
   //Serial.println(" temperature sensor not detected");
   f=0;
  }
  else{
   f++;
   //Serial.println("temperature sensor detectted"); 
  }
  
  
  return f;
  
  
  
  
  
}

//////////////////////////////////GetTEMP///////////////////////////////////////
String GetTemperature(){
	
	
	String Temp_start_id="$";
  	String Temp_stop_id="#";
  	String Temp_Value_separator = "=";
  	String Temp_item_separator = ":";
	
	
	String Final_temp = "";
	
	if(detecttempsensor()==1)
		{
			Final_temp = temperaturesensor();
			Final_temp = Temp_start_id + "T" + Temp_Value_separator + Final_temp + Temp_stop_id ;
			return Final_temp;
		}
	
	else
	return ("TEMPERATURE Error");
	
	
}
