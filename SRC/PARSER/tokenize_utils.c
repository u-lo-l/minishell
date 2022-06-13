/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 06:01:50 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/13 21:13:39 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

void	pass_space_tab(t_input *input)
{
	while (input->cmd[input->curr_i] == ' ' || \
			input->cmd[input->curr_i] == '\t')
		input->curr_i++;
	input->start_i = input->curr_i;
}

int	set_word(t_input *input, char **pword)
{
	int		append_len;
	char	*temp;

	if (input->curr_i == input->start_i)
		return (TRUE);
	append_len = --input->curr_i - input->start_i + 1;
	if (*pword == NULL)
		*pword = ft_strndup(&input->cmd[input->start_i], append_len);
	else
	{
		if (append_len <= 0)
			return (FALSE);
		temp = malloc(sizeof(char) * (ft_strlen(*pword) + append_len + 1));
		if (temp == NULL)
			return (FALSE);
		ft_strlcpy(temp, *pword, ft_strlen(*pword) + 1);
		ft_strlcpy(temp + ft_strlen(*pword), &input->cmd[input->start_i], \
					append_len + 1);
		free(*pword);
		*pword = temp;
	}
	if (*pword == NULL)
		return (FALSE);
	input->start_i = ++input->curr_i;
	return (TRUE);
}

char	*expand_variable(t_input *input, t_env *envlst)
{
	char	*key;
	char	*value;

	key = NULL;
	if (input->cmd[input->curr_i] == '?')
	{
		value = ft_itoa(envlst->error);
		input->start_i = ++input->curr_i;
	}
	else
	{
		while (ft_strchr(" \t\"\'<>$|?\0", input->cmd[input->curr_i]) == NULL)
			input->curr_i++;
		if (set_word(input, &key) == FALSE)
			return (NULL);
		if (is_env_name(key) == FALSE)
		{
			free(key);
			return (NULL);
		}
		value = ft_strdup(search_key(envlst, key));
		free(key);
	}
	return (value);
}

int	delimit_and_add_token_to_tree(t_token_tree *toktree,
										char **pword,
										int *type)
{
	t_token	*new_token;

	if (*pword == NULL)
		return (TRUE);
	new_token = create_token(*pword, *type);
	if (new_token == NULL)
		return (FALSE);
	free(*pword);
	*pword = NULL;
	if (add_token_to_tree(toktree, new_token) == FALSE)
	{
		free_token(new_token);
		return (FALSE);
	}
	*type = WORD;
	return (TRUE);
}

int	case_dollar_util(char **pword, char *expanded_word)
{
	char	*temp;

	temp = ft_strdup(*pword);
	free (*pword);
	*pword = ft_strjoin(temp, expanded_word);
	free (expanded_word);
	free (temp);
	if (*pword == NULL)
		return (FALSE);
	return (TRUE);
}
