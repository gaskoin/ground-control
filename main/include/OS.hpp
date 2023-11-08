#ifndef OS_H
#define OS_H

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include <functional>

class OS
{
private:
    static void task(void *parameters)
    {
        std::function<void(void)> *handler = static_cast<std::function<void(void)> *>(parameters);
        (*handler)();
    }

public:
    static void start(std::function<void()> handler, const char *name)
    {
        xTaskCreate(OS::task, name, 4096, &handler, 4, nullptr);
    }

    static uint32_t currentTime()
    {
        return pdTICKS_TO_MS(xTaskGetTickCount());
    }
};

#endif