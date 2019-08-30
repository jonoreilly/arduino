

#include <WiFi.h>

const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

int LED_BUILTIN = 2;

WiFiServer wifiServer(80);

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    delay(10);

    Serial.println("Setting up SSID and password:");
    Serial.println(ssid);
    Serial.println(password);
    WiFi.softAP(ssid, password);

    Serial.print("\nServer IP address: ");
    Serial.println(WiFi.softAPIP());
    
    wifiServer.begin();
}

void loop()
{
  WiFiClient wifiClient = wifiServer.available();  
  if (wifiClient)
  {        
    Serial.println("New Client.");        
    String currentLine = "";              
    while (wifiClient.connected()) 
    {      
      if (wifiClient.available()) 
      {       
        char c = wifiClient.read();      
        Serial.write(c);                 
        if (c == '\n') 
        {
          if (currentLine.length() == 0) 
          {
            wifiClient.println("HTTP/1.1 200 OK");
            wifiClient.println("Content-type:text/html");
            wifiClient.println();

            wifiClient.print("<style>body{margin:0;white-space:nowrap;}.boton{width:40vw;height:90vh;margin:5vh 5vw;font-size:20vw;}</style>");
            
            wifiClient.print("<a href='/H'><button class='boton'>ON</button></a>");
            wifiClient.print("<a href='/L'><button class='boton'>OFF</button></a>");

            wifiClient.println();
            break;
          } 
          else 
          { currentLine = ""; }
        }
        else if (c != '\r') 
        { currentLine += c; }
        
        if (currentLine.endsWith("GET /H")) 
        { digitalWrite(LED_BUILTIN, HIGH); }
        if (currentLine.endsWith("GET /L")) 
        { digitalWrite(LED_BUILTIN, LOW); }
      }
    }
    wifiClient.stop();
    Serial.println("Client Disconnected.");
  }
}
