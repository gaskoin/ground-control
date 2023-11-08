#include "driver/gpio.h"

#include <Button.hpp>

Button::Button(int pinNumber, std::function<void()> handler) : handler(handler), pinNumber(pinNumber)
{
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = (1ULL << pinNumber);
    io_conf.mode = GPIO_MODE_INPUT;
    gpio_config(&io_conf);
}

void Button::handle()
{
    this->handler();
}

bool Button::getGpioLevel()
{
    return 1 - gpio_get_level((gpio_num_t)pinNumber);
}

bool Button::isPressed()
{
    bool isPressed = getGpioLevel();
    bool value = isPressed && !wasPressedBefore;
    this->wasPressedBefore = isPressed;

    return value;
}