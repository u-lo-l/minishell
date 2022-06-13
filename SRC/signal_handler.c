/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:45:25 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/13 13:52:36 by dkim2            ###   ########.fr       */
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

static void	heredoc_sighandler(int signo)
{
	if (signo == SIGINT)
		ft_putstr_fd("\033[1;32m > \033[0m\n", 1);
	exit (1);
}

int	set_signal_handler(void)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		return (FALSE);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (FALSE);
	return (TRUE);
}

int	set_signal_both(void *sig_handler)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		return (FALSE);
	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
		return (FALSE);
	return (TRUE);
}

int	set_heredoc_signal(void)
{
	if (signal(SIGINT, heredoc_sighandler) == SIG_ERR)
		return (FALSE);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (FALSE);
	return (TRUE);
}
