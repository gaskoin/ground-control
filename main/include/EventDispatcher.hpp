#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include <functional>
#include <map>
#include <vector>

#include "Events.hpp"
#include "Logger.hpp"

class EventDispatcher
{
private:
    typedef std::vector<std::function<void(const uint8_t *)>> FunctionsVector;
    static Logger *log;

    std::map<EventId, FunctionsVector> handlers;

public:
    EventDispatcher();
    ~EventDispatcher(){};

    template <typename T>
    void appendListener(EventId eventId, std::function<void(T *)> handler)
    {
        std::function<void(const uint8_t *)> handlerWrapper = [handler](const uint8_t *rawData)
        {
            T *parameter = const_cast<T *>(reinterpret_cast<const T *>(rawData));
            handler(parameter);
        };

        if (handlers.find(eventId) == handlers.end())
            handlers[eventId] = FunctionsVector();
        handlers[eventId].push_back(handlerWrapper);
    }

    void dispatch(const uint8_t *data, int length);
};

#endif
