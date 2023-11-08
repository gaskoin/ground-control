#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <cstdint>
#include <vector>

#include "esp_mac.h"
#include "esp_now.h"

#include "EventDispatcher.hpp"
#include "Logger.hpp"
#include "OS.hpp"

#define ADDRESS_SIZE 6

static const std::vector<uint8_t> BROADCAST_MAC {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

class Communication
{
private:
    constexpr static char const *TAG = "Communication";
    static Logger *log;

    std::vector<uint8_t> peerAddress;

    Communication(EventDispatcher *eventDispatcher);
    ~Communication(){};

    void nvsInit();
    void wifiInit();
    void espnowInit();

    bool isBroadcast(std::vector<uint8_t> address);

    template <typename T>
    void sendToAddress(std::vector<uint8_t> address, T *data, int size)
    {
        uint8_t *rawData = reinterpret_cast<uint8_t *>(data);
        log->info(Communication::TAG, "Sending eventId = '%d' to %02x:%02x:%02x:%02x:%02x:%02x", rawData[0], MAC2STR(address.data()));
        esp_now_send(address.data(), rawData, size);
    }

public:
    static Communication *init(EventDispatcher *EventDispatcher);

    void connect(const std::vector<uint8_t> address);
    std::vector<uint8_t> getLocalAddress();

    template <typename T>
    void broadcast(T *data, int size)
    {
        sendToAddress(BROADCAST_MAC, data, size);
    }

    template <typename T>
    void sendData(T *data, int size)
    {   
        sendToAddress(peerAddress, data, size);
    }
};

#endif