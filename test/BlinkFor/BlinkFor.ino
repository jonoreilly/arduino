int LED_BUILTIN = 2;

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
  for (int i = 100; i < 1000; i += i/2)
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(i);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(i/2);                       // wait for a second
  }
}
