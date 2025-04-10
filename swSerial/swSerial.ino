#include "SoftwareSerial.h"
SoftwareSerial swSerial(2,3);//rx,tx
void ledAlert(int num,int dtime)
{
  for(int i = 0 ; i < num*2 ; i++)
  {
    digitalWrite(13, (i+1)%2);
    delay(dtime);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  swSerial.begin(9600);
  Serial.println("hello world");
  pinMode(13, OUTPUT);
  ledAlert(10,100);
    
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
void loop() {
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
