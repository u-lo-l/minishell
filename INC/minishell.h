#ifndef MINISHELL_H
# define MINISHELL_H
# include "../LIBFT/libft.h"
# include "minishell_datastructure.h"
# include <stdio.h>
# define TRUE 1
# define FALSE 0

/*signal handler*/
int				set_signal_handler(void);
/*lexer and parser*/
/*	read command*/
t_input			*read_command(const char *prompt);
/*	tokenize*/
t_token			*create_token(char *word);
int				is_eof_token(t_token *tok);
void			free_token(t_token *tok);

t_token_list	*create_empty_toklst(void);
void			free_toklst(t_token_list *lst);
int				add_token_to_toklst(t_token_list *lst, t_token *tok);
int				del_token_from_toklst(t_token_list *lst);
void			print_token_list(t_token_list *lst);

t_token_list	*scan_token(t_input *input, t_env *env_list);
/*		tokenize utils*/
void			skip_space(t_input *input);
int	split_token(t_token_list *toklst, t_input *input, char **word);
void			make_word(t_input *input, char **word);
void			quote_case(t_input *input, char **word, t_env *env_list);
void			dollar_case(t_input *input, char **word, t_env *env_list);


/*	word expansion*/
char	*word_expansion(t_input	*input, t_env *env_list);

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

#endif