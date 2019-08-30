
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ssid     = "JAZZTEL_ZXjb";
const char* password = "ysg2h575k9fk";

int LED_BUILTIN = 2;

WiFiServer wifiServer(69);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    delay(10);

    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) 
    { delay(500); Serial.print("."); }

    Serial.println("\nWiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    
    wifiServer.begin();
    timeClient.begin();
    timeClient.setTimeOffset(7200);
}

void loop()
{
  WiFiClient wifiClient = wifiServer.available();  
  if (wifiClient)
  {        
    Serial.println("New Client.");        
    String currentLine = "";    
    String mensaje = " - No comand passed";          
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

            //wifiClient.print("<style>body{margin:0;white-space:nowrap;}.boton{width:40vw;height:90vh;margin:5vh 5vw;font-size:20vw;}</style>");
            
            //wifiClient.print("<a href='/H'><button class='boton'>ON</button></a>");
            //wifiClient.print("<a href='/L'><button class='boton'>OFF</button></a>");

            timeClient.forceUpdate();
            String formattedDate = timeClient.getFormattedDate();
            int splitT = formattedDate.indexOf("T");
            wifiClient.print(formattedDate.substring(splitT+1, formattedDate.length()-1));
            wifiClient.print(mensaje);

            wifiClient.println();
            break;
          } 
          else 
          { currentLine = ""; }
        }
        else if (c != '\r') 
        { currentLine += c; }
        
        if (currentLine.endsWith("GET /ON")) 
        { digitalWrite(LED_BUILTIN, HIGH); mensaje = " - LED: ON";}
        if (currentLine.endsWith("GET /OFF")) 
        { digitalWrite(LED_BUILTIN, LOW); mensaje = " - LED: OFF"; }
      }
    }
    wifiClient.stop();
    Serial.println("Client Disconnected.\n");
  }
}
