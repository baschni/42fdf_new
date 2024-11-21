/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:27:10 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/21 14:47:55 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# define PROGRAM_NAME "fdf"

# define EMSG_FILE "Error: file could not be read or empty map\n"
# define EMSG_POINT "Error: map has no edges\n"
# define EMSG_SIZE_MAX "Error: map too big\n"
# define EMSG_MEM "Error: memory could not be allocated\n"
# define EMSG_DIFFERENT_WIDTH "Error: lines have different width\n"
# define EMSG_EMPTY_LINE "Error: empty line in file\n"
# define EMSG_WRONG_Z_FORMAT "Error: z value not a number or out of bounds\n"
# define EMSG_WRONG_C_FORMAT "Error: color value not a number \
or out of bounds\n"
# define EMSG_WRONG_COMMA "Error: wrong comma in field value\n"

# define EMSG_SCENE_INIT "Error: scene could not be initialised\n"
# define EMSG_READ_EDGES "Error: edges could not be extracted from map\n"
# define EMSG_INIT_SCALE_FACTOR "Error: scale factor for parallel \
projection could not be obtained\n"

# define SEPARATOR_COORD ' '
# define SEPARATOR_COLOR ','

# define PADDING_NORMAL_SCALE 1.2
# define PADDING_PARALLEL_SCALE 1.2

# define Z_SCALE 1
# define DEFAULT_COLOR 0xFFFFFF
# define INITIAL_SCREEN_COVER 0.8

# define INIT_CAM_ANGLE 30.0

# define INIT_CAM_DIR_X 1
# define INIT_CAM_DIR_Y 1
# define INIT_CAM_DIR_Z - 3.45
//# define INIT_CAM_DIR_Z -2.5

# define DEFAULT_CAM_Y_ORIENT_X 0
# define DEFAULT_CAM_Y_ORIENT_Y 0
# define DEFAULT_CAM_Y_ORIENT_Z 1

#endif