#include "../../INC/minishell.h"
#include <sys/errno.h>
#include <stdlib.h>

void    do_exit(char *token)
{
    if (!token | !ft_cmp(token, "exit"))
        return ;
    exit(errno);
}