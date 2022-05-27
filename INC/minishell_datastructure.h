#ifndef MINISHELL_DATASTRUCTURE_H
# define MINISHELL_DATASTRUCTURE_H

/*global variable*/

/*read line*/
typedef struct	s_input
{
	char	*cmd;
	int		start_i;
	int		curr_i;
}		t_input;


/*DS for token*/

enum e_token_type
{
	WORD,
	COMMAND,
	REDIR,
	PIPE
	// + alpha
};

typedef struct s_token
{
	int		text_len;
	char	*text;
}			t_token;

/* env list */

typedef struct s_envnode
{
	char		*key;
	char		*value;
	struct s_envnode	*nextnode;	// 다음 노드 포인터
	struct s_envnode	*prevnode;	// 이전 노드 포인터
}   t_envnode;

typedef struct s_env
{
	int			element;	// 환경변수 개수
	int			error;
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