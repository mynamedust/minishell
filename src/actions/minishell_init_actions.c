/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init_actions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:31:45 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/19 17:09:37 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_action(int sig)
{
	(void) sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 1;
}

void	ft_sigint(int signum)
{
	(void) signum;
	printf("\n");
	g_exit_status = 130;
}

void	ft_sigquit(int sig)
{
	(void) sig;
	printf("Quit\n");
	g_exit_status = 0;
}

void	ft_quit(int sig)
{
	(void) sig;
	rl_redisplay();
	g_exit_status = 0;
}

void	ctrl_d_handler(char *str)
{
	if (!str)
	{
		printf("\033[1A\033[12Cexit\n");
		exit(0);
	}
}
