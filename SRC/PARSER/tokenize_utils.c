/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 06:01:50 by dkim2             #+#    #+#             */
/*   Updated: 2022/05/28 16:47:10 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

/*
 *	스페이스와 탭을 건너 뛰고 
 *	start index와 current index를 수정한다.
 */
void	pass_space_tab(t_input *input)
{
	while (input->cmd[input->curr_i] == ' ' || \
			input->cmd[input->curr_i] == '\t')
		input->curr_i++;
	input->start_i = input->curr_i;
}

/*
 *	curr_i가 가리키는 부분 에서 한칸 앞으로 가, 거기 까지를 word에 추가하는 함수이다.
 *	만약 curr_i == 0 이라면 처리하 단어가 없다고 판단하고 함수를 종료한다.
 *	[strSTRN  A\0]
 *	[0123456789_]
 *	[   s       ]
 *	[       c   ]
 *	시작 인덱스가 3이고 현재 인덱스가 7인 위와 같은 케이스에서
 *	pword에는 "STRN"가 추가된다.
 *	[strSTRN  A\0]
 *	[0123456789_]
 *	[         s ]
 *	[         c ]
 *	이렇게 인덱스를 이동하는 부분은 따로 처리 할 것이다.
*/
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
		while (ft_strchr(" \t\"\'<>$?\0", input->cmd[input->curr_i]) == NULL)
			input->curr_i++;
		if (set_word(input, &key) == FALSE)
			return (NULL);
		value = search_key(envlst, key);
		free(key);
	}
	return (value);
}

int	delimit_and_add_token_to_tree(t_token_tree *toktree,
										char **pword,
										enum e_token_type *type)
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
	*type = e_word;
	return (TRUE);
}
