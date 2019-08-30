

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

void setupWifiServer ();
void runWifiServer ();
String httpON ();
String httpOFF ();


int LEDs[2][2] = {{14, 0}, {4, 0}};

const char* ssid     = "JAZZTEL_ZXjb";
const char* password = "ysg2h575k9fk";

WiFiServer wifiServer(69);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String lastUpdate = "NONE";
bool change = false;


void WifiServer (void * parameter)
{
  setupWifiServer();
  for (;;)
  { runWifiServer(); }
}


void setupWifiServer ()
{    
  for (int i = 0; i < 2; i++)
  { pinMode(LEDs[i][0], OUTPUT); }

  Serial.begin(115200);
  
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


void runWifiServer ()
{  
  TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
  TIMERG0.wdt_feed=1;
  TIMERG0.wdt_wprotect=0;
  
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
            wifiClient.println("Connection: close");
            wifiClient.println();            

            //wifiClient.print("<style>body{margin:0;white-space:nowrap;}.boton{width:40vw;height:90vh;margin:5vh 5vw;font-size:20vw;}</style>");
            
            //wifiClient.print("<a href='/H'><button class='boton'>ON</button></a>");
            //wifiClient.print("<a href='/L'><button class='boton'>OFF</button></a>");

            timeClient.forceUpdate();
            String formattedDate = timeClient.getFormattedDate();
            int splitT = formattedDate.indexOf("T");
            lastUpdate = formattedDate.substring(splitT+1, formattedDate.length()-1);
            wifiClient.print(lastUpdate);
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
        { mensaje = httpON(); }
        if (currentLine.endsWith("GET /OFF")) 
        { mensaje = httpOFF(); }
      }
    }
    wifiClient.stop();
    Serial.println("Client Disconnected.\n");
  }
}


String httpON ()
{
  if (!(LEDs[0][1] == 1 && LEDs[1][1] == 0))
  {
    LEDs[0][1] = 1;
    LEDs[1][1] = 0;
    digitalWrite(LEDs[0][0], LEDs[0][1]);
    digitalWrite(LEDs[1][0], LEDs[1][1]); 
    change = true;
  }
  return " - PIN 14: ON";  
}


String httpOFF ()
{
  if (!(LEDs[0][1] == 0 && LEDs[1][1] == 1))
  {
    LEDs[0][1] = 0;
    LEDs[1][1] = 1;
    digitalWrite(LEDs[0][0], LEDs[0][1]);
    digitalWrite(LEDs[1][0], LEDs[1][1]); 
    change = true;
  }
  return " - PIN 4: ON"; 
}
