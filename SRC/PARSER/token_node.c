/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:32:41 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/12 04:58:15 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

static t_toktype	set_type(int type)
{
	type &= 0b111;
	if (type == WORD)
		return (e_word);
	else if (type == OUTRDR)
		return (e_outrdr);
	else if (type == APNDRDR)
		return (e_appendrdr);
	else if (type == INRDR)
		return (e_inrdr);
	else
		return (e_heredoc);
}

t_token	*create_token(char	*word, int type)
{
	t_token	*new_tok;

	if ((type > (int)0b1100) || type < 0)
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
		new_tok->type = set_type(type);
	}
	return (new_tok);
}

void	free_token(t_token *tok)
{
	if (tok)
		free(tok->text);
	free (tok);
}
