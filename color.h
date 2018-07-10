#ifndef _COLOR_H_
#define _COLOR_H_

#define ANSI_COLOR_BLACK    "\x1b[30m"
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_WHITE    "\x1b[37m"
#define ANSI_COLOR_LBLACK   "\x1b[90m"
#define ANSI_COLOR_LRED     "\x1b[91m"
#define ANSI_COLOR_LGREEN   "\x1b[92m"
#define ANSI_COLOR_LYELLOW  "\x1b[93m"
#define ANSI_COLOR_LBLUE    "\x1b[94m"
#define ANSI_COLOR_LMAGENTA "\x1b[95m"
#define ANSI_COLOR_LCYAN    "\x1b[96m"
#define ANSI_COLOR_LWHITE   "\x1b[97m"

#define ANSI_BOLD   "\x1b[1m"
#define ANSI_RESET  "\x1b[0m"


#define COLOR(color, ...) \
    ANSI_COLOR_ ## color __VA_ARGS__ ANSI_RESET

#define BOLD(...) \
    ANSI_BOLD __VA_ARGS__ ANSI_RESET

#define COLOR_BOLD(color, ...) \
    ANSI_COLOR_ ## color ANSI_BOLD __VA_ARGS__ ANSI_RESET

#endif
