/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:54:30 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/09 20:02:44 by dkim2            ###   ########.fr       */
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
int				unset_signal_handler(void);

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
int				delimit_and_add_token_to_tree(t_token_tree *toktree, \
											char **pword, \
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
void			free_token_tree(t_token_tree *token_tree);
int				add_token_to_tree(t_token_tree *toktree, t_token *tok);
int				add_one_empty_command(t_token_tree *token_tree);
void			print_token_tree(t_token_tree *token_tree);

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
char			*get_path(t_env *env, char **command_list, int num);
char			**split_path(t_env *env);
char			**get_command_list(t_token_list *token);
void			pipe_do_execve(t_env *env, t_token_list *token);
void			do_execve(t_env *env, t_token_list *token);
void			child_err(t_env *envlst, char *command);
void			when_child(t_env *env, char **command_list);
void			after_execute(t_token_tree *toktree, t_fd *fd);

/*----redirection & pipe*/
int				check_infile(t_command *curr, t_token_list *inredir);
int				do_inredir(t_command *curr, t_token_list *inredir);
int				do_here_doc(t_command *command);
void			push_outfile(int fd, int *red_fd);
int				open_outredir(t_token *tail, int fd);
void			do_outredir(t_command *commamdlst, int *red_fd);
void			make_outfile(t_command *commandlst);
int				no_pipe_util1(t_command *curr, int *std_fd);
void			no_pipe_util2(t_env *envlst, t_command *curr, int *std_fd);
int				no_pipe(t_env *envlst, t_token_tree *toktree, \
						t_command *curr, t_fd *fd);

void			read_here_doc(t_token *currtok, int *fd);
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
int				insert_to_heap(t_envnode **heap, t_envnode *node, int index);
t_envnode		*pop_from_heap(t_envnode **heap, int curr_elemnt_count);
int				show_shell_var_asscending(t_env *envlst);
int				do_export(t_token_list *export_token, t_env *envlst);
/*----cd*/
int				do_cd(t_token_list *cd_token, t_env *envlst);
/*----exit*/
int				do_exit(t_token_list *token);

#endif
