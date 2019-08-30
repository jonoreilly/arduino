
#include "WifiServer.h"
#include "stepper.h"

TaskHandle_t TaskCore0;


void setup() 
{
  xTaskCreatePinnedToCore(WifiServer, "Task1", 10000, NULL, 1, &TaskCore0, 0);
  stepperInit();
}

void loop()
{
  stepperStep();
  delay(10);
}
