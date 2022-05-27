/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:45:29 by dkim2             #+#    #+#             */
/*   Updated: 2022/05/27 14:33:33 by dkim2            ###   ########.fr       */
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
	char	 *trimed_input;
	
	input = ft_calloc(1, sizeof(t_input));
	input->cmd = readline(promt);
	if (input->cmd == NULL)
	{
		printf("\b\bexit\n");
		free(input);
		return (NULL);
	}
	else
	{
		add_history(input->cmd);
		printf("\033[33minput : %s\033[0m\n", input->cmd);
		trimed_input = ft_strtrim(input->cmd, "\t ");
		free(input->cmd);
		input->cmd = trimed_input;
	}
	return (input);
}
