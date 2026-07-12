#ifndef SHELL_LINK_H
#define SHELL_LINK_H

// route commands typed into the shell to their respective implementations
void route_command(const char *cmd, char **tokens);

#endif
