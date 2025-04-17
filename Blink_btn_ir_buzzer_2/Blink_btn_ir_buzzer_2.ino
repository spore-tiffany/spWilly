#include "config.h"






int irFlag = 0;
int fastLEDFlag = 0;
unsigned long fastLEDTime = 0;

void setup() {
  //output,input
  irsetup();
  buzsetup();
  ledsetup();
  sersetup();
  btnsetup();
  fastLEDsetup();

  
  ledAlert(10,100);
  playSong(15);
}
void handleCmd(String cmd)
{
  if(cmd =="1")
  {
    ledAlert(10,100);
  }
  else if(cmd == "2")
  {
    playSong(15);
  }
  else if(cmd == "3")
  {
    fastLEDFlag = fastLEDFlag + 1;
    fastLEDFlag = fastLEDFlag % 4;
    fastLEDTime = millis();
    Serial.print("fastLEDFlag = ");
    Serial.println(fastLEDFlag);

    /*
    if(fastLEDFlag==0)
    {
      fastLEDFlag = 1;
    }
    else if(fastLEDFlag==1){
      fastLEDFlag = 2;
    }
    else if(fastLEDFlag==2){
      fastLEDFlag = 0;
    }
    */
  }
  else if(cmd == "4")
  {
    changeBrightness(10);
  }
  else if(cmd == "5")
  {
    changeBrightness(-10);
  }
}
void handleSerInput()
{
  String str =  hwSerialRead();
  if(str != "")
  {
    Serial.print("str=");
    Serial.println(str);
    handleCmd(str);
    

  }
}

void loop()
{
  handleSerInput();
  if(fastLEDFlag == 0)
  {
    disableLED();
    fastLEDFlag = 1;
  }
  else if(fastLEDFlag == 1)
  {
  }
  else if(fastLEDFlag == 2)
  {
    fastLEDloop(); 
  }
  else if(fastLEDFlag == 3)
  {
    if(millis() - fastLEDTime > 5000)
    {
      fastLEDFlag = 0;
    }
  }
  
}
void loop_() { 
  fastLEDloop(); 
  //Serial.println("loop");
  //delay(1000); 
  int b = digitalRead(btnPin);
  if(b == false)
  {
    Serial.println("press");
    digitalWrite(ledPin, LOW); 
    //tone(buzrPin,528);
  }
  else 
  {
    //Serial.println("No press");
    digitalWrite(ledPin, HIGH);
    //noTone(buzrPin);
  }
  int ir = digitalRead(irPin);
  if(ir == true)
  {
    
    if(irFlag == 0)
    {
      Serial.println("Detected");
      playSong(20);
    }
    irFlag = 1;
  }
  else {
    irFlag =0;
  
  }

  /*
  digitalWrite(ledPin, HIGH);   
  delay(1000);                      
  digitalWrite(ledPin, LOW);    
  delay(1000);  
  */                    
}
