/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyoo <yyoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:20:00 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/08 14:44:01 by yyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <sys/wait.h>
#include <stdlib.h>

int	pipe_here_doc(t_command *command, int *std_fd)
{
	t_token		*curr;
	int			fd[2];

	curr = command->here_doc->head;
	dup2(std_fd[0], 0);
	dup2(std_fd[1], 1);
	while (curr)
	{
		pipe(fd);
		read_here_doc(curr, fd);
		close(fd[1]);
		curr = curr->next;
	}
	dup2(fd[0], 0);
	if (command->input_redir->num_of_tokens > 0)
	{
		if (check_infile(command->input_redir))
			return (1);
	}
	return (0);
}

int	pipe_util1(t_env *envlst, t_token_tree *toktree, t_command *curr, t_fd *fd)
{
	if (curr->here_doc->num_of_tokens > 0)
	{
		if (pipe_here_doc(curr, fd->std_fd))
			return (1);
	}
	if (curr->input_redir->num_of_tokens > 0 \
		&& curr->here_doc->num_of_tokens == 0)
	{
		if (do_inredir(curr->input_redir))
			return (1);
	}
	if (toktree->tail_cmd != curr)
		dup2(fd->pipe_fd2[1], 1);
	if (curr->output_redir->num_of_tokens > 0)
		make_outfile(curr);
	if (curr->simple_command->num_of_tokens > 0)
		check_builtin(envlst, curr->simple_command, toktree->num_of_commands);
	if (curr->simple_command->num_of_tokens == 0)
		exit(1);
	return (0);
}

int	do_pipe(t_env *envlst, t_token_tree *toktree, t_command *curr, t_fd *fd)
{
	int	pid;
	int	status;

	status = 0;
	pipe(fd->pipe_fd2);
	dup2(fd->pipe_fd1[1], 1);
	pid = fork();
	if (pid == 0)
	{
		close(fd->pipe_fd2[0]);
		if (curr->next_cmd == NULL && curr->output_redir->num_of_tokens == 0)
			dup2(fd->std_fd[1], 1);
		if (pipe_util1(envlst, toktree, curr, fd))
			return (1);
	}
	else
	{
		close(fd->pipe_fd2[1]);
		wait(&status);
		if (curr->output_redir->num_of_tokens > 0)
			do_outredir(curr, fd->pipe_fd2);
	}
	dup2(fd->pipe_fd1[0], 0);
	return (0);
}

void	copy_std_fd(t_fd *fd)
{
	fd->std_fd[0] = dup(0);
	fd->std_fd[1] = dup(1);
}
