/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:20:31 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/11 17:13:04 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>

static char	**get_command_list(t_token_list *token)
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

void	stat_value(t_env *envlst, char **converted_envlst, char **command_list)
{
	struct stat	buf;
	int			stat_result;

	stat_result = stat(command_list[0], &buf);
	if ((S_IFMT & buf.st_mode) == S_IFREG)
	{
		if ((S_IXUSR & buf.st_mode) == 0)
			exit (return_err("Permission denied", 126));
		exe(envlst, command_list, converted_envlst, stat_result);
	}
	else if ((S_IFMT & buf.st_mode) == S_IFDIR)
	{
		if ((S_IXUSR & buf.st_mode) == 0)
			exit (return_err("Permission denied", 126));
		exit (return_err("is a directory", 126));
	}
	else
		exe(envlst, command_list, converted_envlst, stat_result);
}

static void	when_child(t_env *envlst, char **command_list)
{
	char		**converted_envlst;

	converted_envlst = envlst_to_arr(envlst);
	if (converted_envlst == NULL)
		return ;
	if (ft_strchr(command_list[0], '/'))
		stat_value(envlst, converted_envlst, command_list);
	exe(envlst, command_list, converted_envlst, -1);
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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		when_child(envlst, command_list);
	}
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		wait(&status);
		set_signal_handler();
		envlst->error = get_child_exit_status(status);
	}
	free(command_list);
}
