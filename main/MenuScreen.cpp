#include "MenuScreen.hpp"

MenuScreen::MenuScreen(Menu &menu) : currentItemIndex(0)
{
    menuItems = menu.getMenuItems();
    refreshMenu();
}

void MenuScreen::refreshMenu()
{
    lines.clear();
    lines.push_back(Line("", FONT_SIZE_12));
    for (int i = 0; i < menuItems.size(); i++)
    {
        MenuItem item = menuItems[i];

        std::string text = item.getText();
        if( currentItemIndex == i)
            text = "> " + text;
        else
            text = "  " + text;

        lines.push_back(Line(text, FONT_SIZE_12));
    }
}

void MenuScreen::next()
{
    int numberOfItems = menuItems.size();
    if (++currentItemIndex >= numberOfItems)
        currentItemIndex = 0;

    refreshMenu();
}

void MenuScreen::select()
{
    menuItems[currentItemIndex].performAction();
    currentItemIndex = 0;

    refreshMenu();
}