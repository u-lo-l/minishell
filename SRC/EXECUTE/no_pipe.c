#include "../../INC/minishell.h"

int	no_pipe_util1(t_command *curr, int *std_fd)
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

void	no_pipe_util2(t_env *envlst, t_command *curr, int *std_fd)
{
	int	red_fd[2];

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