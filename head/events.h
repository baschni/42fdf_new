/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 06:57:53 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/20 23:20:10 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "scene.h"

# define EVENT_CLOSE 17
# define EVENT_KEY_UP 3

# define KEY_CODE_ESC 65307

# define KEY_CODE_W 119
# define KEY_CODE_S 115
# define KEY_CODE_A 97
# define KEY_CODE_D 100

# define KEY_CODE_Q 113
# define KEY_CODE_E 101
# define KEY_CODE_O 111
# define KEY_CODE_U 117

# define KEY_CODE_I 105
# define KEY_CODE_K 107
# define KEY_CODE_J 106
# define KEY_CODE_L 108

# define KEY_CODE_P 112
# define KEY_CODE_R 114


# define MOUSE_WHEEL_IN 4
# define MOUSE_WHEEL_OUT 5

void	connect_events(t_scene *scene);
int	close_window(void *vscene);

#endif