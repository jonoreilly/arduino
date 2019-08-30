int pin = 10;
boolean estado = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);

 cli(); // clear interrupts
/*
  // set timer 1 to 1 Hz
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 15644;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 pres            caler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
*/
  //set timer2 interrupt at 8kHz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 8khz increments
  OCR2A = 30;// = (16*10^6) / (8000*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 bit for 8 prescaler
  TCCR2B |= (1 << CS21);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);

  sei();// allow interrupts
}

void loop() {
  // put your main code here, to run repeatedly:

}


ISR(TIMER2_COMPA_vect)
{
  if (estado)
  {
    estado = false;
    digitalWrite(pin, HIGH);
  }
  else
  {
    estado = true;
    digitalWrite(pin, LOW);
  }
}

