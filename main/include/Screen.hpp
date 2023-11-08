#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <string>
#include <vector>

#define FONT_SIZE_12 12
#define FONT_SIZE_16 16

#define MAX_LINE_WIDTH_16 16
#define MAX_LINE_WIDTH_12 21

class Line
{
private:
    std::string text;
    int fontSize;

public:
    Line(std::string text, int fontSize) : text(text), fontSize(fontSize) {}
    ~Line() {}

    void setText(std::string text) { this->text = text; }
    std::string getText() { return text; }
    int getFontSize() { return fontSize; }
};

class Screen
{
protected:
    std::vector<Line> lines;

public:
    ~Screen() {}
    Screen() {}

    std::vector<Line> getLines() { return lines; }
};

#endif