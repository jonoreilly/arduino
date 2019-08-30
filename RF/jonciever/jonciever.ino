
int triggerh = 800;
int triggerl = 500;

int warmup = 100000;

int timeout = 10000000;

int value, start, mid, last;

int inPin = 1;
int outPin = 0;


void setup() {

  pinMode(outPin, OUTPUT);

}

void loop() 
{

  value = analogRead(inPin);

  if (value > triggerh)
  {
    start = micros();
    while (value > triggerl && micros()-start < timeout)
    {
      value = analogRead(inPin);
    }

    if (micros()-start >= warmup)
    {
      start = micros();
      while (value < triggerh && micros()-start < timeout)
      {
        value = analogRead(inPin);
      }
      mid = micros();
      while (value > triggerl && micros()-mid < timeout)
      {
        value = analogRead(inPin);
      }
      last = micros();

      if (mid-start < last-mid)
      {
        digitalWrite(outPin, HIGH);
      }
    
      else
      {
        digitalWrite(outPin, LOW);
      }
    }
    
  }

}


void action(bool value)
{
  
}

