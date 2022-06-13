/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:20:00 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/13 13:03:04 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <sys/wait.h>
#include <stdlib.h>

static int	pipe_here_doc(t_env *envlst, t_command *command, int *std_fd)
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
	envlst->error = 0;
	dup2(fd[0], 0);
	if (command->input_redir->num_of_tokens > 0)
	{
		close(fd[0]);
		if (do_inredir(command, command->input_redir))
			envlst->error = 1;
	}
	return (envlst->error);
}

static int	pipe_util1(t_env *envlst, t_token_tree *toktree, \
						t_command *curr, t_fd *fd)
{
	if (curr->here_doc->num_of_tokens > 0)
	{
		if (pipe_here_doc(envlst, curr, fd->std_fd))
			return (1);
	}
	if (curr->input_redir->num_of_tokens > 0 \
		&& curr->here_doc->num_of_tokens == 0)
	{
		if (do_inredir(curr, curr->input_redir))
			return (1);
	}
	if (toktree->tail_cmd != curr || curr->output_redir->num_of_tokens > 0)
		dup2(fd->pipe_fd2[1], 1);
	if (curr->output_redir->num_of_tokens > 0)
	{
		make_outfile(envlst, curr);
		if (envlst->error == 1)
			exit(envlst->error);
	}
	if (curr->simple_command->num_of_tokens > 0)
		check_builtin(envlst, curr->simple_command, toktree->num_of_commands);
	if (curr->simple_command->num_of_tokens == 0)
		exit(0);
	return (envlst->error);
}

static void	child_process(t_env *envlst, t_token_tree *toktree, \
							t_command *curr, t_fd *fd)
{
	close(fd->pipe_fd2[0]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (curr->next_cmd == NULL && curr->output_redir->num_of_tokens == 0)
		dup2(fd->std_fd[1], 1);
	exit(pipe_util1(envlst, toktree, curr, fd));
}

static void	parent_process(t_env *envlst, t_command *curr, t_fd *fd)
{
	int	status;

	close(fd->pipe_fd2[1]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	wait(&status);
	envlst->error = get_child_exit_status(status);
	set_signal_handler();
	if (curr->output_redir->num_of_tokens > 0 && envlst->error == 0)
		do_outredir(curr, fd->pipe_fd2);
}

int	do_pipe(t_env *envlst, t_token_tree *toktree, t_command *curr, t_fd *fd)
{
	int	pid;

	pipe(fd->pipe_fd2);
	dup2(fd->pipe_fd1[1], 1);
	pid = fork();
	if (pid == 0)
		child_process(envlst, toktree, curr, fd);
	else
		parent_process(envlst, curr, fd);
	dup2(fd->pipe_fd1[0], 0);
	return (0);
}
