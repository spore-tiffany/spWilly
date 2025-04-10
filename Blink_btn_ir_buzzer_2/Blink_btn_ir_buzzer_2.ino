int ledPin = 2;
int btnPin = 10;
int buzrPin =13;
int irPin =12;
int irFlag = 0;

void setup() {
  //output,input
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  pinMode(irPin,INPUT);
  pinMode(buzrPin,OUTPUT);
  Serial.begin(9600);
  Serial.println("hello world");
  Serial.println("setup");
  playSong(15);
}

void loop() {
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
