/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:19:56 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/13 16:36:46 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

static int	is_special_builtin(t_command *curr)
{
	if (!curr || !curr->simple_command || !curr->simple_command->head)
		return (FALSE);
	if (!ft_strncmp(curr->simple_command->head->text, "cd", 3) \
		|| !ft_strncmp(curr->simple_command->head->text, "export", 7) \
		|| !ft_strncmp(curr->simple_command->head->text, "unset", 6) \
		|| !ft_strncmp(curr->simple_command->head->text, "exit", 5))
		return (TRUE);
	return (FALSE);
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
	{
		close(fd->pipe_fd1[1]);
		close(fd->pipe_fd1[0]);
	}
	close(fd->std_fd[0]);
	close(fd->std_fd[1]);
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
		if (toktree->num_of_commands == 1 && is_special_builtin(curr))
			if_builtin(envlst, curr->simple_command, 1);
		else
		{
			if (count > 1)
				dup2(fd->pipe_fd2[0], 0);
			if (do_pipe(envlst, toktree, curr, fd))
				break ;
		}
		count++;
		curr = curr->next_cmd;
	}
	finish_execute(toktree, fd);
}
