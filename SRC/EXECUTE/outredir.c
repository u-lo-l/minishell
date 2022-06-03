#include "../../INC/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void	push_outfile(int outfile_fd, int *red_fd)
{
	char	*buf;
	int		r;

	buf = malloc(sizeof(char *) * 1);
	r = 1;
	while (r > 0)
	{
		r = read(red_fd[0], buf, 1); // ?????
		if (r < 1)
			break ;
		write(outfile_fd, buf, 1);
	}
	free(buf);
}

int	open_outredir(t_token *tail, int outfile_fd)
{
	struct stat	buf;

	if (tail->type == e_outrdr)
	{
		if (stat(tail->text, &buf) == -1)
			outfile_fd = open(tail->text, O_CREAT | O_TRUNC | O_RDWR, 0755);
		else
			outfile_fd = open(tail->text, O_TRUNC | O_RDWR);
	}
	else if (tail->type == e_appendrdr)
	{
		if (stat(tail->text, &buf) == -1)
			outfile_fd = open(tail->text, O_CREAT | O_APPEND | O_RDWR, 0755);
		else
			outfile_fd = open(tail->text, O_APPEND | O_RDWR);
	}
	return (outfile_fd);
}

void	do_outredir(t_token_list *outredir, int *red_fd)
{
	struct stat	buf;
	t_token		*curr;
	int			outfile_fd;

	close(red_fd[1]);
	close(1);
	curr = outredir->head;
	while (curr->next)
	{
		if (stat(curr->text, &buf) == -1)
			outfile_fd = open(curr->text, O_CREAT | O_RDWR, 0755);
		else
		{
			if (curr->type == e_outrdr)
				outfile_fd = open(curr->text, O_TRUNC | O_RDWR);
		}
		close(outfile_fd);
		curr = curr->next;
	}
	outfile_fd = open_outredir(curr, outfile_fd);
	push_outfile(outfile_fd, red_fd);
}