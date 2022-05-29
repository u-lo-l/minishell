/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:54:30 by dkim2             #+#    #+#             */
/*   Updated: 2022/05/30 00:54:31 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../LIBFT/libft.h"
# include "minishell_datastructure.h"
# include <stdio.h>
# define TRUE 1
# define FALSE 0

/*signal handler*/
int				set_signal_handler(void);
/*	read command*/
t_input			*read_command(const char *prompt);
void			check_input_state(t_input *input);
/*	tokenize*/
/*		tokenize check*/
int				is_quote(char c);
int				is_redir_op(char c);
int				is_space(char c);
int				is_special_char(char c);
/*		tokenize utils*/
void			pass_space_tab(t_input *input);
int				set_word(t_input *input, char **pword);
char			*expand_variable(t_input *input, t_env *env_list);
int				delimit_and_add_token_to_tree(t_token_tree *toktree,
												char **pword,
												enum e_token_type *type);
/*		tokenize special character*/
int				case_space(t_token_tree *toktree, t_input *input, \
							char **pword, t_toktype *type);
int				case_pipe(t_token_tree *toktree, t_input *input, \
							char **word, t_toktype	*type);
int				case_dollar(t_input *input, t_env *envlst, char **word);
int				case_quote(t_input *input, t_env *envlst, char **word);
int				case_redirection(t_token_tree *toktree, t_input *input, \
								char **pword, t_toktype *type);

/*		token_node.c*/
t_token			*create_token(char *word, enum e_token_type type);
int				is_eof_token(t_token *tok);
void			free_token(t_token *tok);
/*		token_list.c*/
t_token_list	*create_empty_toklst(void);
void			free_toklst(t_token_list *lst);
int				add_token_to_toklst(t_token_list *lst, t_token *tok);
// int				del_token_from_toklst(t_token_list *lst);
void			print_token_list(t_token_list *lst);
/*		token_command.c*/
t_command		*create_empty_command(void);
void			free_command(t_command *command);
int				add_token_to_command(t_command *command, t_token *tok);
void			print_command(t_command *command);
/*		token_tree.c*/
t_token_tree	*create_token_tree(void);
void	 		free_token_tree(t_token_tree *token_tree);
int				add_token_to_tree(t_token_tree *toktree, t_token *tok);
// int				add_command(t_token_tree *token_tree, t_command *new_command);
int				add_one_empty_command(t_token_tree *token_tree);
void			print_token_tree(t_token_tree *token_tree);

/*		token_scanner*/
t_token_tree	*tokenize_and_parsing(t_input *input, t_env *envlst);

/*----env_list*/
void	copy_element(char *envp, t_envnode *new_node, int len, int keylen);
void	add_node(char *envp, t_env *env, int i);
t_env	*env_list(char **envp);
void	free_env_list(t_env *envlst);
/*minishell builtins*/
/*----env*/
int		ft_keylen(char *str);
int		ft_cmp(char *str1, char *str);
void	do_env(t_env *env);
char	*search_key(t_env *env, char *key);
/*----unset*/
void	free_head_tail(t_env *env, t_envnode *target);
void	traversal_env(t_env *env, char **unset_token, int i);
t_env	*do_unset(t_env *env, char **unset_token);
/*----pwd*/
void	do_pwd(void);
/*----echo*/
void	do_echo(t_env *env, char *str, char **echo_token);
/*----export*/
void	do_export(t_env *env, char **export_token);
/*----cd*/
void	do_cd(char **cd_toekn);
/*----exit*/
void	do_exit(char *token);

#endif