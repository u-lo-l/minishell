/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_scanner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:32:44 by dkim2             #+#    #+#             */
/*   Updated: 2022/05/22 18:44:20 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

t_token_list	*scan_token(t_input *input, t_env *env_list)
{
	t_token_list	*toklst;
	char			*word;

	if (input == NULL || env_list == NULL)
		return (NULL);
	toklst = create_empty_toklst();
	skip_space(input);
	word = NULL;
	while (TRUE)
	{
		if (input->cmd[input->curr_i] == '\'' || \
			input->cmd[input->curr_i] == '"')
			quote_case(input, &word, env_list);
		else if (ft_strchr(" \t", input->cmd[input->curr_i]))
		{
			if (split_token(toklst, input, &word) == 0)
				break ;
		}
		else if (input->cmd[input->curr_i] == '$')
			dollar_case(input, &word, env_list);
		else
			input->curr_i++;
	}
	return (toklst);
}
/*
int main(int argc, char **argv, char **envp)
{
	t_input 		*input;
	t_env			*envs;
	t_token_list	*cmd_token_list;

	if (argc != 1 || argv == NULL || envp == NULL)
		return (0);
	envs = env_list(envp);
	while (1)
	{
		// 명령어 한 줄 읽어오기
		input = read_command("mini >>  ");
		if (input == NULL)
			break ;
		printf("input : <%s>\n", input->cmd);
		cmd_token_list = scan_token(input, envs);
		print_token_list(cmd_token_list);

		free_toklst(cmd_token_list);
		free(input->cmd);
		free(input);
	}
	free_env_list(envs);
	return (0);
}
*/