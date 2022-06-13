/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:54:30 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/13 22:08:06 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../LIBFT/libft.h"
# include "minishell_datastructure.h"
# include <stdio.h>
/*utils*/
void			ft_double_free(char **str);
int				return_err(char *errstr, int ret_val);
int				is_env_name(char *name);
int				get_child_exit_status(int stat_loc);

/*signal handler*/
int				set_signal_handler(void);
int				set_signal_both(void *sig_handler);
int				set_heredoc_signal(void);

/*	read command*/
void			free_input(t_input *input);
t_input			*read_command(char *prompt);
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
int				delimit_and_add_token_to_tree(t_token_tree *toktree, \
											char **pword, \
											int *type);
int				case_dollar_util(char **pword, char *expanded_word);
/*		tokenize special character*/
int				case_space(t_token_tree *toktree, t_input *input, \
							char **pword, int *type);
int				case_pipe(t_token_tree *toktree, t_input *input, \
							char **word, int	*type);
int				case_dollar(t_input *input, t_env *envlst, char **word, \
							int type);
int				case_quote(t_input *input, t_env *envlst, char **word, \
							int type);
int				case_redirection(t_token_tree *toktree, t_input *input, \
								char **pword, int *type);
/*		token_node.c*/
t_token			*create_token(char *word, int type);
void			free_token(t_token *tok);
/*		token_list.c*/
t_token_list	*create_empty_toklst(void);
void			free_toklst(t_token_list *lst);
int				add_token_to_toklst(t_token_list *lst, t_token *tok);
/*		token_command.c*/
t_command		*create_empty_command(void);
void			free_command(t_command *command);
int				add_token_to_command(t_command *command, t_token *tok);
/*		token_tree.c*/
t_token_tree	*create_token_tree(void);
void			free_token_tree(t_token_tree *token_tree);
int				add_token_to_tree(t_token_tree *toktree, t_token *tok);
int				add_one_empty_command(t_token_tree *token_tree);
/*		token_scanner*/
t_token_tree	*tokenize_and_parsing(t_input *input, t_env *envlst);

/*----env_list*/
t_envnode		*create_envnode(char *key, char *value);
int				modify_value(t_env *envlst, char *key, char *value);
int				add_node_to_lst(t_env *envlst, t_envnode *node);
int				del_node_from_lst(t_env *envlst, char *key);
t_env			*env_list(char **envp);
void			free_env_node(t_envnode *node);
void			free_env_list(t_env *envlst);
int				seperate_keyvalue(char *k_and_v, char **key, char **val);
char			**envlst_to_arr(t_env *envlst);

/*		execute*/
void			execute_command(t_env *env, t_token_tree *tree);
int				check_builtin(t_env *env, t_token_list *token, int command_num);
void			exe(t_env *envlst, char **cmdlst, char **envp, int stat_result);
void			pipe_do_execve(t_env *env, t_token_list *token);
void			do_execve(t_env *env, t_token_list *token);

/*----redirection & pipe*/
/*--------infile redirection*/
int				check_infile(t_command *curr, t_token_list *inredir);
int				do_inredir(t_command *curr, t_token_list *inredir);
void			read_here_doc(t_token *currtok, int *fd);
int				do_here_doc(t_env *envlst, t_command *command);
/*--------outfile redirection*/
int				open_outredir(t_token *tail, int fd);
int				make_outfile(t_env *envlst, t_command *commandlst);
/*--------pipe*/
int				no_pipe(t_env *envlst, t_token_tree *toktree, \
							t_command *curr, t_fd *fd);
int				do_pipe(t_env *envlst, t_token_tree *toktree, \
							t_command *curr, t_fd *fd);

/*minishell builtins*/
void			if_builtin(t_env *envlst, t_token_list *toklst, \
							int command_num);
/*----env*/
void			print_one_env(t_envnode *node, char value_c);
int				do_env(t_token_list *toklst, t_env *envlst);
char			*search_key(t_env *envlst, char *key);
/*----unset*/
int				do_unset(t_token_list *unset_token, t_env *envlst);
/*----pwd*/
int				do_pwd(void);
/*----echo*/
int				do_echo(t_token_list *echo_token);
/*----export*/
int				show_shell_var_asscending(t_env *envlst);
int				do_export(t_token_list *export_token, t_env *envlst);
/*----cd*/
int				do_cd(t_token_list *cd_token, t_env *envlst);
/*----exit*/
int				do_exit(t_env *envlst, t_token_list *token);

#endif
