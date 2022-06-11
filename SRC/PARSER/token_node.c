/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:32:41 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/11 16:23:22 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

t_token	*create_token(char	*word, enum e_token_type type)
{
	t_token	*new_tok;

	if (type > e_heredoc || type < e_word)
		return (NULL);
	new_tok = ft_calloc(1, sizeof(t_token));
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
		new_tok->type = type;
	}
	return (new_tok);
}

void	free_token(t_token *tok)
{
	if (tok)
		free(tok->text);
	free (tok);
}
