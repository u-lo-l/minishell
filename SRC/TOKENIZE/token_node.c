#include "../../INC/minishell.h"
#include <stdlib.h>

t_token	*create_token(char	*word)
{
	t_token	*new_tok;

	new_tok = ft_calloc(sizeof(t_token));
	if (new_tok == NULL)
		return (NULL);
	if (word != NULL)
	{
		new_tok->text = ft_strdup(word);
		if (new_tok->text == NULL)
		{
			free(new_tok);
			return (NULL);
		}
		new_tok->text_len = ft_strlen(word);
	}
	return (new_tok);
}

void	free_token(t_token *tok)
{
	if (!tok)
		free(tok->text);
	free (tok);
}