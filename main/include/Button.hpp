#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>

class Button
{
private:
    std::function<void()> handler;
    bool wasPressedBefore;

protected:
    int pinNumber;

    bool getGpioLevel();
public:
    Button(int pinNumber, std::function<void()> handler);
    ~Button(){};

    virtual bool isPressed();
    void handle();
};

#endif
