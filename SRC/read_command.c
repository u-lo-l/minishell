#include "../INC/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

t_input *read_command(const char *promt)
{
	t_input	*input;

	input = ft_calloc(1, sizeof(t_input));
	input->cmd = readline(promt);
	if (input->cmd == NULL)
	{
		rl_on_new_line();
		printf("\033[1A");
		rl_redisplay();
		printf("exit\n");
		exit (0);
	}
	else
	{
		add_history(input->cmd);
		printf("%s\n", input->cmd);
	}
	return (input);
}


