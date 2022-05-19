#include "../INC/minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

char *read_command(const char *promt)
{
	char *command_line;

	command_line = readline(promt);
	if (command_line == NULL)
	{
		rl_on_new_line();
		printf("\033[1A");
		rl_redisplay();
		printf("exit\n");
		exit (0);
	}
	else
	{
		add_history(command_line);
		printf("%s\n", command_line);
	}
	return (command_line);
}


