/*
Code written by Sounder Rajendran on June 12, 2019
sounderajendran@gmail.com | Github: https://github.com/RSounder
All rights reserved. Using entire code or a part of it can be done for free of cost, provided this attribution text remains intact and unaltered.  
*/

#include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);
const char* ssid = "Stark";
const char* password = "eachday97";

void setup() 
{
  Serial.begin(115200);
  connectWiFi();
  server.begin();
}

void loop() 
{

}

void connectWiFi()
{
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));
}
