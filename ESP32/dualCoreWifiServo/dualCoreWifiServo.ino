#include "WifiServer.h"
#include "oled.h"
#include <Servo.h>

TaskHandle_t TaskCore0;

Servo myservo;  
static const int servoPin = 13;

void setup() 
{
  xTaskCreatePinnedToCore(WifiServer, "Task1", 10000, NULL, 1, &TaskCore0, 0);
  
  myservo.attach(servoPin);
  
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
    myservo.write(lastValue);
  }
  delay(100); 
}

void writeDisplay ()
{
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Position:");
  display.print(lastValue);
  display.println("/180");
  display.println();
  display.println(lastUpdate);
   
  display.display();
}
