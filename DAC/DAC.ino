
int freq = 440;
int intToBinary = 0;
//long counter = 0;
//long microSeconds = 0;
long periodoMicro = 1000000/freq;
//long last = 0;
float sinvalue = 0.0;
//float angle = 0;
//float offset = 0;
byte count = 0;
byte pins[] = {6, 5, 4, 3, 2};
byte const pinQuantity = 5;
//bool add = true;
bool bus[] =  {0, 0, 0, 0, 0};

void setup() 
{
  for (int i = 0; i < pinQuantity; i++)
  {
    pinMode(pins[i], OUTPUT);
  }
  pinMode(LED_BUILTIN, OUTPUT);
  
// Serial.begin(9600);
}



void loop() 
{
  /*
  if(micros()%10000 > 5000)
  {digitalWrite(LED_BUILTIN, HIGH);}
  else
  {digitalWrite(LED_BUILTIN, LOW);}
  */
 // Serial.println(micros());
  /*
  counter ++;
  if (add)
  {
   if (counter%1000 == 0)
   { 
    periodoMicro += periodoMicro/100;
    offset = angle;
    last = microSeconds;
    if (periodoMicro > 1000000/250)
    {
      add = false;
    }
   }
  }
  else
  {
    if (counter%1000 == 0)
   { 
     periodoMicro -= periodoMicro/100;
     offset = angle;
     last = microSeconds;
     if (periodoMicro < 1000000/1200)
     {
       add = true;
     }
    }
  }
  */
 /* 
  microSeconds = micros();
  angle = ((((microSeconds-last) % periodoMicro)/(float)periodoMicro)*(2*PI)+offset);
  
  sinvalue = sin(angle);
*/

  sinvalue = sin(((((micros()) % periodoMicro)/(float)periodoMicro)*(2*PI)));

//Serial.println(sinvalue);

  intToBinary = (int)((sinvalue + 1) * 16);

// Serial.println(intToBinary);


  count = 0;
  while (intToBinary > 0)
      {
        bus[count] = intToBinary % 2;
        intToBinary = intToBinary / 2;
        count++;  
      }
 //     Serial.println("cucu");
    
      for (int i = 0; i < count; i++)
      {
          digitalWrite(pins[i], bus[i]);
      }

      for (int i = count; i < pinQuantity; i++)
      {
        digitalWrite(pins[i], LOW); 
      }


  /*
  if (sinvalue > 0)
  {
    digitalWrite(pins[0], HIGH); 
  }
  else
  {
    digitalWrite(pins[0], LOW);
  }

  if ((sinvalue > 0.5) || ((0 > sinvalue) && (sinvalue > -0.5)))
  {
    digitalWrite(pins[1], HIGH);
  }
  else
  {
    digitalWrite(pins[1], LOW);
  }

  if ((sinvalue > 0.75) || ((0.5 > sinvalue) && (sinvalue > 0.25)) || ((0 > sinvalue) && (sinvalue > -0.25)) || ((-0.5 > sinvalue) && (sinvalue > -0.75)))
  {
    digitalWrite(pins[2], HIGH);
  }
  else
  {
    digitalWrite(pins[2], LOW);
  }

  if ((sinvalue > 0.875) || ((0.75 > sinvalue) && (sinvalue > 0.625)) || ((0.5 > sinvalue) && (sinvalue > 0.375)) || ((0.25 > sinvalue) && (sinvalue > 0.125)) || ((0 > sinvalue) && (sinvalue > -0.125)) || ((-0.25 > sinvalue) && (sinvalue > -0.375)) || ((-0.5 > sinvalue) && (sinvalue > -0.625)) || ((-0.75 > sinvalue) && (sinvalue > -0.875)))
  {
    digitalWrite(pins[3], HIGH);
  }
  else
  {
    digitalWrite(pins[3], LOW);
  }
  
  if ((sinvalue > 0.9375) || ((0.875 > sinvalue) && (sinvalue > 0.8125)) || ((0.75 > sinvalue) && (sinvalue > 0.6875)) || ((0.625 > sinvalue) && (sinvalue > 0.5625)) || ((0.5 > sinvalue) && (sinvalue > 0.4375)) || ((0.375 > sinvalue) && (sinvalue > 0.3125)) || ((0.25 > sinvalue) && (sinvalue > 0.1875)) || ((0.125 > sinvalue) && (sinvalue > 0.0625)) || ((0 > sinvalue) && (sinvalue > -0.0625)) || ((-0.125 > sinvalue) && (sinvalue > -0.1875)) || ((-0.25 > sinvalue) && (sinvalue > -0.3125)) || ((-0.375 > sinvalue) && (sinvalue > -0.4375)) || ((-0.5 > sinvalue) && (sinvalue > -0.5625)) || ((-0.625 > sinvalue) && (sinvalue > -0.6875)) || ((-0.75 > sinvalue) && (sinvalue > -0.8125)))
  {
    digitalWrite(pins[4], HIGH);
  }
  else
  {
    digitalWrite(pins[4], LOW);
  }
  */
}
   

