/*
ESP32 Solenoid Controller
by Roland Pelayo
for TeachMeMicro

Rev 1.0 - December 4, 2023

Full tutorial on https://www.teachmemicro.com/esp32-solenoid-lock-controller
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "mainpage.h"

int solenoid = 14;

//provide your own WiFi SSID and password
const char* ssid = "<Insert Your WiFi SSID>";
const char* password = "<Insert Your WiFi Password>";

//create WebServer object at port 80
WebServer server(80);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // set the pin where the solenoid is connected as output pin
  pinMode(solenoid, OUTPUT);

   //Use ESP32 as WiFi Station
  WiFi.mode(WIFI_STA);
  //Initiate WiFi Connection
  WiFi.begin(ssid, password);
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  //Print your WiFi's SSID (might be insecure)
  Serial.println(ssid);
  Serial.print("IP address: ");
  //Print your local IP address (needed for browsing the app)
  Serial.println(WiFi.localIP());

  //Use multicast DNS so that we can use esp32.local 
  if(!MDNS.begin("esp32")) {
     Serial.println("Error starting mDNS");
     return;
  }

  //Handle visitors to root page
  server.on("/", []() {
   server.send(200, "text/html", page);
  });

  //Handle when user toggles the switch
  server.on("/switchState", []() {
    if(server.method() == HTTP_GET){
      //Print the state of the switch in Serial Monitor
      Serial.println(server.arg(0));
      if(server.arg(0).equals("true")) //if switch is true, turn on solenoid
        digitalWrite(solenoid, HIGH);
      else                             //if switch is false, turn off solenoid
        digitalWrite(solenoid, LOW);
    }
   server.send(200, "text/html", ""); //send empty string to client, so that browser stays on homepage
  });

  //start web server
  server.begin();
  //Just stating things
  Serial.println("HTTP server started");
}

// the loop routine runs over and over again forever:
void loop() {
  //Make the ESP32 always handle web clients
  server.handleClient();
}
