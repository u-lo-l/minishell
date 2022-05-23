#include "../../INC/minishell.h"

void    do_exit(char *token)
{
    if (!token | !ft_cmp(token, "exit"))
        return ;
    exit(errno);
}