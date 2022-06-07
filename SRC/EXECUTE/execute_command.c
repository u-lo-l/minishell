/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyoo <yyoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:19:56 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/07 20:19:58 by yyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

void	check_builtin(t_env *envlst, t_token_list *toklst, int command_num)
{
	if (envlst == NULL || toklst->head == NULL)
		return ;
	if (!ft_strncmp(toklst->head->text, "echo", 5))
		do_echo(toklst, envlst);
	else if (!ft_strncmp(toklst->head->text, "cd", 3))
		envlst->error = do_cd(toklst, envlst);
	else if (!ft_strncmp(toklst->head->text, "pwd", 4))
		do_pwd(envlst);
	else if (!ft_strncmp(toklst->head->text, "export", 7))
		do_export(toklst, envlst);
	else if (!ft_strncmp(toklst->head->text, "unset", 6))
		do_unset(toklst, envlst);
	else if (!ft_strncmp(toklst->head->text, "env", 4))
		do_env(envlst);
	else if (!ft_strncmp(toklst->head->text, "exit", 5))
		do_exit(toklst, envlst);
	else
	{
		if (command_num > 1)
			pipe_do_execve(envlst, toklst);
		else
			do_execve(envlst, toklst);
	}
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
