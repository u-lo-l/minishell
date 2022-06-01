/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:51:37 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/01 14:42:20 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

/* key 길이 측정 */
int	ft_keylen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

/* 문자열 같은지 검사하는 함수 */
int	ft_cmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] != '\n')
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str1[i] == '\0' && (str2[i] == '\n' || str2[i] == '\0'))
		return (1);
	return (0);
}

void	print_one_env(t_envnode *node, char value_c)
{
	if (!node)
		return ;
	if (node->key)
		printf("%s", node->key);
	if (node->value)
		printf("=%c%s%c", value_c, node->value, value_c);
	printf("\n");
}
