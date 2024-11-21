/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:42:12 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/21 14:40:42 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_CAMERA_BONUS_H
# define MOVE_CAMERA_BONUS_H

void	zoom(int in_or_out, t_scene *scene);
void	traverse(int in_cam_dir, int forward_or_backward, t_scene *scene);
void	change_projection(t_scene *scene);
void	reset_view(t_scene *scene);
void	roll_camera(int right_or_left, t_scene *scene);
void change_view_angle(int enlarge_or_reduce, t_scene *scene);
void	rotate_camera_x_y(int right_or_left, t_scene *scene);
void	rotate_camera_z(int up_or_down, t_scene *scene);


# define SCALE_ON_ZOOM 1.1
# define ANGLE_ROLL 5
# define ANGLE_FOV 10


#endif