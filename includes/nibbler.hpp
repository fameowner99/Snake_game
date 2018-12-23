/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nibbler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 20:08:19 by anesteru          #+#    #+#             */
/*   Updated: 2018/10/14 20:08:20 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_HPP
# define NIBBLER_HPP


# include <iostream>
# include <deque>
# include <dlfcn.h>

# include "ISound.hpp"
# include "IGUI.hpp"
# include "snake.hpp"
# include <chrono>

# define TIME_PER_FRAME 200000
# define TIME_FOOD_SPAWN 1000000

enum	ePosition	{LEFT_POS, MIDLE_POS, RIGHT_POS};
enum	eCells		{BACKGROUND, SNAKE_BODY, SNAKE_HEAD, FOOD, BONUS_FOOD, WALL};


void	spawn_walls(int *level, int snake1_head, int snake2_head, int width, int size, int dif);
void	spawn_food(int level_size, int *level, eCells food);
void	start_menu(IGUI *&gui, int &p, int &dif, void *&handler, int height, int width, int *level);
void	destroy(IGUI *gui, void *handle);
void	change_library(IGUI *gui, int gui_key, void *&handle_gui);
IGUI	*create(void *handle, int *level, int width, int height);

#endif
