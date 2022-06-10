/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outredir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:20:06 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/10 17:18:20 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void	push_outfile(int outfile_fd, int *red_fd)
{
	char	*buf;
	int		r;

	buf = malloc(sizeof(char *) * 1);
	r = 1;
	while (r > 0)
	{
		r = read(red_fd[0], buf, 1);
		if (r < 1)
			break ;
		write(outfile_fd, buf, 1);
	}
	free(buf);
}

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

void	make_outfile(t_command *commandlst)
{
	t_token		*curr;
	struct stat	buf;
	int			outfile_fd;

	curr = commandlst->output_redir->head;
	while (curr)
	{
		if (stat(curr->text, &buf) == -1)
			outfile_fd = open(curr->text, O_CREAT | O_TRUNC | O_RDWR, 0755);
		else
			outfile_fd = open(curr->text, O_TRUNC | O_RDWR);
		close(outfile_fd);
		curr = curr->next;
	}
}

void	do_outredir(t_command *commandlst, int *red_fd)
{
	t_token		*curr;
	int			outfile_fd;

	outfile_fd = 0;
	close(red_fd[1]);
	close(1);
	curr = commandlst->output_redir->tail;
	outfile_fd = open_outredir(curr, outfile_fd);
	if ((commandlst->input_redir->num_of_tokens == 0) \
		|| (commandlst->input_redir->num_of_tokens > 0 \
		&& commandlst->output_redir->tail->type == 2))
		push_outfile(outfile_fd, red_fd);
}
