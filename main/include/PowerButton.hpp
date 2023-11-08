#ifndef POWER_BUTTON_HPP
#define POWER_BUTTON_HPP

#include <Button.hpp>
#include <Power.hpp>

class PowerButton : public Button
{
private:
    Power *power;

public:
    PowerButton(Power *power, int pinNumber, std::function<void()> handler);
    ~PowerButton(){};

    virtual bool isPressed() override;
};

#endif
