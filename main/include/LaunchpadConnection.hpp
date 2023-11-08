#ifndef LaunchpadConnection_H
#define LaunchpadConnection_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Communication.hpp"
#include "EventDispatcher.hpp"
#include "LaunchpadStatusEventListener.hpp"
#include "Logger.hpp"
#include "OS.hpp"

class LaunchpadConnection
{
private:
    static Logger *log;

    Communication *communication;
    uint32_t lastHealthCheckTime;
    LaunchpadStatusEventListener *listener;

    void broadcast();
    void monitorActivity();
    void onHealthCheck(HealthCheckEvent *event);
    bool isConnected();

public:
    LaunchpadConnection(EventDispatcher *eventDispatcher, Communication *communication);
    LaunchpadConnection(const LaunchpadConnection &) = delete;

    void registerStatusChangeListener(LaunchpadStatusEventListener *listener);

    void startActivityMonitor();
    void startBroadcast();
    void sendArm();
    void sendIgnite();
    void sendAbort();
};
#endif