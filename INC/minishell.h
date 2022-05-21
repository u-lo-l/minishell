#ifndef MINISHELL_H
# define MINISHELL_H
# include "../LIBFT/libft.h"
# include "minishell_datastructure.h"
# include <stdio.h>
# define TRUE 1
# define FALSE 0
/*signal handler*/
int		set_signal_handler(void);
/*lexer and parser*/
t_input	*read_command(const char *prompt);

/*word expansion*/

/*pathname expansion*/

/*minishell builtins*/
/*----env*/
int		ft_keylen(char *str);
int		ft_cmp(char *str1, char *str);
void	display_env(t_env *env);
char	*search_key(t_env *env, char *key);
void	copy_element(char *envp, t_envnode *new_node, int len, int keylen);
void	add_node(char *envp, t_env *env, int i);
t_env	*env_list(char **envp);
/*----unset*/
void	free_head_tail(t_env *env, t_envnode *target);
t_env	*do_unset(t_env *env, char *key);


#endif