#include "../../INC/minishell.h"
#include <stdlib.h>

void	if_builtin(t_env *envlst, t_token_list *toklst, int command_num)
{
	if (!ft_strncmp(toklst->head->text, "echo", 5))
		envlst->error = do_echo(toklst);
	else if (!ft_strncmp(toklst->head->text, "cd", 3))
		envlst->error = do_cd(toklst, envlst);
	else if (!ft_strncmp(toklst->head->text, "pwd", 4))
		envlst->error = do_pwd();
	else if (!ft_strncmp(toklst->head->text, "export", 7))
		envlst->error = do_export(toklst, envlst);
	else if (!ft_strncmp(toklst->head->text, "unset", 6))
		envlst->error = do_unset(toklst, envlst);
	else if (!ft_strncmp(toklst->head->text, "env", 4))
		envlst->error = do_env(envlst);
	else if (!ft_strncmp(toklst->head->text, "exit", 5))
		envlst->error = do_exit(toklst);
	if (command_num > 1)
		exit(1);
}