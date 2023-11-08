#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <vector>
#include <string>

#include "ssd1306.h"

#include "Logger.hpp"
#include "OS.hpp"
#include "Screen.hpp"

class Display
{
private:
    static Logger *log;
    
    ssd1306_handle_t ssd1306;
    Screen *screen;
    
    void manageDisplay();
    void draw();

public:
    Display();
    ~Display() {};
    Display(const Display &) = delete;

    void show(Screen *screen);
    bool isShown(Screen *screen);

    void startDisplayManager();
};

#endif