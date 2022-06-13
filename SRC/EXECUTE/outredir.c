/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outredir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyoo <yyoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:20:06 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/13 21:22:52 by yyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int	open_outredir(t_token *tail, int outfile_fd)
{
	struct stat	buf;

	if (tail->type == e_outrdr)
	{
		if (stat(tail->text, &buf) == -1)
			outfile_fd = open(tail->text, O_CREAT | O_TRUNC | O_RDWR, 0755);
		else
			outfile_fd = open(tail->text, O_TRUNC | O_RDWR);
	}
	else if (tail->type == e_appendrdr)
	{
		if (stat(tail->text, &buf) == -1)
			outfile_fd = open(tail->text, O_CREAT | O_APPEND | O_RDWR, 0755);
		else
			outfile_fd = open(tail->text, O_APPEND | O_RDWR);
	}
	return (outfile_fd);
}

int	make_outfile(t_env *envlst, t_command *commandlst)
{
	t_token		*curr;
	int			outfile_fd;

	curr = commandlst->output_redir->head;
	while (curr)
	{
		if (ft_strlen(curr->text) == 0)
		{
			ft_putstr_fd("minishell : ", 2);
			ft_putstr_fd(curr->text, 2);
			ft_putstr_fd(": Redirection Error\n", 2);
			envlst->error = 1;
			return (1);
		}
		outfile_fd = open_outredir(curr, outfile_fd);
		close(outfile_fd);
		curr = curr->next;
	}
	return (0);
}
