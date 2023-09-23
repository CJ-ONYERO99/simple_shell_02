#ifndef ORION_SHELL_H
#define ORION_SHELL_H

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

/* PROTOTYPES */
int is_orion_interactive(void);
void initiate_orion_interactive(void);
void initiate_orion_non_interactive(void);
char **parse_command_input(char *command_input, char *orion_separator);
void perform_actions(char **parsed_arguments);
char *get_command_path(char *command);
char *orion_implode(char **splitted_tokens, char *needle);
void execute_orion_command(char **parsed_command);
char *orion_read_lines(void);
int orion_is_white_space(char *input_string);
char *orion_str_tokenizer(char *input_string, const char *separator);
int orion_echo(char **parsed_commands);
int is_orion_path_available(char *full_command_path);
int orion_write_error(char *imploded_command);
void orion_free_command_memory(char **parsed_command);
void orion_do_system_call(char *command_to_execute, char **parsed_arguments);
void orion_handle_file(char *file_name);
void orion_process_file(char *file_name);

/* ORION_BUILT_IN_FUNCTIONS */
int orion_exit(char **parsed_command);
int orion_env(char **parsed_command);
int orion_cd(char **parsed_command);

extern char **environ;
char *orion_shell_name;

typedef int (*Command)(char **args);

/**
 * struct built_in - basic info
 * @name: name of command
 * @command: pointer to command
 */
typedef struct built_in
{
	char *name;
	Command command;
} BuiltIn;

#endif /* ORION_SHELL_H */

