#include "../../INC/minishell.h"
#include <stdio.h>
#include <stdlib.h>

char	*word_expansion(t_input	*input, t_env *env_list)
{
	char	*key;
	char	*value;

	while (TRUE)
	{
		if (input->cmd[input->curr_i] == ' ' || \
			input->cmd[input->curr_i] == '\t' || \
			input->cmd[input->curr_i] == '\0')
		{
			key = ft_strndup(input->cmd + input->start_i, \
				input->curr_i - input->start_i);
			break ;
		}
		input->curr_i++;
	}
	value = get_env_value(env_list, key);
	free(key);
	return (value);
}

int main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	char	*val;

	if (argc != 1 || argv == NULL || envp == NULL)
		return (1);
	env_list = make_env_list(envp);
	if (env_list == NULL)
		return (1);
	// display_env(env_list);
	// val = word_expansion(env_list, "PATH");
	val = get_env_value(env_list, "?");
	printf("<%s>\n", val);
	return (0);
}