#include <Arduino.h>
#include <BasicOTA.h>
#include <WiFiManager.h>
#include "clockapp.h"

// config.h must be added by the user.
// It may contain sensitive data that
// should not got in source control
#include "config.h"
// Expected contents:
/*
#pragma once


#define HOST_NAME       "resistor_clock"
#define OTA_PASSWORD    "OTA password"
*/

ClockApp app;
unsigned long last;

void setup()
{
    Serial.begin(115200);
    delay(10);
    Serial.println("Starting Resistor Clock Sketch");

    app.setup();

    app.setMessage("Waiting for network...");

    WiFi.mode(WIFI_STA);
    WiFiManager wm;

    wm.setAPCallback([](WiFiManager *wm) {
        app.setMessage("Configure WiFi\nSSID:  " + wm->getConfigPortalSSID() + "\nPassword:  Ohms Law\nhttp://192.168.4.1");
    });

    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    res = wm.autoConnect("ResistorClock", "Ohms Law"); // password protected ap

    if (!res)
    {
        Serial.println("Failed to connect");
        delay(3000);
        ESP.restart();
    } 
    else
    {
        //if you get here you have connected to the WiFi    
        Serial.println("Connected to wireless network");
    }

    // wifi_setup(HOST_NAME, SSID, SSID_PASSWORD);
    ota_setup(HOST_NAME, OTA_PASSWORD);
    Serial.println("Clock Sketch Setup");

    app.start();
    Serial.println("Clock Sketch Running");
    last = millis();
}

void loop()
{
    // wifi_onLoop();
    ota_onLoop();
    app.on_loop();
    auto t = millis();
    if (t - last > 3000)
    {
        Serial.print('.');
        last = t;
    }
}