/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:32:50 by dkim2             #+#    #+#             */
/*   Updated: 2022/05/27 14:43:14 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

void	skip_space(t_input *input)
{
	if (input == NULL)
		return ;
	while (input->cmd[input->curr_i] == ' ' || \
			input->cmd[input->curr_i] == '\t')
	{
		input->curr_i++;
		input->start_i = input->curr_i;
	}
}

int	split_token(t_token_tree *toktree, t_input *input, char **word, enum e_token_type type)
{
	t_token	*token;

	if (!toktree || !toktree->tail_cmd || !input || !word)
		return (FALSE);
	// if (input->curr_i == input->start_i)
		// return (TRUE);
	input->curr_i--;
	make_word(input, word);
	token = create_token(*word, type);
	free(*word);
	*word = NULL;
	add_token_to_command(toktree->tail_cmd, token);
	input->curr_i++;
	skip_space(input);
	if (input->cmd[input->curr_i] == 0)
		return (FALSE);
	return (TRUE);
}

void	make_word(t_input *input, char **word)
{
	char	*word_n;

	if (!input)
		return ;
	if (*word == NULL)
		*word = ft_strndup(input->cmd + input->start_i, \
						input->curr_i - input->start_i + 1);
	else
	{
		word_n = malloc(ft_strlen(*word) + input->curr_i - input->start_i + 2);
		ft_strlcpy(word_n, *word, ft_strlen(*word) + 1);
		free(*word);
		*word = ft_strndup(input->cmd + input->start_i, \
						input->curr_i - input->start_i + 1);
		if (*word == NULL)
			return ;
		ft_strlcat(word_n, *word, ft_strlen(*word) + ft_strlen(word_n) + 1);
		free(*word);
		*word = word_n;
	}
}

void	quote_case(t_input *input, char **word, t_env *env_list)
{
	char	quote;

	quote = input->cmd[input->curr_i];
	input->curr_i--;
	make_word(input, word);
	input->curr_i += 2;
	input->start_i = input->curr_i;
	while (input->cmd[input->curr_i] != quote)
	{
		if (quote == '"' && input->cmd[input->curr_i] == '$')
			dollar_case(input, word, env_list);
		else
			input->curr_i++;
	}
	input->curr_i--;
	make_word(input, word);
	input->curr_i += 2;
	input->start_i = input->curr_i;
}

void	dollar_case(t_input *input, char **word, t_env *env_list)
{
	char	*expand;
	char	*new_word;

	input->curr_i--;
	make_word(input, word);
	input->curr_i += 2;
	input->start_i = input->curr_i;
	while (ft_isalnum(input->cmd[input->curr_i]) || \
			input->cmd[input->curr_i] == '_')
		input->curr_i++;
	expand = word_expansion(input, env_list);
	input->start_i = input->curr_i;
	new_word = ft_strjoin(*word, expand);
	free(*word);
	*word = new_word;
}
