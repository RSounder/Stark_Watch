/*
Code written by Sounder Rajendran on June 12, 2019
sounderajendran@gmail.com | Github: https://github.com/RSounder
All rights reserved. Using entire code or a part of it can be done for free of cost, provided this attribution text remains intact and unaltered.  
*/

#include <Adafruit_NeoPixel.h>      //Include AdaFruit NEO Library
#include <ESP8266WiFi.h>

WiFiClient client;
WiFiServer server(80);

const char* ssid = "Your_SSID";
const char* password = "Your_Password";

String  data =""; 

#define PIN            5            //Assign NEO Ring to pin 9
#define NUMPIXELS      12           //Define that there are 24 LED's in ring
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);     //AdaFruit Neo Library

int delayval = 3000;                // delay for 2.5 seconds (24 LED's in a minute)
int barStart = 0; // start at point 0
int barSize = 1; // start with one blue pixel
int num_rec_1=0;
int num_rec_2=0;
int num_rec_3=0;

void setup() {
  
    Serial.begin(115200);
  /* start server communication */
  connectWiFi();
  server.begin();
  
  pixels.begin();                   // This initializes the NeoPixel library.
pixels.show(); // Initialize all pixels to 'off'
}

void loop() {
rainbowCycle(3);

//______
Serial.println("In Loop");
  delay(100);
    /* If the server available, run the "checkClient" function */  
    client = server.available();
    if (!client) return; 
    data = checkClient ();
delay(100);
Serial.println(data);
if(data.length()==3){
Serial.println("Length 3");
  num_rec_1=int(data[0])-48;
  num_rec_2=0;
  num_rec_3=int(data[2])-48;
Serial.print(num_rec_1);Serial.print(":");Serial.print(num_rec_2);Serial.print(":");Serial.println(num_rec_3);
  
}
if(data.length()==4){

  if(data[1]=='h'){
Serial.println("Length 4");
  num_rec_1=int(data[0])-48;
  num_rec_2=int(data[2])-48;
  num_rec_3=int(data[3])-48;
  }
  else if(data[2]=='h'){
  num_rec_1=int(data[0]+data[1]);
  num_rec_2=0;
  num_rec_3=int(data[3])-48;
  if(num_rec_1==97){num_rec_1=10;}
  else if(num_rec_1==98){num_rec_1=11;}
  else if(num_rec_1==99){num_rec_1=12;}  
  }
Serial.print(num_rec_1);Serial.print(":");Serial.print(num_rec_2);Serial.print(":");Serial.println(num_rec_3);
  
}
else if(data.length()==5){
Serial.println("Length 5");
  num_rec_1=int(data[0]+data[1]);
  num_rec_2=int(data[3])-48;
  num_rec_3=int(data[4])-48;
  
  if(num_rec_1==97){num_rec_1=10;}
  else if(num_rec_1==98){num_rec_1=11;}
  else if(num_rec_1==99){num_rec_1=12;}
Serial.print(num_rec_1);Serial.print(":");Serial.print(num_rec_2);Serial.print(":");Serial.println(num_rec_3);
  
  }
delay(1000);
//______
  for(int i=0;i<NUMPIXELS;i++){
    pixels.clear();
    //delay(1000);
  }
for(int i=0; i<num_rec_1;i++){
  pixels.setPixelColor(i, pixels.Color(255, 0, 0));
}
  pixels.show();                                        // This sends the updated pixel to the ring
  delay(delayval);                                      // Delay for a period of time

///////////////////

  for(int i=0;i<NUMPIXELS;i++){
    pixels.clear();
    //delay(1000);
  }

if(num_rec_2==0){
  pixels.setPixelColor(0, pixels.Color(127, 127, 127));
  pixels.setPixelColor(3, pixels.Color(127, 127, 127));
  pixels.setPixelColor(6, pixels.Color(127, 127, 127));
  pixels.setPixelColor(9, pixels.Color(127, 127, 127));

  }
else{
for(int i=0; i<num_rec_2;i++){
  pixels.setPixelColor(i, pixels.Color(0, 255, 0));
}
  pixels.show();                                        // This sends the updated pixel to the ring
  delay(delayval);                                      // Delay for a period of time
}
//////////////////

  for(int i=0;i<NUMPIXELS;i++){
    pixels.clear();
    //delay(1000);
  }


if(num_rec_3==0){

for(int i=0; i<12;i++){
  pixels.setPixelColor(i, pixels.Color(127,127,127));
}
  }  
for(int i=0; i<num_rec_3;i++){
  pixels.setPixelColor(i, pixels.Color(0,0,255));
}
  pixels.show();                                        // This sends the updated pixel to the ring
  delay(delayval);                                      // Delay for a period of time

/////////////////
theaterChaseRainbow(3);
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < pixels.numPixels(); i=i+3) {
        pixels.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      pixels.show();

      delay(wait);

      for (uint16_t i=0; i < pixels.numPixels(); i=i+3) {
        pixels.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
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
