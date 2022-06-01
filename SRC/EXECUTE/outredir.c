#include "../../INC/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void	push_outfile(t_list *list, int fd)
{
	char	*buf;
	int		r;

	buf = malloc(sizeof(char *) * 1);
	r = 1;
	while (r > 0)
	{
		r = read(list->fd2[0], buf, 1); // ?????
		if (r < 1)
			break ;
		write(fd, buf, 1);
	}
	free(buf);
}

int	open_outredir(t_token *tail, int fd)
{
	struct stat	buf;

	if (tail->type == 1)
	{
		if (stat(tail->text, &buf) == -1)
			fd = open(tail->text, O_CREAT | O_TRUNC | O_RDWR, 0755);
		else
			fd = open(tail->text, O_TRUNC | O_RDWR);
	}
	else if (tail->type == 2)
	{
		if (stat(tail->text, &buf) == -1)
			fd = open(tail->text, O_CREAT | O_APPEND | O_RDWR, 0755);
		else
			fd = open(tail->text, O_APPEND | O_RDWR);
	}
	return (fd);
}

void	do_outredir(t_token_list *outredir)
{
	struct stat	buf;
	t_token		*curr;
	int			fd;

	curr = outredir->head;
	while (curr->next)
	{
		if (stat(curr->text, &buf) == -1)
			fd = open(curr->text, O_CREAT | O_RDWR, 0755);
		else
		{
			if (curr->type == 1)
				fd = open(curr->text, O_TRUNC | O_RDWR);
		}
		close(fd);
		curr = curr->next;
	}
	fd = open_outredir(curr, fd);
	push_outfile(fd);
}