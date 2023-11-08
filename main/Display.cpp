#include "driver/i2c.h"

#include "freertos/FreeRTOS.h"

#include "Config.hpp"
#include "Display.hpp"
#include "Screen.hpp"
#include "StatusScreen.hpp"

Logger *Display::log = Logger::getInstance();

Display::Display()
{
    ssd1306 = ssd1306_create(I2C_NUM_0, SSD1306_I2C_ADDRESS);
}

void Display::manageDisplay()
{
    while (true)
    {
        ssd1306_clear_screen(ssd1306, 0x00);
        draw();
        ssd1306_refresh_gram(ssd1306);

        vTaskDelay(pdMS_TO_TICKS(Config::getDisplayRate()));
    }
}

void Display::show(Screen *screen)
{
    this->screen = screen;
}

bool Display::isShown(Screen *screen)
{
    return this->screen == screen;
}

void Display::draw()
{
    if (screen == nullptr)
        return;

    std::vector<Line> lines = screen->getLines();
    int yPosition = 0;
    for (int i = 0; i < lines.size(); i++)
    {
        std::string text = lines[i].getText();
        int fontSize = lines[i].getFontSize();

        ssd1306_draw_string(ssd1306, 0, yPosition, reinterpret_cast<uint8_t *>(text.data()), fontSize, 1);
        yPosition += fontSize;
    }
}

void Display::startDisplayManager()
{
    OS::start([&, this]() { this->manageDisplay(); }, "display_manager");
}
