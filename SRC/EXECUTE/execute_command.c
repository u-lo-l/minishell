#include "../../INC/minishell.h"

void	check_builtin(t_env *envlst, t_token_list *toklst)
{
	int	status;

	if (toklst->head == NULL || envlst == NULL)
		return ;
	if (ft_cmp(toklst->head->text, "echo"))
		do_echo(toklst);
	else if (ft_cmp(toklst->head->text, "cd"))
		do_cd(toklst);
	else if (ft_cmp(toklst->head->text, "pwd"))
		do_pwd();
	else if (ft_cmp(toklst->head->text, "export"))
		do_export(envlst, toklst);
	else if (ft_cmp(toklst->head->text, "unset"))
		do_unset(envlst, toklst);
	else if (ft_cmp(toklst->head->text, "env"))
		do_env(envlst);
	else if (ft_cmp(toklst->head->text, "exit"))
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
