/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:51:27 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/07 20:11:25 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_redirect(t_shell *shell, t_mlist *list)
{
	int	n;
	int	out;

	n = 0;
	out = 0;
	while (list->argv[n])
	{
		if (list->argv[n][0] == '<')
			out = ft_redirect_input(shell, list, n);
		else if (list->argv[n][0] == '>')
			out = ft_redirect_output(list, n);
		else
			n++;
		if (out != 0)
			return (out);
	}
	return (out);
}
