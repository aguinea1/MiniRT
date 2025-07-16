/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:53:31 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/16 13:20:27 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"
//anade las etructuras que quieras para hacerles free y ya, en teoria deberia funcionar
static void	delete(void *content)
{
	free(content);
}

static void	my_clear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		delete((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	free_all(t_list **cyl, t_list **plane, t_list **sphere, t_list **light)
{
	my_clear(sphere, delete);
	my_clear(plane, delete);
	my_clear(cyl, delete);
	my_clear(light, delete);
}
