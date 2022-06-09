/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:20:31 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/09 20:53:58 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

char	**get_command_list(t_token_list *token)
{
	t_token	*curr;
	char	**command_list;
	int		i;

	command_list = malloc(sizeof(char *) * (token->num_of_tokens + 1));
	curr = token->head;
	i = 0;
	while (curr)
	{
		command_list[i] = curr->text;
		i++;
		curr = curr->next;
	}
	command_list[i] = NULL;
	return (command_list);
}

static void	child_err(t_env *envlst, char *command, struct stat *buf)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	envlst->error = 127;
	if ((buf->st_mode & 00100) == 0)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		envlst->error = 126;
	}
	else if (command[ft_strlen(command) - 1] == '/')
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": fail to execute command\n", 2);
	exit(envlst->error);
}

void	when_child(t_env *envlst, char **command_list)
{
	char		*path;
	char		**converted_envlst;
	struct stat	buf;

	converted_envlst = envlst_to_arr(envlst);
	if (converted_envlst == NULL)
		return ;
	if (stat(command_list[0], &buf) != -1)
		path = command_list[0];
	else
		path = get_path(envlst, command_list);
	if (execve(path, command_list, converted_envlst) == -1)
		child_err(envlst, command_list[0], &buf);
}

void	pipe_do_execve(t_env *envlst, t_token_list *token)
{
	char		**command_list;

	command_list = NULL;
	command_list = get_command_list(token);
	when_child(envlst, command_list);
	free(command_list);
}

void	do_execve(t_env *envlst, t_token_list *token)
{
	char		**command_list;
	pid_t		pid;
	int			status;

	status = 0;
	command_list = NULL;
	command_list = get_command_list(token);
	pid = fork();
	if (pid == 0)
	{
		unset_signal_handler();
		when_child(envlst, command_list);
	}
	else if (pid > 0)
	{
		wait(&status);
		set_signal_handler();
		envlst->error = get_child_exit_status(status);
	}
	free(command_list);
}
