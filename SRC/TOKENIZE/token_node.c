/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:32:41 by dkim2             #+#    #+#             */
/*   Updated: 2022/05/22 18:38:20 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

t_token	*create_token(char	*word)
{
	t_token	*new_tok;

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
		new_tok->text_len = ft_strlen(word);
	}
	return (new_tok);
}

int	is_eof_token(t_token *tok)
{
	if (tok->text == NULL)
		return (TRUE);
	return (FALSE);
}

void	free_token(t_token *tok)
{
	if (tok)
		free(tok->text);
	free (tok);
}
