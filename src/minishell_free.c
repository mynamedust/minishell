/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:58:06 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/18 00:04:11 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_2d_array_with_null(char **array)
{
	int	n;

	if (!array)
		return ;
	n = 0;
	while (array[n])
	{
		free(array[n]);
		n++;
	}
}

void	ft_list_clear(t_mlist **list)
{
	int	n;

	if (!list || !*list)
		return ;
	n = 0;
	while ((*list)->argv && (*list)->argv[n])
	{
		free((*list)->argv[n]);
		n++;
	}
	if ((*list)->argv)
		free((*list)->argv);
	if ((*list)->command)
		free((*list)->command);
	if ((*list)->bin)
		free((*list)->bin);
	free(*list);
	*list = NULL;
}

void	ft_free_2_linked_list(t_mlist **list)
{
	while (*list)
	{
		if ((*list)->next)
		{
			*list = (*list)->next;
			ft_list_clear(&(*list)->prev);
		}
		else
			ft_list_clear(list);
	}
	*list = NULL;
}
