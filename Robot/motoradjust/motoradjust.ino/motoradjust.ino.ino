//#include <VirtualWire.h>

#define pinNumber 4

int pins[pinNumber] = {9, 10, 11, 12};
int valores[pinNumber] = {50, 50, 50, 50};
int valor = 0;
bool state[pinNumber] = {0, 0, 0, 0};
int estado = 0;
int analogPin = A1;

int contador = 1;

void setup() 
{

  for (int i = 0; i < pinNumber; i++)
  {
    pinMode(pins[i], OUTPUT);
  }

  Serial.begin(9600);

  cli(); // clear interrupts

  //set timer2 interrupt at 8kHz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  OCR2A = 200;
  //OCR2A = 249;// = (16*10^6) / (8000*8) - 1 (must be <256)
  TCCR2A |= (1 << WGM21);// turn on CTC mode
  TCCR2B |= (1 << CS21);// Set CS21 bit for 8 prescaler   
  TIMSK2 |= (1 << OCIE2A);// enable timer compare interrupt

  sei();// allow interrupts

}

int nuevo = 0;

void loop() 
{
  nuevo = (((long)analogRead(analogPin)*30)/1023);
  if (valor + 1 < nuevo || valor - 1 > nuevo) 
  { 
    valor = nuevo; 
    Serial.println(valor);
  }
}


ISR(TIMER2_COMPA_vect)
{
  contador++;
  if (contador > 100) { contador = 1; }  
  if (valor >= contador) 
  { 
    if (!estado)
    {
      estado = 1;
      digitalWrite(13, HIGH); 
      for (int i = 0; i < pinNumber; i++)
      {
        digitalWrite(pins[i], HIGH);
      }
    }
  }
  else 
  {
    if (estado)
    {
      estado = 0;
      digitalWrite(13, LOW); 
      for (int i = 0; i < pinNumber; i++)
      {
        digitalWrite(pins[i], LOW);
      }
    }
  }
}







