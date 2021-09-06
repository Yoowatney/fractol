/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 20:31:41 by yoyoo             #+#    #+#             */
/*   Updated: 2021/05/17 16:24:33 by yoyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*fix;
	t_list	*curr;

	if (!lst)
		return (NULL);
	fix = (t_list *)ft_lstnew(f(lst->content));
	if (!fix)
		return (NULL);
	curr = fix;
	lst = lst->next;
	while (lst)
	{
		curr->next = (t_list *)ft_lstnew(f(lst->content));
		if (!curr->next)
		{
			ft_lstclear(&fix, del);
			return (NULL);
		}
		curr = curr->next;
		lst = lst->next;
	}
	return (fix);
}
