
byte anodepin[4] = {2,3,4,5};
byte cathodepin[7] = {6,7,8,9,10,11,12};
byte puntopin = 1;
byte alarmapin = 13;

int alarmastoppin = A5;
int inputsegundos = A0;
int inputminutos = A1;
int inputhoras = A2;
byte state = 1;

byte minutos = 0;
byte horas = 0;
byte segundos = 0;
bool alarma = 0;

byte currentDigit = 0;

bool numeros[10][7] = {{0,0,0,0,0,0,1},//0
                       {1,0,0,1,1,1,1},//1
                       {0,0,1,0,0,1,0},//2
                       {0,0,0,0,1,1,0},//3
                       {1,0,0,1,1,0,0},//4
                       {0,1,0,0,1,0,0},//5
                       {0,1,0,0,0,0,0},//6
                       {0,0,0,1,1,1,1},//7
                       {0,0,0,0,0,0,0},//8
                       {0,0,0,1,1,0,0}};//9


void setup() {

  for (byte i = 0; i < 4; i++)
  {
    pinMode(anodepin[i], OUTPUT);
  }

  for (byte i = 0; i < 7; i++)
  {
    pinMode(cathodepin[i], OUTPUT);
  }

  pinMode(puntopin, OUTPUT);
  pinMode(alarmapin, OUTPUT);

  cli(); // clear interrupts

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

  //set timer2 interrupt at 8kHz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 8khz increments
  OCR2A = 249;// = (16*10^6) / (8000*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 bit for 8 prescaler
  TCCR2B |= (1 << CS21);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);

  sei();// allow interrupts
}



void loop() {

  if (analogRead(inputsegundos) > 700 && state%2 != 0)
  {
    state = state*2;
    segundos = 0;
    /*
    segundos += 1;
    if (segundos >= 60)
    {
      segundos -= 60;
    }
    */
  }

  if (analogRead(inputsegundos) < 300 && state%2 == 0)
  {
    state = state/2;
  }

  if (analogRead(inputminutos) > 700 && state%3 != 0)
  {
    state = state*3;
    minutos += 1;
    if (minutos >= 60)
    {
      minutos -= 60;
    }
  }

  if (analogRead(inputminutos) < 300 && state%3 == 0)
  {
    state = state/3;
  }

  if (analogRead(inputhoras) > 700 && state%5 != 0)
  {
    state = state*5;
    horas += 1;
    if (horas >= 24)
    {
      horas -= 24;
    }
  }

  if (analogRead(inputhoras) < 300 && state%5 == 0)
  {
    state = state/5;
  }

  if(alarma)
  {
    sonarAlarma();
  }
}



ISR(TIMER1_COMPA_vect)
{
  segundos += 1;
  
  if (segundos >= 60)
  {
    segundos = 0;
    minutos += 1;
    
    if (minutos >= 60)
    {
      minutos = 0;
      horas += 1;
            
      if (horas >= 24)
      {
        horas = 0;
      }
      alarma = 1;
    }
  }
}



ISR(TIMER2_COMPA_vect)
{
  for (byte i = 0; i < 4; i++)
  {
    digitalWrite(anodepin[i], LOW);
  }
  
  for (byte i = 0; i < 7; i++)
  {
    digitalWrite(cathodepin[i], HIGH);
  }
  
  digitalWrite(puntopin, HIGH);
  digitalWrite(anodepin[currentDigit], HIGH);
  
  byte numero = 0;
  
  if (currentDigit == 0)
  {
    numero = horas/10;
    //numero = minutos/10;
  }
  else
  {
    if (currentDigit == 1)
    {
      numero = horas - (horas/10)*10;
      //numero = minutos - (minutos/10)*10;
      digitalWrite(puntopin, LOW);
    }
    else
    {
      if (currentDigit == 2)
      {
        numero = minutos/10;
        //numero = segundos/10;
      }
      else
      {
        numero = minutos - (minutos/10)*10;
        //numero = segundos - (segundos/10)*10;
      }
    }
  }
  
  for (byte i = 0; i < 7; i++)
  {
    digitalWrite(cathodepin[i], numeros[numero][i]);
  }

  currentDigit += 1;
  if (currentDigit == 4)
  {
    currentDigit = 0;
  }
}


void sonarAlarma()
{
  alarma = 0;
  
  for (int i = 0; i < 100; i ++)
  {
    digitalWrite(alarmapin, HIGH);
    delay(300);
    digitalWrite(alarmapin, LOW);
    delay(300);

    if (analogRead(alarmastoppin) >= 700)
    {
      break;
    }
  }
}


