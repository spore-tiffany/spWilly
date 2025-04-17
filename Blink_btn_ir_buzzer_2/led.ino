


void ledAlert(int num,int dtime)
{
  for(int i = 0 ; i < num*2 ; i++)
  {
    digitalWrite(ledPin, (i+1)%2);
    delay(dtime);
  }
}

void ledsetup()
{
  pinMode(ledPin, OUTPUT);
}

void ledloop()
{

}