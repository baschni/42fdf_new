/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 06:57:53 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/19 16:56:14 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# define EVENT_CLOSE 17

int	close_window(void *vscene);
int	resize_window(void *vscene);
void	connect_events(t_scene *scene);

#endif