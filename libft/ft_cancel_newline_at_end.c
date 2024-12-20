/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cancel_newline_at_end.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:59:14 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/13 17:36:04 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_cancel_newline_at_end(char *line)
{
	char	*i;

	i = line;
	while (*i)
		i++;
	if (i == line)
		return ;
	i--;
	if (*i == '\n')
		*i = '\0';
}
