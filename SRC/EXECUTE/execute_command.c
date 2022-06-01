#include "../../INC/minishell.h"

void	check_builtin(t_env *envlst, t_token_list *toklst)
{
	int	status;

	if (envlst == NULL || toklst->head == NULL)
		return ;
	if (!ft_strncmp(toklst->head->text, "echo", 5))
		do_echo(toklst);
	else if (!ft_strncmp(toklst->head->text, "cd", 3))
		do_cd(toklst);
	else if (!ft_strncmp(toklst->head->text, "pwd", 4))
		do_pwd();
	else if (!ft_strncmp(toklst->head->text, "export", 7))
		do_export(envlst, toklst);
	else if (!ft_strncmp(toklst->head->text, "unset", 6))
		do_unset(envlst, toklst);
	else if (!ft_strncmp(toklst->head->text, "env", 4))
		do_env(envlst);
	else if (!ft_strncmp(toklst->head->text, "exit", 5))
		do_exit(toklst);
	else
		do_execve(envlst, toklst, &status);
}

void	execute_command(t_env *envlst, t_token_tree *toktree)
{
	t_command	*curr;

	curr = toktree->head_cmd;
	while (curr)
	{
		// if (curr->input_redir)
		if (curr->simple_command)
			check_builtin(envlst, curr->simple_command);
		curr = curr->next_cmd;
	}
}
