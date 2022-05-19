#ifndef MINISHELL_H
# define MINISHELL_H
# include "minishell_datastructure.h"
# include <stdio.h>
# define TRUE 1
# define FALSE 0
/*signal handler*/
int		set_signal_handler(void);
/*lexer and parser*/
char	*read_command(const char *prompt);

/*word expansion*/

/*pathname expansion*/

/*minishell builtins*/

#endif
