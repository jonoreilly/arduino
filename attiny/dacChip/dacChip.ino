#include <Wire.h>
#include <math.h>


int freq = 580;
long periodoMicro = 1000000/freq;

byte valor = 0;
byte dacAddress = 98; //0x10 -> 16
long segundos = 0;


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  //Serial.begin(115200);

  cli();

  TCCR1 &= ~( (1<<COM1A1)|(1<<COM1A0) );
  TCCR1 &= ~( (1<<COM1B1)|(1<<COM1B0) );

  TCCR1 |= (1<<CS13)|(1<<CS12);
  TCCR1 &= ~((1<<CS11)|(1<<CS10));

  TIMSK |= (1<<TOIE1);

  sei();

  TCNT1 = 0;
}

void loop() {
  valor = byte((sin((segundos%periodoMicro)/float(periodoMicro)*2*PI)*125)+125);
  //Serial.println(valor);
  Wire.beginTransmission(dacAddress);
  Wire.write(byte(0x00));
  Wire.write(valor);
  Wire.endTransmission();
}


ISR(TIMER1_COMPA_vect)
{
  segundos += 1;
}

