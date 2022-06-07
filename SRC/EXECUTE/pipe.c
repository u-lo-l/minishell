#include "../../INC/minishell.h"

int	pipe_here_doc(t_command * command, int *std_fd)
{
	t_token		*curr;
	int			fd[2];

	pipe(fd);
	curr = command->here_doc->head;
	dup2(std_fd[0], 0);
	dup2(std_fd[1], 1);
	while (curr)
	{
		read_here_doc(curr, fd);
		close(fd[1]);
		dup2(fd[0], 0);
		curr = curr->next;
	}
	if (command->input_redir->num_of_tokens > 0)
	{
		if (check_infile(command->input_redir))
			return (1);
	}
	return (0);
}


int	pipe_util1(t_command *curr, int *std_fd)
{
	if (curr->here_doc->num_of_tokens > 0)
	{
		if (pipe_here_doc(curr, std_fd))
			return (1);
	}
	if (curr->input_redir->num_of_tokens > 0 \
		&& curr->here_doc->num_of_tokens == 0)
	{
		if (do_inredir(curr->input_redir))
			return (1);
	}
	return (0);
}