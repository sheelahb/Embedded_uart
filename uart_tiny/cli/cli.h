#ifndef CLI_H
#define CLI_H

#define CLI_MAX_COMMANDS 10
#define CLI_MAX_ARGS 5
#define CLI_INPUT_BUFFER_SIZE 100

typedef int (*CommandHandler)(int argc, char *argv[]);

typedef struct {
    const char *name;
    const char *description;
    CommandHandler handler;
} Command;

void cli_init();
void cli_register_command(const char *name, const char *description, CommandHandler handler);
void cli_process_input(const char *input);
void cli_list_commands();

#endif // CLI_H
