/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:47:57 by gdaignea          #+#    #+#             */
/*   Updated: 2023/10/18 15:29:40 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tab;
	t_list	*temp;

	if (!lst)
		return (NULL);
	tab = ft_lstnew(f(lst->content));
	if (!tab)
		return (NULL);
	temp = tab;
	lst = lst->next;
	while (lst)
	{
		tab->next = ft_lstnew(f(lst->content));
		if (!tab->content)
		{
			ft_lstclear(&temp, del);
			return (NULL);
		}
		lst = lst->next;
		tab = tab->next;
	}
	return (temp);
}
