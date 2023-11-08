#include "drivers/I2C.hpp"

#include "Button.hpp"
#include "PowerButton.hpp"
#include "Communication.hpp"
#include "Display.hpp"
#include "EventDispatcher.hpp"
#include "LaunchpadConnection.hpp"
#include "GroundControl.hpp"
#include "InputMonitor.hpp"
#include "Power.hpp"

extern "C" void app_main(void)
{
    I2C::init();
    Power *power = Power::init();

    Display *display = new Display();
    EventDispatcher *eventDispatcher = new EventDispatcher();
    Communication *communication = Communication::init(eventDispatcher);

    LaunchpadConnection *connection = new LaunchpadConnection(eventDispatcher, communication);
    GroundControl *groundControl = new GroundControl(display, connection);

    std::vector<Button *> buttons = {
        new Button(GPIO_NUM_38, [&, groundControl](){ groundControl->onSelectButtonPress(); }),
        new PowerButton(power, GPIO_NUM_35, [&, groundControl](){ groundControl->onNextButtonPress(); })
    };
    InputMonitor *inputMonitor = new InputMonitor(buttons);

    inputMonitor->start();
    connection->registerStatusChangeListener(groundControl);
    connection->startActivityMonitor();
    connection->startBroadcast();
    display->startDisplayManager();
}