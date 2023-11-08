#ifndef GROUND_CONTROL_HPP
#define GROUND_CONTROL_HPP

#include "Display.hpp"
#include "LaunchpadConnection.hpp"
#include "LaunchpadStatusEventListener.hpp"
#include "StatusScreen.hpp"
#include "MenuScreen.hpp"

class GroundControl : public LaunchpadStatusEventListener
{
private:
    Display *display;
    LaunchpadConnection *launchpad;
    StatusScreen *statusScreen;
    MenuScreen *menuScreen;

public:
    GroundControl(Display *display, LaunchpadConnection *connection);

    void onSelectButtonPress();
    void onNextButtonPress();
    virtual void onLaunchpadStatusChange(std::string status) override;
};

#endif