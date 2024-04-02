// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// License:    GPL
// Author:     Brian K Preston
// File Name:  no file name
// Build Date: Mon Apr  1 11:26:33 PM CDT 2024
// Version:    3.6.7

#ifndef _BASH_COLOR_HPP
#define _BASH_COLOR_HPP

#include <iostream>

using std::string;

// shell color constants
const string FMT_RESET             = "\033[0m";
const string FMT_RESET_BOLD        = "\033[21m";
const string FMT_RESET_DIM         = "\033[22m";
const string FMT_RESET_UNDERLINE   = "\033[24m";
const string FMT_RESET_BLINK       = "\033[25m"; 
const string FMT_RESET_REVERSE     = "\033[27m";
const string FMT_RESET_HIDDEN      = "\033[28m";
const string FMT_BOLD              = "\033[1m";
const string FMT_DIM               = "\033[2m";
const string FMT_UNDERLINE         = "\033[4m";
const string FMT_BLINK             = "\033[5m";
const string FMT_REVERSE           = "\033[7m";
const string FMT_HIDDEN            = "\033[8m";
const string FMT_FG_DEFUALT        = "\033[39m";        
const string FMT_FG_RED            = "\033[31m";
const string FMT_FG_GREEN          = "\033[32m";
const string FMT_FG_YELLOW         = "\033[33m";
const string FMT_FG_BLUE           = "\033[34m";
const string FMT_FG_MAGENTA        = "\033[35m";
const string FMT_FG_CYAN           = "\033[36m";
const string FMT_FG_LIGHT_GREY     = "\033[37m";
const string FMT_FG_DARK_GREY      = "\033[90m";
const string FMT_FG_LIGHT_RED      = "\033[91m";
const string FMT_FG_LIGHT_GREEN    = "\033[92m";
const string FMT_FG_LIGHT_YELLOW   = "\033[93m";
const string FMT_FG_LIGHT_BLUE     = "\033[94m";
const string FMT_FG_LIGHT_MAGENTA  = "\033[95m";
const string FMT_FG_LIGHT_CYAN     = "\033[96m";
const string FMT_FG_WHITE          = "\033[97m";
const string FMT_BG_DEFUALT        = "\033[49m";
const string FMT_BG_BLACK          = "\033[40m";
const string FMT_BG_RED            = "\033[41m";
const string FMT_BG_GREEN          = "\033[42m";
const string FMT_BG_YELLOW         = "\033[43m";
const string FMT_BG_BLUE           = "\033[44m";
const string FMT_BG_MAGENTA        = "\033[45m";
const string FMT_BG_CYAN           = "\033[46m";
const string FMT_BG_DARK_GREY      = "\033[100m";
const string FMT_BG_LIGHT_RED      = "\033[101m";
const string FMT_BG_LIGHT_GREEN    = "\033[102m";
const string FMT_BG_LIGHT_YELLOW   = "\033[103m";
const string FMT_BG_LIGHT_BLUE     = "\033[104m";
const string FMT_BG_LIGHT_MAGENTA  = "\033[105m";
const string FMT_BG_LIGHT_CYAN     = "\033[106m";
const string FMT_BG_WHITE          = "\033[107m";


#endif

