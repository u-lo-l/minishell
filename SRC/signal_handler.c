/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:45:25 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/13 13:29:19 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/minishell.h"
#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_on_new_line();
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

int	set_signal_handler(void)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		return (FALSE);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (FALSE);
	return (TRUE);
}

void	pipe_heredoc_sighandler(int signo)
{
	if (signo == SIGINT)
		ft_putstr_fd("^C\n", 1);
	exit (1);
}