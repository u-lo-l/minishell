#include "../../INC/minishell.h"

void	check_builtin(t_env *env, t_token_list *token)
{
	int	status;

	if (ft_cmp(token->head->text, "echo"))
		do_echo(token);
	else if (ft_cmp(token->head->text, "cd"))
		do_cd(token);
	else if (ft_cmp(token->head->text, "pwd"))
		do_pwd();
	else if (ft_cmp(token->head->text, "export"))
		do_export(env, token);
	else if (ft_cmp(token->head->text, "unset"))
		do_unset(env, token);
	else if (ft_cmp(token->head->text, "env"))
		do_env(env);
	else if (ft_cmp(token->head->text, "exit"))
		do_exit(token);
	else
		do_execve(env, token, &status);
}

void	execute_command(t_env *env, t_token_tree *tree)
{
	t_command	*curr;

	curr = tree->head_cmd;
	while (curr)
	{
		// if (curr->input_redir)
		if (curr->simple_command)
			check_builtin(env, curr->simple_command);
		curr = curr->next_cmd;
	}
}
