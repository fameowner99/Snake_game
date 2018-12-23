/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:59:04 by anesteru          #+#    #+#             */
/*   Updated: 2018/11/01 19:59:05 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
# define SNAKE_HPP

# include "nibbler.hpp"

class Snake
{
	public:

		Snake(int width, int height, int *level, int position, ISound *sound);
		~Snake(void);

		void	reset(void);
		void	erase(void);
		int		get_head(void);
		int		get_score(void);
		bool	is_out_of_bounds(void);
		bool	is_alive(void);
		bool	move(int key);

	private:

		int					*_level;
		int					_width;
		int					_height;
		int					_position;
		ISound				*_sound;
		int					_score;
		int					_direction;
		int					_head;
		bool				_alive;
		std::deque<int>		_snake_body;
};

#endif
