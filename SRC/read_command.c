/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:45:29 by dkim2             #+#    #+#             */
/*   Updated: 2022/05/26 16:57:31 by dkim2            ###   ########.fr       */
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
	}
	return (input);
}
