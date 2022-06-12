/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:45:36 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/11 20:41:10 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/minishell.h"
#include <stdlib.h>
#include <termios.h>

static void test()
{
	printf("test success\n");
}

int	is_eof_token(t_token *tok)
{
	if (tok->text == NULL)
		return (TRUE);
	return (FALSE);
}
static void	print_token_type(enum e_token_type type)
{
	if (type == e_word)
		printf("e_word");
	else if (type == e_outrdr)
		printf("e_outrdr");
	else if (type == e_appendrdr)
		printf("e_appendrdr");
	else if (type == e_inrdr)
		printf("e_inrdr");
	else if (type == e_heredoc)
		printf("e_heredoc");
}
void	print_token_list(t_token_list *lst)
{
	t_token	*curr;

	if (lst)
	{	
		curr = lst->head;
		printf("%d tokens |", lst->num_of_tokens);
		while (curr)
		{
			if (is_eof_token(curr))
				printf("EOF_TOK\n");
			else
			{
				printf("\033[2m->\033[0m");
				printf("[");
				print_token_type(curr->type);
				printf(":%s]", curr->text);
			}
			curr = curr->next;
		}
	}
	printf("\n");
}

void	print_command(t_command *command)
{
	printf("========COMMAND========\n");
	printf("├▪ SIM_CMD\t: ");
	print_token_list(command->simple_command);
	printf("├▪ IN_REDIR\t: ");
	print_token_list(command->input_redir);
	printf("├▪ OUT_REDIR\t: ");
	print_token_list(command->output_redir);
	printf("├▪ HERE_DOC\t: ");
	print_token_list(command->here_doc);
	printf("└▪ REDIRECTION\t: ");
	print_token_list(command->redirection);
	printf("\n");
}

void	print_token_tree(t_token_tree *token_tree)
{
	t_command	*command;

	if (token_tree == NULL)
		return ;
	printf("Num of Commands : %d\n", token_tree->num_of_commands);
	command = token_tree->head_cmd;
	while (command != NULL)
	{
		print_command(command);
		command = command->next_cmd;
	}
}

static int	init_shell(int argc, char **argv, struct termios *atr)
{
	struct termios	temp_attr;

	if (argc > 1 || argv[1] != NULL)
		return (return_err("unexpected err : invalid arguments", FALSE));
	if (set_signal_handler() == FALSE)
		return (return_err("unexpected err : signal handler fail", FALSE));
	if (isatty(0) == FALSE)
		return (return_err("unexpected err : is not a tty", FALSE));
	if (tcgetattr(0, atr) == -1)
		return (return_err("unexpected err : cannot get tty attr", FALSE));
	temp_attr = *atr;
	temp_attr.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &temp_attr) == -1)
		return (return_err("unexpected err : cannot set tty attr", FALSE));
	return (TRUE);
}

static int	finish_shell(t_env *envlst, struct termios *origin_atr)
{
	if (envlst)
		free_env_list(envlst);
	if (isatty(0) == FALSE)
		return (FALSE);
	tcsetattr(0, TCSANOW, origin_atr);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_input			*input;
	t_env			*envlst;
	t_token_tree	*cmd_token_tree;
	struct termios	origin_attr;

	if (init_shell(argc, argv, &origin_attr) == FALSE)
		exit (1);
	envlst = env_list(envp);
	if (envlst == NULL)
		exit (return_err("unexpected error : invalid envp", 1));
	while (1)
	{
		input = read_command("mini >> ");
		if (input == NULL)
			break ;
		cmd_token_tree = tokenize_and_parsing(input, envlst);
		free(input->cmd);
		free(input);
		if (cmd_token_tree == NULL)
			envlst->error = return_err("err : Bad Syntax!", 1);
		else if (cmd_token_tree->num_of_commands != 0)
		{
			execute_command(envlst, cmd_token_tree);
			print_token_tree(cmd_token_tree);
			test();
		}
		free_token_tree(cmd_token_tree);
	}
	return (finish_shell(envlst, &origin_attr));
}
