#include "../../INC/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

char	*get_path();

void	do_execve(t_env *env, t_token_list *token, int *status)
{
    int     i;
    char    **list;
	t_token *curr;
    pid_t	pid;
    struct stat buf;

    list = malloc(sizeof(char *) * token->num_of_tokens);
    i = 0;
    while (curr)
    {
        list[i] = malloc(sizeof(char) * ft_strlen(curr->text));
        i++; 
        curr = curr->next;
    }

	pid = fork();
    if (pid == 0)
    {
        if (stat(list[0], &buf) == 0)
            execve(list[0], list, 0);

    }
    if (pid > 0)
    {
        wait(status);
    }
}