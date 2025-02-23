// Server.h
#pragma once

#include <WebServer.h>
#include <esp32cam.h>
#include "Router.h"
#include <functional>

class RouterServer {
public:
    RouterServer() : server(80) {}

    void setup() {
        // Set up routes using std::bind
        router.addRoute("/cam-lo.jpg", std::bind(&RouterServer::handleJpg, this, loRes));
        router.addRoute("/cam-hi.jpg", std::bind(&RouterServer::handleJpg, this, hiRes));
        router.addRoute("/cam-mid.jpg", std::bind(&RouterServer::handleJpg, this, midRes));
        router.addRoute("/hello", std::bind(&RouterServer::handleHello, this));

        // Start the server
        server.begin();
    }

    void run() {
        server.handleClient();
    }

private:
    void handleJpg(const esp32cam::Resolution& resolution) {
        if (!esp32cam::Camera.changeResolution(resolution)) {
            Serial.println("SET-RES FAIL");
        }
        serveJpg();
    }

    void serveJpg() {
        auto frame = esp32cam::capture();
        if (frame == nullptr) {
            Serial.println("CAPTURE FAIL");
            server.send(503, "", "");
            return;
        }
        Serial.printf("CAPTURE OK %dx%d %db\n", frame->getWidth(), frame->getHeight(),
                      static_cast<int>(frame->size()));

        server.setContentLength(frame->size());
        server.send(200, "image/jpeg");
        WiFiClient client = server.client();
        frame->writeTo(client);
    }

    void handleHello() {
        Serial.println("HELLO");
        server.send(200, "text/plain", "Hello from ESP32-CAM");
    }

    WebServer server;
    Router router;

    // Declare static members
    static const esp32cam::Resolution loRes;
    static const esp32cam::Resolution midRes;
    static const esp32cam::Resolution hiRes;
};

// Define static members outside the class
const esp32cam::Resolution RouterServer::loRes = esp32cam::Resolution::find(320, 240);
const esp32cam::Resolution RouterServer::midRes = esp32cam::Resolution::find(350, 530);
const esp32cam::Resolution RouterServer::hiRes = esp32cam::Resolution::find(800, 600);