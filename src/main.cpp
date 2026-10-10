
#include <FS.h>
#include <Arduino.h>
#include <Hash.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SimpleTimer.h>
#include <ESPAsyncWiFiManager.h> 

#include "coms_tracer.h"
#include "coms_web.h"
#include "simulator.h"

//#define SIMULATOR
SimpleTimer timer;

int timerTask1, timerTask2, timerTask3;

void setup() {

  //Onboard LED port Direction output
  pinMode(LED,OUTPUT); 
  pinMode(WIFI_LED,OUTPUT); 
  pinMode(COM_LED,OUTPUT); 
  
  Serial.begin(115200);
  init_wifi_manager();

  SPIFFS.begin();
  Serial.println("");

  String str = "";
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
      str += dir.fileName();
      str += " / ";
      str += dir.fileSize();
      str += "\r\n";
  }
  Serial.print(str);
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  //Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  
  digitalWrite(WIFI_LED,1);

  init_webserver();
  
  Serial.println("HTTP server started");

#ifndef SIMULATOR
  timerTask2 = timer.setInterval(RS485_PERIOD_MS, read_from_tracer);
#endif 

#ifdef SIMULATOR
  for(uint32_t ix = 0; ix < 1000; ix++)
  {
    simulate_data();
  }
  timerTask3 = timer.setInterval(RS485_PERIOD_MS, simulate_data);

#endif
  
}

void loop() {
  timer.run();
}