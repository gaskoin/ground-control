#ifndef LAUNCHPAD_STATUS_EVENT_LISTENER_H
#define LAUNCHPAD_STATUS_EVENT_LISTENER_H

#include <string>

class LaunchpadStatusEventListener
{
public:
    virtual ~LaunchpadStatusEventListener() {};
    virtual void onLaunchpadStatusChange(std::string status) = 0;
};

#endif