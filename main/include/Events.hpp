#ifndef EVENTS_H
#define EVENTS_H

#include <cstdint>
#include <string>
#include <map>
#include <vector>

enum class EventId
{
    ACK,
    BROADCAST,
    PAIR,
    HEALTH_CHECK
};

typedef struct
{
    EventId eventId;
    uint8_t address[6];

    const std::vector<uint8_t> getAddress()
    {
        return std::vector<uint8_t>(address, address + 6);
    }
} PairEvent;

enum class LaunchStatus
{
    IDLE,
    CHARGED,
    ARMED,
    IGNITION
};

typedef struct
{
    EventId eventId;
    uint16_t batteryVoltage;
    LaunchStatus status;

    const std::string getStatusString()
    {
        std::map<LaunchStatus, std::string> statusMap = {
            {LaunchStatus::IDLE, "Idle"},
            {LaunchStatus::CHARGED, "Charged"},
            {LaunchStatus::ARMED, "Armed"},
            {LaunchStatus::IGNITION, "Ignition"}
        };

        return statusMap[status];
    }
} HealthCheckEvent;

enum class OutboundEventId
{
    BROADCAST,
    ARM,
    START_IGNITION,
    ABORT
};

typedef struct
{
    OutboundEventId eventId;
    uint8_t address[6];
} BroadcastEvent;

typedef struct
{
    OutboundEventId eventId;
} ArmEvent;

typedef struct
{
    OutboundEventId eventId;
    uint16_t delay;
} IgniteEvent;

typedef struct
{
    OutboundEventId eventId;
} AbortEvent;

#endif