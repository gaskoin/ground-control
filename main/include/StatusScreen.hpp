#ifndef STATUS_SCREEN_HPP
#define STATUS_SCREEN_HPP

#include "Screen.hpp"

class StatusScreen : public Screen
{
public:
    ~StatusScreen() {}
    StatusScreen();
    StatusScreen(const StatusScreen &) = delete;

    void setLaunchpadStatus(std::string status);
};

#endif