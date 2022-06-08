/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:19:56 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/08 02:36:11 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

int	check_builtin(t_env *envlst, t_token_list *toklst, int command_num)
{
	if (envlst == NULL || toklst->head == NULL)
		return (return_err("unexpected error", 1));
	else if (!ft_strncmp(toklst->head->text, "echo", 5))
		envlst->error = do_echo(toklst);
	else if (!ft_strncmp(toklst->head->text, "cd", 3))
		envlst->error = do_cd(toklst, envlst);
	else if (!ft_strncmp(toklst->head->text, "pwd", 4))
		envlst->error = do_pwd();
	else if (!ft_strncmp(toklst->head->text, "export", 7))
		envlst->error = do_export(toklst, envlst);
	else if (!ft_strncmp(toklst->head->text, "unset", 6))
		envlst->error = do_unset(toklst, envlst);
	else if (!ft_strncmp(toklst->head->text, "env", 4))
		envlst->error = do_env(envlst);
	else if (!ft_strncmp(toklst->head->text, "exit", 5))
		envlst->error = do_exit(toklst);
	else
	{
		if (command_num > 1)
			pipe_do_execve(envlst, toklst);
		else
			do_execve(envlst, toklst);
	}
	return (0);
}

void	print_result(int *fd1)
{
	int		r;
	char	buf[1024];

	r = 1;
	while (1)
	{
		r = read(fd1[0], buf, 1024);
		if (r < 1)
			break ;
		buf[r] = 0;
		printf("%s", buf);
	}
	close(fd1[0]);
}

void	after_execute(t_token_tree *toktree, t_fd *fd)
{
	dup2(fd->std_fd[0], 0);
	dup2(fd->std_fd[1], 1);
	if (toktree->num_of_commands > 1)
	{
		close(fd->pipe_fd1[1]);
		print_result(fd->pipe_fd2);
	}
}

/* 얘도 exit status 반환해야지 */
void	execute_command(t_env *envlst, t_token_tree *toktree)
{
	t_command	*curr;
	t_fd		*fd;
	int			count;

	fd = malloc(sizeof(t_fd));
	count = 1;
	curr = toktree->head_cmd;
	copy_std_fd(fd);
	pipe(fd->pipe_fd1);
	while (curr)
	{
		if (no_pipe(envlst, toktree, curr, fd))
			break ;
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
	after_execute(toktree, fd);
}
