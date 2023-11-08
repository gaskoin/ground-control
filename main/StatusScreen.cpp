#include "StatusScreen.hpp"
#include "utils/StringUtils.hpp"

static const int STATUS_LINE = 0;
static const int TITLE_LINE = 1;
static const int LAUNCHPAD_STATUS_LINE = 2;

StatusScreen::StatusScreen()
{
    lines = {
        Line("", FONT_SIZE_12),
        Line(" Ground-Control ", FONT_SIZE_16),
        Line("", FONT_SIZE_12)
    };
}

void StatusScreen::setLaunchpadStatus(std::string status)
{
    std::string line = "Launchpad";
    int paddingSize = MAX_LINE_WIDTH_12 - status.length();
    lines[LAUNCHPAD_STATUS_LINE].setText(StringUtils::padRight(line, paddingSize, '.') + status);
}