#include <Arduino.h>
#include <WiFi.h>
#include <lionbit.h>
#include <display.h>
#include <WiFiClient.h>
#include <WebServer.h>

#include <WiFiUdp.h>
#include <HTTPUpdateServer.h>

#include <DNSServer.h>
#include <ESPmDNS.h>



/**
IN1 -> D4
IN2 -> D5
IN3 -> D6
IN4 -> D7 
*/

// AP credential 
const char * SSID  = "SMART-CAR"; //"King-knight";
const char *PASSWORD = "12345678"; //"nrl1633n";



WebServer server(80);
HTTPUpdateServer httpupdate; 

void stop()
{
  // OUT 1 & OUT 2
  digitalWrite(D4, LOW); 
  digitalWrite(D5, LOW); 

  // OUT 3 & OUT 4
  digitalWrite(D6, LOW); 
  digitalWrite(D7, LOW); 

  server.send(200, "text/html", "<h>STOP</h>");

}
void forward()
{
  // OUT 1 & OUT 2
  digitalWrite(D4, HIGH);  
  digitalWrite(D5, LOW); 

  // OUT 3 & OUT 4
  digitalWrite(D6, HIGH); 
  digitalWrite(D7, LOW); 
   server.send(200, "text/html", "<h>FORWARD</h>");
}

void backward()
{
  // OUT 1 & OUT 2
  digitalWrite(D4, LOW);  
  digitalWrite(D5, HIGH); 

  // OUT 3 & OUT 4
  digitalWrite(D6, LOW); 
  digitalWrite(D7, HIGH); 
   server.send(200, "text/html", "<h>BACKWARD</h>");
}

void left()
{
  // OUT 1 & OUT 2
  digitalWrite(D4, LOW);  
  digitalWrite(D5, HIGH); 

  // OUT 3 & OUT 4
  digitalWrite(D6, HIGH); 
  digitalWrite(D7, LOW); 
   server.send(200, "text/html", "<h>LEFT</h>");
}

void right()
{
  // OUT 1 & OUT 2
  digitalWrite(D4, HIGH);  
  digitalWrite(D5, LOW); 

  // OUT 3 & OUT 4
  digitalWrite(D6, LOW); 
  digitalWrite(D7, HIGH); 
   server.send(200, "text/html", "<h>RIGHT</h>");
}


void setup() {
  Serial.begin(115200); 
  pinMode(D4, OUTPUT); // IN1
  pinMode(D5, OUTPUT); // IN2
  pinMode(D6, OUTPUT); // IN3
  pinMode(D7, OUTPUT); // IN4

  bool ret = WiFi.softAP(SSID, PASSWORD);
  if(ret)
    Serial.println("AP Created.....");

  Serial.print("Local IP :");
  Serial.println(WiFi.localIP()); 

  MDNS.begin("wificar"); // http://wificar.local

  server.on("/stp", stop); 
  server.on("/fwd", forward); 
  server.on("/bkw", backward); 
  server.on("/lft", left); 
  server.on("/rght", right); 

  httpupdate.setup(&server, SSID, PASSWORD);

  server.begin();
  MDNS.addService("http", "tcp", 80);


}

void loop() {
  server.handleClient(); 
  
}