#ifndef COLORS_H
#define COLORS_H

// Core ANSI Escape Strings for Formatting
#define ANSI_RESET        "\x1b[0m"
#define ANSI_BOLD         "\x1b[1m"
#define ANSI_CLEAR_SCREEN "\x1b[2J"
#define ANSI_CURSOR_HOME  "\x1b[H"

// Foreground Font Colors
#define CLR_RED     "\x1b[31m"
#define CLR_GREEN   "\x1b[32m"
#define CLR_YELLOW  "\x1b[33m"
#define CLR_BLUE    "\x1b[34m"
#define CLR_MAGENTA "\x1b[35m"
#define CLR_CYAN    "\x1b[36m"
#define CLR_WHITE   "\x1b[37m"

// Unicode Full Block Character Definition
#define BLOCK "\u2588\u2588"

// Arch-style system matrix block macro
#define PRINT_COLOR_MATRIX() \
    printf(CLR_CYAN BLOCK " " CLR_MAGENTA BLOCK " " CLR_GREEN BLOCK "\n"); \
    printf(CLR_BLUE BLOCK " " CLR_RED     BLOCK " " CLR_YELLOW BLOCK "\n" ANSI_RESET)

#endif
