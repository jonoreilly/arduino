

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"


#include "pagina.h"


void setupWifiServer ();
void runWifiServer ();
void processRequest(String currentLine);
void processRGB(String currentLine, int requestPosition, String requestHeader);
void processON();
void processOFF();


int LEDs[2][2] = {{14, 0}, {4, 0}};

const char* ssid     = "JAZZTEL_ZXjb";
const char* password = "ysg2h575k9fk";

WiFiServer wifiServer(80);
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
  
  Serial.print("Connecting to");
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


void resetTimerWatchDog()
{
  TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
  TIMERG0.wdt_feed=1;
  TIMERG0.wdt_wprotect=0;
}


void runWifiServer ()
{  
  resetTimerWatchDog();
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

            wifiClient.print(HTML);

            /*
            timeClient.forceUpdate();
            String formattedDate = timeClient.getFormattedTime();
            int splitT = formattedDate.indexOf("T");
            lastUpdate = formattedDate.substring(splitT+1, formattedDate.length()-1);
            wifiClient.print(lastUpdate);
            wifiClient.print(mensaje);
            */

            wifiClient.println();
            Serial.println("Request respondida");
            break;
          } 
          else 
          { 
            resetTimerWatchDog();
            processRequest(currentLine);
            currentLine = "";
          }
        }
        else if (c != '\r') 
        { currentLine += c; }
        
        //if (currentLine.endsWith("GET /ON")) 
        //{ mensaje = httpON(); }
        //if (currentLine.endsWith("GET /OFF")) 
        //{ mensaje = httpOFF(); }

      }
    }
    wifiClient.stop();
    Serial.println("Client Disconnected.\n");
  }
}

/*
String httpON ()
{
  if (!(LEDs[0][1] == 1 && LEDs[1][1] == 0))
  {
    LEDs[0][1] = 1;
    LEDs[1][1] = 0;
    rgbValores[0] = 250;
    rgbValores[1] = 250;
    rgbValores[2] = 250;
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
    rgbValores[0] = 50;
    rgbValores[1] = 50;
    rgbValores[2] = 50;
    digitalWrite(LEDs[0][0], LEDs[0][1]);
    digitalWrite(LEDs[1][0], LEDs[1][1]); 
    change = true;
  }
  return " - PIN 4: ON"; 
}
*/



int contieneString(String contenedor, String mensaje)
{
  int lenContenedor = contenedor.length();
  int lenMensaje = mensaje.length();
  
  for(int i = 0; i < lenContenedor; i++)
  {
    bool contiene = true;
    if(lenMensaje+i > lenContenedor) { break; }
    for(int j = 0; j < lenMensaje; j++)
    {
      if (contenedor.charAt(i+j) != mensaje.charAt(j))
      {
        contiene = false;
        break;
      }
    }
    if (contiene) { return i; }
  }
  return -1;
}




void processRequest(String currentLine)
{
  String requestHeader = "GET /RGB/";
  int requestPosition = contieneString(currentLine, requestHeader);
  if (requestPosition >= 0) { processRGB(currentLine, requestPosition, requestHeader); }
  else
  {
    requestHeader = "GET /ON";
    requestPosition = contieneString(currentLine, requestHeader);
    if (requestPosition >= 0) { processON(); }
    else 
    {
      requestHeader = "GET /OFF";
      int requestPosition = contieneString(currentLine, requestHeader);
      if (requestPosition >= 0) { processOFF(); }
    }
  }
}




void processRGB(String currentLine, int requestPosition, String requestHeader)
{
  int color = -1;
  char charcolor = currentLine.charAt(requestPosition + requestHeader.length());
  if (charcolor == 'R') { color = 0; }
  else if (charcolor == 'G') { color = 1; }
  else if (charcolor == 'B') { color = 2; }
  
  if(color >= 0)
  {
    String cantidad = "";
    int contadorNumero = 0;
    int startNumero = requestPosition + requestHeader.length() + 2;
    while (true)
    {
      if(startNumero + contadorNumero >= currentLine.length()) { break; }
      char elchar = currentLine.charAt(startNumero + contadorNumero);
      contadorNumero++;
      if (elchar >= '0' && elchar <= '9') { cantidad += elchar; }
      else {break;}
    }
    if (cantidad.length() != 0) { rgbValores[color] = cantidad.toInt(); }
  }
}



void processON()
{
  rgbON = true;
}

void processOFF()
{
  rgbON = false;
}
