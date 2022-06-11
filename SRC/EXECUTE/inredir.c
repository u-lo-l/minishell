/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inredir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:20:10 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/11 15:43:42 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>

static void	err_infile(t_command *curr, char *infile_text)
{
	t_token	*file;
	int		outfile_fd;

	file = curr->redirection->head;
	while (ft_strncmp(file->text, infile_text, ft_strlen(infile_text) + 1))
	{
		outfile_fd = open_outredir(file, outfile_fd);
		close(outfile_fd);
		file = file->next;
	}
}

int	check_infile(t_command *curr, t_token_list *inredir)
{
	t_token		*infile;
	struct stat	buf;

	infile = inredir->head;
	while (infile)
	{
		if (stat(infile->text, &buf) == -1)
		{
			ft_putstr_fd("minishell : ", 2);
			ft_putstr_fd(infile->text, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			err_infile(curr, infile->text);
			return (1);
		}
		infile = infile->next;
	}
	return (0);
}

int	do_inredir(t_command *curr, t_token_list *inredir)
{
	int			in_fd;

	if (check_infile(curr, inredir))
		return (1);
	in_fd = open(inredir->tail->text, O_RDONLY);
	dup2(in_fd, 0);
	close(in_fd);
	return (0);
}

void	read_here_doc(t_token *currtok, int *fd)
{
	char	*key;
	char	*buffer;
	int		key_len;

	key = currtok->text;
	if (key == NULL)
		return ;
	key_len = ft_strlen(key);
	while (TRUE)
	{
		buffer = readline(" > ");
		if (buffer == NULL)
			break ;
		else if (ft_strncmp(key, buffer, key_len + 1) == 0)
		{
			free(buffer);
			break ;
		}
		ft_putstr_fd(buffer, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(buffer);
	}
}

int	do_here_doc(t_command *command)
{
	t_token		*curr;
	int			fd[2];

	curr = command->here_doc->head;
	while (curr)
	{
		pipe(fd);
		read_here_doc(curr, fd);
		close(fd[1]);
		curr = curr->next;
		if (curr != NULL)
			close(fd[0]);
	}
	dup2(fd[0], 0);
	if (command->input_redir->num_of_tokens > 0)
	{
		close(fd[0]);
		if (do_inredir(command, command->input_redir))
			return (1);
	}
	return (0);
}
