#ifndef MENU_HPP
#define MENU_HPP

#include <functional>
#include <string>
#include <vector>

class MenuItem
{
private:
    std::string text;
    std::function<void()> actionHandler;

public:
    MenuItem(std::string text, std::function<void()> actionHandler) : text(text), actionHandler(actionHandler) {};
    ~MenuItem() {};

    std::string getText() { return text; }
    void performAction() { actionHandler(); }
};

class Menu
{
private:
    std::vector<MenuItem> menuItems;

public:
    Menu() {};
    ~Menu() {};

    void add(const MenuItem &menuItem) { menuItems.push_back(std::move(menuItem)); }
    std::vector<MenuItem> getMenuItems() { return menuItems; }
};

#endif