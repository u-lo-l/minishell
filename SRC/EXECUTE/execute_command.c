/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:19:56 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/09 16:28:07 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

int	check_builtin(t_env *envlst, t_token_list *toklst, int command_num)
{
	if (envlst == NULL || toklst->head == NULL)
		return (0);
	if (!ft_strncmp(toklst->head->text, "echo", 5) \
		|| !ft_strncmp(toklst->head->text, "cd", 3) \
		|| !ft_strncmp(toklst->head->text, "pwd", 4) \
		|| !ft_strncmp(toklst->head->text, "export", 7) \
		|| !ft_strncmp(toklst->head->text, "unset", 6) \
		|| !ft_strncmp(toklst->head->text, "env", 4) \
		|| !ft_strncmp(toklst->head->text, "exit", 5))
		if_builtin(envlst, toklst, command_num);
	else
	{
		if (command_num > 1)
			pipe_do_execve(envlst, toklst);
		else
			do_execve(envlst, toklst);
	}
	return (0);
}

static t_fd	*begin_execute(void)
{
	t_fd	*fd;

	fd = malloc(sizeof(t_fd));
	if (fd == NULL)
		return (NULL);
	fd->std_fd[0] = dup(0);
	fd->std_fd[1] = dup(1);
	if (pipe(fd->pipe_fd1) != 0)
	{
		free (fd);
		return (NULL);
	}
	return (fd);
}

static void	finish_execute(t_token_tree *toktree, t_fd *fd)
{
	dup2(fd->std_fd[0], 0);
	dup2(fd->std_fd[1], 1);
	if (toktree->num_of_commands > 1)
		close(fd->pipe_fd1[1]);
	close(fd->pipe_fd1[0]);
	free(fd);
}

void	execute_command(t_env *envlst, t_token_tree *toktree)
{
	t_command	*curr;
	t_fd		*fd;
	int			count;

	fd = begin_execute();
	if (!fd)
		return ;
	count = 1;
	curr = toktree->head_cmd;
	while (curr)
	{
		if (toktree->num_of_commands == 1 && \
			no_pipe(envlst, toktree, curr, fd))
			break ;
		else if (toktree->num_of_commands != 1)
		{
			if (count > 1)
				dup2(fd->pipe_fd2[0], 0);
			if (do_pipe(envlst, toktree, curr, fd))
				break ;
		}
		count_plus(curr, &count);
	}
	finish_execute(toktree, fd);
}
