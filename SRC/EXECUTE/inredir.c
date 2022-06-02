#include "../../INC/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>

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

/*
 * ft_cmp 대신 비슷한 기존 함수인 ft_strncmp사용
 * ft_cmp 사용 시 EOF 일 때 종료 안 됨.
 * read == 0 or -1인 경우 예외처리 추가 함.
 * buf[r]이 아닌 buf[r - 1]을 하여 개행문자 삭제함.
*/
void	read_here_doc(t_token *curr, int *fd)
{
	char	buf[1024];
	int		r;

	while (1)
	{
		write(1, "> ", 2);
		r = read(0, buf, 1024);
		if (r <= 0)
			break ;
		buf[r - 1] = 0;
		if (ft_strncmp(curr->text, buf, ft_strlen(buf) + 1) == 0)
			break ;
		write(fd[1], buf, ft_strlen(buf));
		write(fd[1], "\n", 1);
	}
}

/*
 * 고정된 버퍼와 read사용 시 읽을 수 있는 문자열의 길이에 제한이 생김.
 * -> readline함수로 대체 시도.
*/
/*
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
		buffer = readline("heredoc > ");
		if (buffer == NULL)
			break ;
		else if (ft_strncmp(key, buffer, key_len + 1) == 0)
			break ;
		write(fd[1], buffer, ft_strlen(buffer));
		write(fd[1], "\n", 1);
		free(buffer);
	}
}
*/
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
