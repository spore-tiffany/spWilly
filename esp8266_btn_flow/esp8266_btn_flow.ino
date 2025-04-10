
#define BTN_NONE 0
#define BTN_PRESS 1
#define BTN_RELEASE 2


int btnPin = 10;
int ledPin =2;
int state = BTN_NONE;
void setup() {
    // put your setup code here, to run once:
  pinMode(btnPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  for(int i = 0 ; i < 3 ; i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(300);
    digitalWrite(ledPin,LOW);
    delay(300);
  }
}
int getBtnState()
{
  int rtn;
  int btnPress = digitalRead(btnPin);
  if(btnPress == true)
  {
    //Serial.println("NO");
    if(state == BTN_PRESS)
    {
      state = BTN_RELEASE;
    }
    else if(state == BTN_RELEASE)
    {
      state = BTN_NONE;
    }
  }
  else {
    //Serial.println("YES");
    if(state == BTN_NONE)
    {
      state = BTN_PRESS;
    }
  }
  delay(10);
  rtn = state;
  return rtn;
}
int count;
void loop() {
  // put your main code here, to run repeatedly:
  int r = getBtnState();
  if(r == BTN_RELEASE)
  {
    count = count + 1;
    count = count % 7;
    Serial.print("count:");
    Serial.println(count);
  }

}
