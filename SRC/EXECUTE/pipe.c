/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:20:00 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/13 21:39:15 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <sys/wait.h>
#include <stdlib.h>

static int	pipe_here_doc(t_env *envlst, t_command *command, t_fd *fd)
{
	t_token		*curr;

	if (!set_heredoc_signal())
		exit (return_err("SIGNAL HANDLER FAIL", 1));
	curr = command->here_doc->head;
	dup2(fd->std_fd[0], 0);
	dup2(fd->std_fd[1], 1);
	while (curr)
	{
		pipe(fd->heredoc_fd);
		read_here_doc(curr, fd->heredoc_fd);
		close(fd->heredoc_fd[1]);
		curr = curr->next;
	}
	envlst->error = 0;
	dup2(fd->heredoc_fd[0], 0);
	if (command->input_redir->num_of_tokens > 0)
	{
		close(fd->heredoc_fd[0]);
		if (do_inredir(command, command->input_redir))
			envlst->error = 1;
	}
	if (!set_signal_both(SIG_DFL))
		exit (return_err("SIGNAL HANDLER FAIL", 1));
	return (envlst->error);
}

static int	pipe_util1(t_env *envlst, t_token_tree *toktree, \
						t_command *curr, t_fd *fd)
{
	if (curr->here_doc->num_of_tokens > 0 \
		&& pipe_here_doc(envlst, curr, fd))
		return (1);
	if (curr->input_redir->num_of_tokens > 0 \
		&& curr->here_doc->num_of_tokens == 0 \
		&& do_inredir(curr, curr->input_redir))
		return (1);
	if (toktree->tail_cmd != curr || curr->output_redir->num_of_tokens > 0)
		dup2(fd->pipe_fd2[1], 1);
	if (curr->output_redir->num_of_tokens > 0)
	{
		make_outfile(envlst, curr);
		if (envlst->error == 1)
			exit(envlst->error);
	}
	if (curr->output_redir->num_of_tokens > 0)
	{
		fd->outfile = open_outredir(curr->output_redir->tail, fd->outfile);
		dup2(fd->outfile, 1);
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
	if (!set_signal_both(SIG_DFL))
		exit (return_err("SIGNAL HANDLER FAIL", 1));
	if (curr->next_cmd == NULL && curr->output_redir->num_of_tokens == 0)
		dup2(fd->std_fd[1], 1);
	exit(pipe_util1(envlst, toktree, curr, fd));
}

static void	parent_process(t_env *envlst, t_fd *fd)
{
	int	status;

	close(fd->pipe_fd2[1]);
	if (!set_signal_both(SIG_IGN))
		exit (return_err("SIGNAL HANDLER FAIL", 1));
	wait(&status);
	envlst->error = get_child_exit_status(status);
	if (!set_signal_handler())
		exit (return_err("SIGNAL HANDLER FAIL", 1));
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
		parent_process(envlst, fd);
	dup2(fd->pipe_fd1[0], 0);
	return (0);
}
