dht DHT;
#define DHT11_PIN 5

String putdata(float a,float e);
String humidity_final="";

void humidity()
{
	     
	
	

int chk = DHT.read11(DHT11_PIN);
  if(chk==DHTLIB_OK){
       // Serial.print(DHT.humidity);
       // Serial.print(",\t");
	   // Serial.print(DHT.temperature);
	  humidity_final=putdata(DHT.humidity,DHT.temperature);
	  //Serial.println(putdata(DHT.humidity,DHT.temperature));
	//	Serial.println();
	    
  }
  else{
  	humidity_final="HUMIDITY error";
  }
 
  // DISPLAY DATA
  
  delay(500);
  
}
//////////////////////////////////Detect Humidity Sensor//////////////////////////////////
//////////////////////////putdata()///////////////////////////////////////////////////////
String putdata(float a,float e){

String Humidity_value_separator="=";
String Humidity_item_separator = ":";
String Humidity_start_id = "$";
String Humidity_stop_id = "#";

String humid_final="";
String humid="";
String temp="";	
	humid=floattostring(a);
	temp=floattostring(e);
	humid_final=	Humidity_start_id +
				 	"HU"+Humidity_value_separator+humid+Humidity_item_separator+
					"T"+Humidity_value_separator+temp+
					 Humidity_stop_id;
	//Serial.println(humid_final);
	return humid_final;
}
/////////////////////////////////////////String outpur//////////////////////
String GetHumidity(){
	humidity();
	return humidity_final;
	
	
}