#include "WifiServer.h"
#include "oled.h"

TaskHandle_t TaskCore0;

String text[] = {"OFF", "ON"};

void setup()
{    
  xTaskCreatePinnedToCore(WifiServer, "Task1", 10000, NULL, 1, &TaskCore0, 0);
  
  display.begin(SSD1306_SWITCHCAPVCC); 
  display.display();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  writeDisplay();
}

void loop()
{ 
  if (change)
  {
    change = false;
    writeDisplay();
  }
  delay(100); 
}


void writeDisplay ()
{
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Pin 14 ");
  display.println(text[LEDs[0][1]]);
  display.print("Pin 4  ");
  display.println(text[LEDs[1][1]]);
  display.println();
  display.println(lastUpdate);
   
  display.display();
}
