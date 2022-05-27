#include "../INC/minishell.h"

void    check_builtin(char **env, char *str, char **token)
{
	if (ft_cmp(str, "echo") && ft_cmp(token[0], "echo"))
		do_echo(env, str, token);
	if (ft_cmp(str, "cd") && ft_cmp(token[0], "cd"))
		do_cd(token);
	if (ft_cmp(str, "env") && ft_cmp(token[0], "env"))
		do_pwd();
	if (ft_cmp(str, "env") && ft_cmp(token[0], "env"))
		do_export(env, token);
	if (ft_cmp(str, "unset") && ft_cmp(token[0], "unset"))
		do_unset(env, token);
	if (ft_cmp(str, "env") && ft_cmp(token[0], "env"))
		do_env(env);
	if (ft_cmp(str, "exit") && ft_cmp(token[0], "exit"))
		do_exit(token);

}