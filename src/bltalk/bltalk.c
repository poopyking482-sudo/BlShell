#include <stdio.h>
#include <string.h>

// ---------------------------------------------------------
// THE PRINT FUNCTION
// ---------------------------------------------------------
void yourPrintCode(const char* argument) {
    printf("%s\n", argument);
}

// ---------------------------------------------------------
// MAIN COMMAND ENTRY POINT
// ---------------------------------------------------------
int main(int argc, char* argv[]) {
    // 1. Check if an argument exists
    if (argc < 2) {
        printf("error: bltalk cannot call!\n");
        return 0; // just stops the program here and drops back to the shell
    }

    char* arg = argv[1];
    size_t len = strlen(arg);

    // 2. verify syntax rules (< and >)
    if (arg[0] == '<' && arg[len - 1] == '>') {
        
        // jumps past the opening '<'
        char* cleanStart = arg + 1;
        
        // snips off the trailing '>'
        arg[len - 1] = '\0';

        // 3. run the print logic
        yourPrintCode(cleanStart);
        
    } else {
        // if syntax is wrong
        printf("error: bltalk cannot call!\n");
    }
    
    // naturally drops out of the application and returns control to the shell
}
