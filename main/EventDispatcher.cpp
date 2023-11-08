#include <string>

#include "EventDispatcher.hpp"

#include "esp_now.h"

static const char *TAG = "EventDispatcher";
Logger *EventDispatcher::log = Logger::getInstance();

EventDispatcher::EventDispatcher() {}

void EventDispatcher::dispatch(const uint8_t *data, int length)
{
    EventId eventId = static_cast<EventId>(data[0]);
    if (handlers.find(eventId) != handlers.end())
    {
        FunctionsVector functions = handlers.at(eventId);
        for (auto handler: functions)
            handler(data);
    }
    else
        log->warning(TAG, "No handler registered for eventId '%d'", eventId);
}