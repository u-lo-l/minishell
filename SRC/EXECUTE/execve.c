#include "../../INC/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

char	**split_path(t_env *env)
{
	t_envnode	*curr;
	char		**path;

	path = NULL;
	curr = env->phead;
	while (curr)
	{
		if (ft_strnstr(curr->key, "PATH", 4))
		{
			path = ft_split(curr->value, ':');
			break ;
		}
		curr = curr->nextnode;
	}
	return (path);
}

char	*get_path(t_env *env, char **command_list, int num)
{
	struct stat	buf;
	char		**path;
	char		*simple_path;
	char		*str;
	int			i;

	path = split_path(env);
	while (path[num])
		num++;
	str = ft_strjoin("/", command_list[0]);
	i = 0;
	while (path[i])
	{
		simple_path = ft_strjoin(path[i], str);
		if (stat(simple_path, &buf) != -1)
			break ;
		free(simple_path);
		i++;
	}
	if (i == num)
		return (NULL);
	return (simple_path);
}

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
		command_list[i] = malloc(sizeof(char) * ft_strlen(curr->text));
		command_list[i] = curr->text;
		i++;
		curr = curr->next;
	}
	command_list[i] = 0;
	return (command_list);
}

void	when_child(t_env *env, char **command_list)
{
	struct stat	buf;
	char		*path;
	int			num;

	num = 0;
	if (stat(command_list[0], &buf) != -1)
	{
		if (execve(command_list[0], command_list, 0) != -1)
			exit(1);
	}
	else
	{
		path = get_path(env, command_list, num);
		if (path == 0)
		{
			printf("bash: %s: command not found\n", command_list[0]);
			exit(1);
		}
		if (execve(path, command_list, 0) != -1)
			exit(1);
	}
}

void	do_execve(t_env *env, t_token_list *token, int *status)
{
	char		**command_list;
	pid_t		pid;

	command_list = NULL;
	command_list = get_command_list(token);
	pid = fork();
	if (pid == 0)
		when_child(env, command_list);
	else if (pid > 0)
	{
		wait(status);
		*status = *status >> 8;
	}
}
