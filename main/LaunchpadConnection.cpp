#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Config.hpp"
#include "Display.hpp"
#include "LaunchpadConnection.hpp"

static const char *TAG = "LaunchpadConnection";
static const std::string LOW_BATTERY = "Low Battery";
static const std::string INACTIVE = "Inactive";
Logger *LaunchpadConnection::log = Logger::getInstance();

LaunchpadConnection::LaunchpadConnection(EventDispatcher *eventDispatcher, Communication *communication)
{
    this->communication = communication;

    eventDispatcher->appendListener<HealthCheckEvent>(
        EventId::HEALTH_CHECK, [&, this](HealthCheckEvent *event) { this->onHealthCheck(event); }
    );

    eventDispatcher->appendListener<PairEvent>(
        EventId::PAIR, [&, this](PairEvent *event) { this->communication->connect(event->getAddress()); }
    );
}

bool LaunchpadConnection::isConnected()
{
    uint32_t timePassedSinceLastHealthCheck = OS::currentTime() - lastHealthCheckTime;
    return timePassedSinceLastHealthCheck < Config::getAllowedLaunchpadInactivityPeriod();
}

void LaunchpadConnection::onHealthCheck(HealthCheckEvent *event)
{
    lastHealthCheckTime = OS::currentTime();

    std::string status = event->getStatusString();
    if (event->batteryVoltage < Config::getLowBatteryVoltage())
        status = LOW_BATTERY;

    if (listener != nullptr)
        listener->onLaunchpadStatusChange(status);
}

void LaunchpadConnection::sendArm()
{
    ArmEvent event = { .eventId = OutboundEventId::ARM };
    communication->sendData<ArmEvent>(&event, sizeof(ArmEvent));
}

void LaunchpadConnection::sendIgnite()
{
    IgniteEvent event = {
        .eventId = OutboundEventId::START_IGNITION,
        .delay = Config::getIgnitionDelay()
    };

    communication->sendData<IgniteEvent>(&event, sizeof(IgniteEvent));
}

void LaunchpadConnection::sendAbort()
{
    AbortEvent event = { .eventId = OutboundEventId::ABORT };
    communication->sendData<AbortEvent>(&event, sizeof(AbortEvent));
}

// TODO: We can send broadcast only when launchpad is not connected
void LaunchpadConnection::broadcast()
{
    log->info(TAG, "Starting Launchpad Broadcast");
    std::vector<uint8_t> address = communication->getLocalAddress();

    BroadcastEvent broadcastEvent;
    broadcastEvent.eventId = OutboundEventId::BROADCAST;
    std::copy(address.begin(), address.end(), broadcastEvent.address);

    while (true)
    {
        log->info(TAG, "Sending broadcast");
        communication->broadcast<BroadcastEvent>(&broadcastEvent, sizeof(BroadcastEvent));
        vTaskDelay(pdMS_TO_TICKS(Config::getBroadcastPeriod()));
    }
}

void LaunchpadConnection::monitorActivity()
{
    log->info(TAG, "Starting Launchpad Activity Monitor");

    while (true)
    {
        if (!isConnected() && listener != nullptr)
            listener->onLaunchpadStatusChange(INACTIVE);

        vTaskDelay(pdMS_TO_TICKS(Config::getLaunchpadInactivityMonitorPeriod()));
    }
}

void LaunchpadConnection::registerStatusChangeListener(LaunchpadStatusEventListener *listener)
{
    this->listener = listener;
}

void LaunchpadConnection::startActivityMonitor()
{
    OS::start([&, this]() { this->monitorActivity(); }, "launchpad_activity_monitor");
}

void LaunchpadConnection::startBroadcast()
{
    OS::start([&, this]() { this->broadcast(); }, "launchpad_broadcast");
}