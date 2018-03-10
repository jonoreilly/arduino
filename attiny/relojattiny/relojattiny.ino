/*
#include <avr/io.h>
#include <avr/interrupt.h>


byte outpin = 1;
bool outvalue = 0;
*/


void setup() {
/*
  cli();  // disable global interrupts
     TCCR1 = 0;  // set all bits in TCCR1 register to 0
     // 244 count, match every 2.00 secs, 8MHz clock, prescaller @ 16,384
     OCR1A = 244; 
     // clear timer on compare match
     TCCR1 |= (1 << CTC1);
     // set CS10, CS11,CS12, and CS13 bits for 16,384 prescaler
     TCCR1 |= (1 << CS10);
     TCCR1 |= (1 << CS11);
     TCCR1 |= (1 << CS12);
     TCCR1 |= (1 << CS13);
     // reset Timer/Counter prescaler
     GTCCR |= (1 << PSR1);
     // Zero (Reset) Timer1 8-bit up counter value
     TCNT1 = 0;
     // enable Timer1 compare interrupt
     TIMSK |= (1 << OCIE1A);
     // enable global interrupts
     sei();
*/
  for (int i = 0; i < 5; i++)
  {
    pinMode(i, OUTPUT);
  }
  //pinMode(outpin, OUTPUT);
  

}

int mytime = 500;

void loop() {

  for (int i = 0; i < 5; i++)
  {
    digitalWrite(i, HIGH);
    delay(mytime);
  }

  for (int i = 0; i < 5; i++)
  {
    digitalWrite(i, LOW);
    delay(mytime);
  }

}


/*
ISR(TIMER1_COMPA_vect)//timer1 interrupt 1Hz toggles pin 13 (LED)
{
  if (outvalue)
  {
    digitalWrite(outpin,outvalue);
    outvalue = 0;
  }
  else
  {
    digitalWrite(outpin,outvalue);
    outvalue = 1;
  }
}
*/


