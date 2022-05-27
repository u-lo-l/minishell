#ifndef MINISHELL_DATASTRUCTURE_H
# define MINISHELL_DATASTRUCTURE_H

/*global variable*/

/*read line*/
typedef struct	s_input
{
	char	*cmd;
	int		start_i;
	int		curr_i;
}			t_input;


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
}						t_token;

typedef struct s_token_list
{
	int		num_of_tokens;
	t_token	*head;
	t_token	*tail;
}			t_token_list;

typedef struct s_command
{
	t_token_list		*simple_command;
	t_token_list		*input_redir;
	t_token_list		*output_redir;
	t_token_list		*here_doc;
	struct s_command	*next_cmd;
}						t_command;

typedef struct s_token_tree
{
	int			num_of_commands;
	t_command	*head_cmd;
	t_command	*tail_cmd;
}				t_token_tree;

/* env list */

typedef struct s_envnode
{
	char		*key;
	char		*value;
	struct s_envnode	*nextnode;	// 다음 인덱스의 환경변수
}   t_envnode;

typedef struct s_env
{
	int			element;	// 환경변수 개수
	t_envnode	*phead;	// 헤드노드
	t_envnode	*ptail; // 꼬리노드
}   t_env;

/**/

/**/

/**/

/**/

/**/

/**/

/**/

#endif