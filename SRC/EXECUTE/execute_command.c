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

int	redir_util1(t_command *curr, int *std_fd)
{
	if (curr->here_doc->num_of_tokens > 0)
	{
		if (do_here_doc(curr))
		{
			close(0);
			dup2(std_fd[0], 0);
			return (1);
		}
	}
	if (curr->input_redir->num_of_tokens > 0 \
		&& curr->here_doc->num_of_tokens == 0)
	{
		if (do_inredir(curr->input_redir))
			return (1);
	}
	return (0);
}

void	redir_util2(t_env *envlst, t_command *curr, int *std_fd, int *red_fd)
{
	if (curr->output_redir->num_of_tokens > 0)
	{
		make_outfile(curr);
		pipe(red_fd);
		dup2(red_fd[1], 1);
	}
	if (curr->simple_command->num_of_tokens > 0)
		check_builtin(envlst, curr->simple_command);
	if (curr->output_redir->num_of_tokens > 0)
	{
		do_outredir(curr, red_fd);
	}
	if (curr->input_redir->num_of_tokens > 0 \
		|| curr->here_doc->num_of_tokens > 0)
	{
		dup2(std_fd[0], 0);
		close(std_fd[0]);
	}
	if (curr->output_redir->num_of_tokens > 0)
	{
		dup2(std_fd[1], 1);
		close(std_fd[1]);
	}
}

void	execute_command(t_env *envlst, t_token_tree *toktree)
{
	t_command	*curr;
	int			std_fd[2];
	int			red_fd[2];

	curr = toktree->head_cmd;
	while (curr)
	{
		std_fd[0] = dup(0);
		std_fd[1] = dup(1);
		// if (toktree->num_of_commands == 1) 파이프 개수 = num_of_commands - 1
		if (redir_util1(curr, std_fd))
			break ;
		redir_util2(envlst, curr, std_fd, red_fd);
		curr = curr->next_cmd;
	}
}
