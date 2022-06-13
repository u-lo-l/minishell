/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_datastructure.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyoo <yyoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:16:32 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/13 21:24:29 by yyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DATASTRUCTURE_H
# define MINISHELL_DATASTRUCTURE_H
# define TRUE 		((int)1)
# define FALSE 		((int)0)
/*token type bit field*/
# define WORD		((int)0b0000)
# define OUTRDR		((int)0b0001)
# define APNDRDR	((int)0b0010)
# define INRDR		((int)0b0011)
# define HEREDOC	((int)0b0100)
# define QUOTE		((int)0b1000)
/*read line*/
typedef struct s_input
{
	char	*cmd;
	int		start_i;
	int		curr_i;
}	t_input;

/*DS for token*/
typedef enum e_token_type
{
	e_word = 0,
	e_outrdr,
	e_appendrdr,
	e_inrdr,
	e_heredoc
}	t_toktype;

typedef struct s_token
{
	enum e_token_type	type;
	char				*text;
	struct s_token		*next;
}	t_token;

typedef struct s_token_list
{
	int		num_of_tokens;
	t_token	*head;
	t_token	*tail;
}	t_token_list;

typedef struct s_command
{
	t_token_list		*simple_command;
	t_token_list		*input_redir;
	t_token_list		*output_redir;
	t_token_list		*here_doc;
	t_token_list		*redirection;
	struct s_command	*next_cmd;
}	t_command;

typedef struct s_token_tree
{
	int			num_of_commands;
	t_command	*head_cmd;
	t_command	*tail_cmd;
}	t_token_tree;

/* env list */
typedef struct s_envnode
{
	char				*key;
	char				*value;
	struct s_envnode	*nextnode;
	struct s_envnode	*prevnode;
}	t_envnode;

typedef struct s_env
{
	int			element;
	int			error;
	t_envnode	*phead;
	t_envnode	*ptail;
}	t_env;

/* fd */
typedef struct s_fd
{
	int	std_fd[2];
	int	pipe_fd1[2];
	int	pipe_fd2[2];
	int	heredoc_fd[2];
	int	outfile;
}	t_fd;

#endif