#include "../../INC/minishell.h"

void	check_builtin(t_env *envlst, t_token_list *toklst)
{
	int	status;

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
		do_execve(envlst, toklst, &status);
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
			break;
		buf[r] = 0;
		printf("%s", buf);
	}
}

void	execute_command(t_env *envlst, t_token_tree *toktree)
{
	t_command	*curr;
	int			std_fd[2];
	int			red_fd[2];
	int			fd1[2];
	int			count;

	count = 1;
	curr = toktree->head_cmd;
	std_fd[0] = dup(0);
	std_fd[1] = dup(1);
	while (curr)
	{
		if (toktree->num_of_commands == 1)
		{
			if (no_pipe_util1(curr, std_fd))
				break ;
			no_pipe_util2(envlst, curr, std_fd, red_fd);
		}
		else
		{
			if (count > 1)
			{
				dup2(fd1[0], 0);
				close(fd1[0]);
			}
			if (toktree->num_of_commands > 1)
			{	
				pipe(fd1);
				dup2(fd1[1], 1);
				close(fd1[1]);
			}
			if (pipe_util1(curr, std_fd))
				break ;
			pipe_util2(envlst, curr, std_fd, red_fd);
		}
		count++;
		curr = curr->next_cmd;
	}
	if (toktree->num_of_commands > 1)
	{
		dup2(std_fd[0], 0);
		dup2(std_fd[1], 1);
		print_result(fd1);
		close(fd1[0]);
		
	}
}
