// Color.h

#ifndef _color_h
#define _color_h

#include <iostream>
using namespace std;

const std::string color_def_start("\033[0");
const std::string black(";30");
const std::string red(";31");
const std::string green(";32");
const std::string yellow(";33");
const std::string blue(";34");
const std::string magenta(";35");
const std::string cyan(";36");
const std::string white(";37");
const std::string bg_black(";40");
const std::string bg_red(";41");
const std::string bg_green(";42");
const std::string bg_yellow(";43");
const std::string bg_blue(";44");
const std::string bg_magenta(";45");
const std::string bg_cyan(";46");
const std::string bg_white(";47");
const std::string color_def_end("m");
const std::string reset("\033[0m");

// print a character with color
void fgColorPrint(char message,char color);
void fgColorPrint_plus(char message,char color);


#endif
