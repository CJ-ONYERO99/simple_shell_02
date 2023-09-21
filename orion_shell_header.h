#ifndef ORION_SHELL_HEADER_H
#define ORION_SHELL_HEADER_H

#define ORION_TOKEN_BUFFER_SIZE 64
#define ORION_MAX_BUFFER_SIZE 1024
#define ORION_TOKEN_SEPARATOR " \n\a\t\r"

/* HEADER FILES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <fcntl.h>

/* FUNCTION PROTOTYPES */
int is_orion_interactive(void);
void start_orion_interactive(void);
void start_orion_non_interactive(void);
char **orion_parse_cmd(char *input_cmd, char *separator);
void perform_orion_actions(char **parsed_args);
char *orion_get_cmd_path(char *cmd);
char *orion_implode_tokens(char **tokens, char *delimiter);
void execute_orion_cmd(char **parsed_cmd);
char *orion_read_input_lines(void);
int orion_is_whitespace(char *input_str);
char *orion_tokenize_str(char *input_str, const char *delimiter);
int orion_echo_cmd(char **parsed_cmds);
int is_orion_cmd_available(char *full_cmd_path);
int orion_write_error_msg(char *cmd_str);
void free_orion_cmd_memory(char **parsed_cmd);
void execute_orion_system_call(char *cmd_to_execute, char **parsed_args);
void handle_orion_file(char *file_name);
void process_orion_file(char *file_name);

/* ORION BUILT-IN FUNCTIONS */
int orion_exit_shell(char **parsed_cmd);
int orion_print_environment(char **parsed_cmd);
int orion_change_directory(char **parsed_cmd);

extern char **environ;
char *orion_shell_name;

typedef int (*OrionCmd)(char **args);

/**
 * struct orion_builtin - struct to define built-in commands
 * @name: name of the command
 * @command: function to execute the command
 */
typedef struct orion_builtin
{
	char *name;
	OrionCmd command;
} OrionBuiltIn;

#endif /* ORION_SHELL_HEADER_H */