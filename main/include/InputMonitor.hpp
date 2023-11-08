#ifndef INPUT_MONITOR_H
#define INPUT_MONITOR_H

#include <vector>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Button.hpp"
#include "Logger.hpp"
#include "OS.hpp"

class InputMonitor
{
private:
    static Logger *log;
    std::vector<Button *> buttons;
    
    void monitorInput();
public:
    InputMonitor(std::vector<Button *> buttons);
    InputMonitor(const InputMonitor &) = delete;
    
    void start();
};
#endif