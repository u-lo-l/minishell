/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyoo <yyoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:52:00 by yyoo              #+#    #+#             */
/*   Updated: 2022/05/30 18:43:37 by yyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

/* env_list에 노드를 추가하는 함수 add_node와 비슷하게 동작 함 */
void	do_export(t_env *env, t_token_list *export_token)
{
	int			i;
	t_token		*curr;

	if (!env)
		return ;
	curr = export_token->head->next;
	i = env->element;
	while (curr)
	{
		add_node(curr->text, env, i);
		env->element++;
		i++;
		curr = curr->next;
	}
}
/*
int main(int argc, char **argv, char **envp)
{
	t_env *ev;
	char	**token;

	token = malloc(sizeof(char *) * 3);
	token[0] = malloc(sizeof(char) *7);
	token[1] = malloc(sizeof(char) *10);
	token[2] = malloc(sizeof(char) *10);

	(void)argc;
	(void)argv;
	ev = env_list(envp);
	do_env(ev);
	printf("\n#############################################\n\n");
	
	token[0] = "export";
	token[1] = "A=123";
	token[2] = "B=BBBB";
	
	export(ev, token);
	do_env(ev);
	printf("\n#############################################\n\n");
	printf("%s\n", ev->ptail->key);
	printf("element : %d\n", ev->element);
}
*/
