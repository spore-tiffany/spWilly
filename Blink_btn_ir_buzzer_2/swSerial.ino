#include "SoftwareSerial.h"
SoftwareSerial swSerial(2,3);//rx,tx


void sersetup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  swSerial.begin(9600);
  Serial.println("hello world");
  
    
}
String hwSerialRead()
{
  String str="";
  while(Serial.available())
  {
    char c = Serial.read();
    if(c!='\n')
    {
      str = str + c;
    }
    delay(5);//***
  }

  return str;
}

String swSerialRead()
{
  String str="";
  while(swSerial.available())
  {
    char c = swSerial.read();
    if(c!='\n')
    {
      str = str + c;
    }
    delay(5);//***
  }

  return str;
}
void serloop() {
  // put your main code here, to run repeatedly:
  String hwStr = hwSerialRead();
  String swStr = swSerialRead();
  if(hwStr !="")
  {
    Serial.print("hwSerial:");
    Serial.println(hwStr);
    //ledAlert(hwStr.length(),150);
    swSerial.println(hwStr);
  }
  if(swStr !="")
  {
    Serial.print("swSerial:");
    Serial.println(swStr);
    ledAlert(swStr.length(),150);
  }
  delay(50);
}
