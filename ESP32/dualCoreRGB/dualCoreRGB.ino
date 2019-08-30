

TaskHandle_t TaskCore0;

int const pincount = 3;
int rgbValores [pincount] = {100,100,100};
int rgbPins [pincount] = {13,12,14};
bool rgbPinState [pincount] = {false,false,false};

int contador = 0;
int maxContador = 255;

bool rgbON = false;


hw_timer_t * timer = NULL;



#include "WifiServer.h"



void setup()
{    
  xTaskCreatePinnedToCore(WifiServer, "Task1", 10000, NULL, 1, &TaskCore0, 0);

  for(int i = 0; i < pincount; i++)
  {
    pinMode(rgbPins[i], OUTPUT);
  }
  
  setupTimer();
}

void loop()
{ 
  
}



void IRAM_ATTR onTimer()
{
  contador++;
  if(contador > maxContador) { contador = 0; }

  for(int i = 0; i < pincount; i++)
  {
    if(!rgbON)
    {
      if(rgbPinState[i])
      {
        rgbPinState[i] = false;
        digitalWrite(rgbPins[i], LOW);
      }
    }
    else
    {
      bool valor = rgbValores[i] > contador; 
      if(valor != rgbPinState[i])
      {
        rgbPinState[i] = valor;
        digitalWrite(rgbPins[i], valor);
      }
    }
  }
}

void setupTimer() 
{
  /* 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up */
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  /* Set alarm to call onTimer function every second 1 tick is 1us
  => 1 second is 1000000us */
  /* Repeat the alarm (third parameter) */
  timerAlarmWrite(timer, 5, true);
  timerAlarmEnable(timer);
}
