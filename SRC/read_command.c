/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:45:29 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/11 16:07:57 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/minishell.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

t_input	*read_command(char *prompt)
{
	t_input	*input;
	char	*trimed_input;

	input = ft_calloc(1, sizeof(t_input));
	input->cmd = readline(prompt);
	if (input->cmd == NULL)
	{
		ft_putstr_fd("\033[1A", 1);
		ft_putstr_fd(prompt, 1);
		ft_putstr_fd("exit\n", 1);
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
