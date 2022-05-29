/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 06:14:52 by dkim2             #+#    #+#             */
/*   Updated: 2022/05/29 23:43:14 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (TRUE);
	return (FALSE);
}

int	is_redir_op(char c)
{
	if (c == '<' || c == '>')
		return (TRUE);
	return (FALSE);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}

int	is_special_char(char c)
{
	if (c == '|' || c == '"' || c == '$' || \
		c == '<' || c == '>' || c == '\'' || c == 0)
		return (TRUE);
	return (FALSE);
}
