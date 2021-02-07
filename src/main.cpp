#include <Arduino.h>
#include <BasicOTA.h>
#include <WiFiManager.h>
#include "clockapp.h"

// include/config.h must be added by the user.
// It may contain sensitive data that
// should not stored in source control
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
    res = wm.autoConnect("ResistorClock", "Ohms Law");

    if (!res)
    {
        Serial.println("Failed to connect");
        delay(3000);
        ESP.restart();
    } 
    else
    {
        Serial.println("Connected to wireless network");
    }

    ota_setup(HOST_NAME, OTA_PASSWORD);
    Serial.println("Clock Sketch Setup");

    app.start();
    Serial.println("Clock Sketch Running");
    last = millis();
}

void loop()
{
    ota_onLoop();
    app.on_loop();
    auto t = millis();
    if (t - last > 3000)
    {
        Serial.print('.');
        last = t;
    }
}