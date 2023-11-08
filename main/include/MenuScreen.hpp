#ifndef MENU_SCREEN_HPP
#define MENU_SCREEN_HPP

#include "Screen.hpp"
#include "menu/Menu.hpp"

class MenuScreen : public Screen
{
private:
    uint8_t currentItemIndex;
    std::vector<MenuItem> menuItems;

    void refreshMenu();
public:
    MenuScreen(Menu &menu);
    ~MenuScreen() {}
    MenuScreen(const MenuScreen &) = delete;

    void next();
    void select();
};

#endif