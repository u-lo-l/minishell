#include "../../INC/minishell.h"

void	check_builtin(t_env *envlst, t_token_list *toklst)
{
	int	status;

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
	int			std_fd[2];
	int			red_fd[2];

	curr = toktree->head_cmd;
	while (curr)
	{
		std_fd[0] = dup(0);
		std_fd[1] = dup(1);
		// if (toktree->num_of_commands == 1) 파이프 개수 = num_of_commands - 1
		if (curr->here_doc->num_of_tokens > 0)
		{
			if (do_here_doc(curr))
			{
				close(0);
				dup2(std_fd[0], 0);
				break ;
			}
		}
		if (curr->input_redir->num_of_tokens > 0 \
			&& curr->here_doc->num_of_tokens == 0)
		{
			if (do_inredir(curr->input_redir))
				break ;
		}
		if (curr->output_redir->num_of_tokens > 0)
		{
			pipe(red_fd);
			dup2(red_fd[1], 1);
		}
		if (curr->simple_command->num_of_tokens > 0)
			check_builtin(envlst, curr->simple_command);
		if (curr->output_redir->num_of_tokens > 0){
			do_outredir(curr->output_redir, red_fd);
		}
		if (curr->input_redir->num_of_tokens > 0 || curr->here_doc->num_of_tokens > 0)
		{
			dup2(std_fd[0], 0);
			close(std_fd[0]);
		}
		if (curr->output_redir->num_of_tokens > 0)
		{
			dup2(std_fd[1], 1);
			close(std_fd[1]);
		}
		curr = curr->next_cmd;
	}
	// close(0);
	// dup2(in_fd, 0);

}
