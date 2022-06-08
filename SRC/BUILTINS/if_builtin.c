#include "../../INC/minishell.h"
#include <stdlib.h>

void	if_builtin(t_env *envlst, t_token_list *toklst)
{
	if (!ft_strncmp(toklst->head->text, "echo", 5))
		do_echo(toklst, envlst);
	else if (!ft_strncmp(toklst->head->text, "cd", 3))
		envlst->error = do_cd(toklst, envlst);
	else if (!ft_strncmp(toklst->head->text, "pwd", 4))
		do_pwd(envlst);
	else if (!ft_strncmp(toklst->head->text, "export", 7))
		do_export(toklst, envlst);
	else if (!ft_strncmp(toklst->head->text, "unset", 6))
		do_unset(toklst, envlst);
	else if (!ft_strncmp(toklst->head->text, "env", 4))
		do_env(envlst);
	else if (!ft_strncmp(toklst->head->text, "exit", 5))
		do_exit(toklst, envlst);
	exit(1);
}