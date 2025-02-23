#pragma once

#include <WebServer.h>
#include <functional>
#include <map>

class Router {
public:
    using Handler = std::function<void()>;

    void addRoute(const String& path, Handler handler) {
        routes[path] = handler;
    }

    void setupRoutes(WebServer& server) {
        for (const auto& route : routes) {
            server.on(route.first.c_str(), route.second);
        }
    }

private:
    std::map<String, Handler> routes;
};