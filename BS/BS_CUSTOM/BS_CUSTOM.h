
/////////////////floattostring///////////////////////
String floattostring(float d){
  
  String d1="";
 
  
  float subint= (int)d;
  float subfract= abs(d-subint);
  int upto2= (int)(subfract*100);
 
  int num1;
  int num2;
  num1=(int)abs(d);
  num2= upto2;
  if(d>=0){
   d1= String(num1)+"."+String(num2);

  }
  else{
    d1= "-"+String(num1)+"."+String(num2);
     
  }
  
  return d1;
  
  
}
////////////////end-floatotstrinf////////////////