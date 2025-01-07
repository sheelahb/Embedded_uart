#include "cli.h"
#include "uart.h"
#include <string.h>
#include <stdio.h>

static Command cli_commands[CLI_MAX_COMMANDS];
static int cli_command_count = 0;

// Initialize the CLI
void cli_init() {
    cli_command_count = 0;
}

// Register a command
void cli_register_command(const char *name, const char *description, CommandHandler handler) {
    if (cli_command_count >= CLI_MAX_COMMANDS) {
        console_puts("Error: Command limit reached\n");
        return;
    }

    cli_commands[cli_command_count].name = name;
    cli_commands[cli_command_count].description = description;
    cli_commands[cli_command_count].handler = handler;
    cli_command_count++;
}

// List all registered commands
void cli_list_commands() {
    console_puts("Available Commands:\n");
    for (int i = 0; i < cli_command_count; i++) {
        console_puts("  ");
        console_puts(cli_commands[i].name);
        console_puts(" - ");
       console_puts(cli_commands[i].description);
        console_puts("\n");
    }
}

// Process input
void cli_process_input(const char *input) {
    char buffer[CLI_INPUT_BUFFER_SIZE];
    strncpy(buffer, input, CLI_INPUT_BUFFER_SIZE - 1);
    buffer[CLI_INPUT_BUFFER_SIZE - 1] = '\0'; // Ensure null-termination

    // Tokenize input
    char *argv[CLI_MAX_ARGS];
    int argc = 0;
    char *token = strtok(buffer, " ");
    while (token != NULL && argc < CLI_MAX_ARGS) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    if (argc == 0) return; // No input

    // Match command
    for (int i = 0; i < cli_command_count; i++) {
        if (strcmp(argv[0], cli_commands[i].name) == 0) {
            cli_commands[i].handler(argc, argv);
            return;
        }
    }

    console_puts("Error: Unknown command\n");
}
