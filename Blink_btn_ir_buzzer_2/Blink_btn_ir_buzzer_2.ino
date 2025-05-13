#include "config.h"
#include "basic_config.h"





int irFlag = 1;
int buzFlag = 1;
int ledFlag = 1;

int fastLEDFlag = 2;
unsigned long fastLEDTime = 0;
int buzTime  = sizeof(melody) / sizeof(melody[0]);
int scenario = 1;
int irState = 0;
unsigned long detectTimer = 0;
void setup() {
  
  
  Serial.begin(9600);
  //output,input
  irsetup();
  //buzsetup();
  ledsetup();
  sersetup();
  btnsetup();
  fastLEDsetup();

  
  ledAlert(10,100);
  playSong(buzTime);
  mqttSetup();
}
void handleCmd(String cmd)
{
  if(cmd =="1")
  {
    ledAlert(20,100);
  }
  else if(cmd == "2")
  {
    playSong(buzTime);
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
  else if(cmd >="10" && cmd <="19")
  {
    int value = map(cmd.toInt(), 10, 19, 10, 255);
    setupBrightness(value);
  }
   else if(cmd >="20" && cmd <="29")
  {
    int value = map(cmd.toInt(), 20, 29, 5, 50);
    buzTime = value;
    if(value == 50)
    {
      buzTime  = sizeof(melody) / sizeof(melody[0]);
    }
  }
  else if(cmd == "31")
  {
    irFlag = true;
    ledFlag = 1;
    buzFlag = 1;
  }
  else if(cmd == "32")
  {
    irFlag = true;
    ledFlag = 0;
    buzFlag = 1;
  }
  else if(cmd == "33")
  {
    irFlag = true;
    ledFlag = 1;
    buzFlag = 0;
  }
  else if(cmd == "34")
  {
    irFlag = true;
    ledFlag = 0;
    buzFlag = 0;
  }
  else if(cmd == "35")
  {
    irFlag = false;
    ledFlag = 1;
    buzFlag = 0;
  }
  else if(cmd == "36")
  {
    irFlag = false;
    ledFlag = 0;
    buzFlag = 1;
  }
  else if(cmd == "37")
  {
    irFlag = false;
    ledFlag = 0;
    buzFlag = 0;
  }
  else if(cmd == "41")
  {
    irFlag = true;
  }
  else if(cmd == "42")
  {
    irFlag = false;
  }
  else if(cmd == "43")
  {
    ledFlag = true;
  }
  else if(cmd == "44")
  {
    ledFlag = false;
    disableLED();
  }
  else if(cmd == "45")
  {
    buzFlag = true;
  }
  else if(cmd == "46")
  {
    buzFlag = false;
    noTone(buzzer);
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

int handleIR()
{
  int ir = digitalRead(irPin);
  if(ir == 1)
  {
    Serial.println("ir Detected");
  }
  return ir;
}

void loop()
{
  mqttLoop();
  handleSerInput();
  /*
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
*/

  if(irFlag == false)
  {
    fastLEDloop(); 
    playSong(buzTime);
  }
  else 
  {
    if(handleIR() == true)
    {
      
      if(irState == 0)
      {
        
        irState = 1;
      }
      detectTimer = millis();
      
    }
    else
    {
      if(irState == 1 && millis() - detectTimer >5000 )
      {
        irState = 2;
        fastLEDTime = millis();
      }
    }
    if(irState == 0)
    {
      noTone(buzzer);
      disableLED();
    }
    else if(irState == 1)
    {
      fastLEDloop(); 
      playSong(buzTime);
    }
    else if(irState == 2)
    {
      noTone(buzzer);
      if(millis() - fastLEDTime > 5000)
      {
        irState = 0;
      }
    }
    
  }
  
  
  
}

