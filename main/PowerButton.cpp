#include "driver/gpio.h"

#include <PowerButton.hpp>

PowerButton::PowerButton(Power *power, int pinNumber, std::function<void()> handler) : Button::Button(pinNumber, handler), power(power) {}

bool PowerButton::isPressed()
{
    bool isButtonPressed = getGpioLevel();
    if (isButtonPressed)
        power->resetIrqState();

    return isButtonPressed;
}
