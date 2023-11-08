#include "Button.hpp"
#include "PowerButton.hpp"
#include "InputMonitor.hpp"
#include "GroundControl.hpp"
#include "StatusScreen.hpp"

GroundControl::GroundControl(Display *display, LaunchpadConnection *launchpadConnection) : display(display), launchpad(launchpadConnection)
{
    Menu menu = Menu();
    menu.add(MenuItem("Abort", [&, this]() { this->launchpad->sendAbort(); }));
    menu.add(MenuItem("Arm", [&, this]() { this->launchpad->sendArm(); }));
    menu.add(MenuItem("Ignite in 10 sec", [&, this]() { this->launchpad->sendIgnite(); }));
    menu.add(MenuItem("Back", [&, this]() { this->display->show(this->statusScreen); }));

    statusScreen = new StatusScreen();
    menuScreen = new MenuScreen(menu);
    display->show(statusScreen);
}

void GroundControl::onNextButtonPress()
{
    if (display->isShown(menuScreen))
        menuScreen->next();
    else
        display->show(menuScreen);
}

void GroundControl::onSelectButtonPress()
{
    if (display->isShown(statusScreen))
    {
        display->show(menuScreen);
        return;
    }

    menuScreen->select();
    display->show(statusScreen);
}

void GroundControl::onLaunchpadStatusChange(std::string status)
{
    statusScreen->setLaunchpadStatus(status);
}

