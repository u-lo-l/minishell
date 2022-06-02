#include "../../INC/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int	check_infile(t_token_list *inredir)
{
	t_token		*curr;
	struct stat	buf;

	curr = inredir->head;
	while (curr)
	{
		if (stat(curr->text, &buf) == -1)
		{
			printf("minishell: %s: No such file or directory\n", curr->text);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	do_inredir(t_token_list *inredir)
{
	int			in_fd;

	if (check_infile(inredir))
		return (1);
	in_fd = open(inredir->tail->text, O_RDONLY);
	dup2(in_fd, 0);
	close(in_fd);
	return (0);
}

void	read_here_doc(t_token *curr, int *fd)
{
	char	buf[1024];
	int		r;

	while (1)
	{
		write(1, "> ", 2);
		r = read(0, buf, 1024);
		buf[r] = 0;
		if (ft_cmp(curr->text, buf))
			break ;
		write(fd[1], buf, ft_strlen(buf));
	}
}

int	do_here_doc(t_command *command)
{
	t_token		*curr;
	int			fd[2];

	pipe(fd);
	curr = command->here_doc->head;
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
