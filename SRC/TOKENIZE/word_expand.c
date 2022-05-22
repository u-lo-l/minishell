/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:32:33 by dkim2             #+#    #+#             */
/*   Updated: 2022/05/22 18:32:34 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdio.h>
#include <stdlib.h>

char	*word_expansion(t_input	*input, t_env *env_list)
{
	char	*key;
	char	*value;

	key = NULL;
	while (ft_isalnum(input->cmd[input->curr_i]) || \
			input->cmd[input->curr_i] == '_')
		input->curr_i++;
	input->curr_i--;
	make_word(input, &key);
	input->start_i = ++input->curr_i;
	if (key == NULL)
		return (NULL);
	value = search_key(env_list, key);
	free(key);
	return (value);
}
/*
int main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*val;

	if (argc != 1 || argv == NULL || envp == NULL)
		return (1);
	env = env_list(envp);
	if (env == NULL)
		return (1);
	// display_env(env);
	// val = word_expansion(env, "PATH");
	val = search_key(env, "SHELL");
	printf("<%s>\n", val);
	return (0);
}*/