#ifndef COMS_WEB_H
#define COMS_WEB_H

#include <Arduino.h>
#include <Hash.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h> 

#define WIFI_LED D0




enum State { XML_Preamble, XML_Body, XML_Done };



uint32_t init_wifi_manager();
uint32_t init_webserver();


void XML_hist_data(AsyncWebServerRequest *request);
void XML_curr_data(AsyncWebServerRequest *request);
void XML_gen_data(AsyncWebServerRequest *request);
void notFound(AsyncWebServerRequest *request);

#endif
