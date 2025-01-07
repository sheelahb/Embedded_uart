#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>

// Define sShellCommand structure
typedef struct ShellCommand {
  const char *command;
  int (*handler)(int argc, char *argv[]);
  const char *help;
} sShellCommand;

extern const sShellCommand *const g_shell_commands;
extern const size_t g_num_shell_commands;


typedef struct ShellImpla {
  //! Function to call whenever a character needs to be sent out.
  int (*send_char)(char c);
} sShellImpl;

//! Initializes the demo shell. To be called early at boot.
void shell_boot(const sShellImpl *impl);

//! Prints a line then a newline
void shell_put_line(const char *str);
//void shell_boot(sShellImpl *impl);
void shell_receive_char(char c);
void shell_put_line(const char *line);
void shell_putc(char c);
int shell_help_handler(int argc, char *argv[]);

#endif  // SHELL_H
