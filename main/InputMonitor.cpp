#include <functional>
#include <vector>
#include <utility>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Config.hpp"
#include "InputMonitor.hpp"

static const char *TAG = "InputMonitor";
Logger *InputMonitor::log = Logger::getInstance();

InputMonitor::InputMonitor(std::vector<Button *> buttons) : buttons(buttons) {}

void InputMonitor::monitorInput()
{
    log->info(TAG, "Starting Input Monitor");

    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(Config::getInputMonitorPeriod()));

        for (Button *button : buttons)
        {
            if (button->isPressed())
                button->handle();
        }
    }
}

void InputMonitor::start()
{
    OS::start([&, this]() { this->monitorInput(); }, "input_monitor");
}