/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:45:29 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/08 14:01:14 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

t_input	*read_command(const char *promt)
{
	t_input	*input;
	char	*trimed_input;

	input = ft_calloc(1, sizeof(t_input));
	input->cmd = readline(promt);
	if (input->cmd == NULL)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
//		ft_putstr_fd("\033[1A", 2);
//		rl_redisplay();
		ft_putstr_fd("exit\n", 2);
		free(input);
		input = NULL;
	}
	else
	{
		add_history(input->cmd);
		trimed_input = ft_strtrim(input->cmd, "\t ");
		free(input->cmd);
		input->cmd = trimed_input;
	}
	return (input);
}

void	check_input_state(t_input *input)
{
	int	i;

	i = 0;
	printf("str : [%s ]\n", input->cmd);
	printf(" s  : [");
	while (i <= (int)ft_strlen(input->cmd))
	{
		if (i++ == input->start_i)
			printf("\033[33ms\033[0m");
		else
			printf(" ");
	}
	i = 0;
	printf("]\n");
	printf(" c  : [");
	while (i <= (int)ft_strlen(input->cmd))
	{
		if (i == input->curr_i)
			printf("\033[34mc\033[0m");
		else
			printf(" ");
	}
	printf("]\n");
}
