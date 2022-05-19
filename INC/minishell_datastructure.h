#ifndef MINISHELL_DATASTRUCTURE_H
# define MINISHELL_DATASTRUCTURE_H

/*global variable*/

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

/**/

/**/

/**/

/**/

/**/

/**/

/**/

/**/

#endif
