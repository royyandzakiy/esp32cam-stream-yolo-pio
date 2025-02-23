// App.h
#pragma once

#include <WiFi.h>
#include <esp32cam.h>
#include "RouterServer.h"
#include "credentials.h"

#define WIFI_SSID WIFI_SSID_CREDENTIALS
#define WIFI_PASS WIFI_PASS_CREDENTIALS

class App {
public:
    void setup() {
        Serial.begin(115200);
        Serial.println();

        // Initialize the camera
        if (!setupCamera()) {
            Serial.println("CAMERA FAIL");
            return;
        }

        // Connect to Wi-Fi
        if (!connectToWiFi()) {
            Serial.println("WiFi FAIL");
            return;
        }

        // Start the routerServer
        routerServer.setup();
    }

    void run() {
        routerServer.run();
    }

private:
    bool setupCamera() {
        using namespace esp32cam;
        Config cfg;
        cfg.setPins(pins::AiThinker);
        cfg.setResolution(hiRes);
        cfg.setBufferCount(2);
        cfg.setJpeg(80);
        return Camera.begin(cfg);
    }

    bool connectToWiFi() {
        WiFi.persistent(false);
        WiFi.mode(WIFI_STA);
        WiFi.begin(WIFI_SSID, WIFI_PASS);
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
        }
        Serial.print("http://");
        Serial.println(WiFi.localIP());
        return true;
    }

    // Declare static members
    static const esp32cam::Resolution loRes;
    static const esp32cam::Resolution midRes;
    static const esp32cam::Resolution hiRes;

    RouterServer routerServer;
};

// Define static members outside the class
const esp32cam::Resolution App::loRes = esp32cam::Resolution::find(320, 240);
const esp32cam::Resolution App::midRes = esp32cam::Resolution::find(350, 530);
const esp32cam::Resolution App::hiRes = esp32cam::Resolution::find(800, 600);