/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:58:50 by anesteru          #+#    #+#             */
/*   Updated: 2018/11/01 19:58:52 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "snake.hpp"

Snake::Snake(int width, int height, int *level, int position, ISound *sound) :
	_level(level), _width(width), _height(height), _position(position),
	_sound(sound), _score(0), _alive(true)
{
	reset();
}

Snake::~Snake(void) {}

void	Snake::reset(void)
{
	this->_score = 0;
	this->_alive = true;
	this->_direction = UP;
	if (this->_position == MIDLE_POS)
		this->_head = this->_height / 2 * this->_width + this->_width / 2;
	else if (this->_position == LEFT_POS)
		this->_head = this->_height / 2 * this->_width + this->_width / 4;
	else if (this->_position == RIGHT_POS)
		this->_head = this->_height / 2 * this->_width + this->_width / 1.3;
	this->_snake_body.push_front(this->_head);
	this->_snake_body.push_back(this->_head + this->_width);
	this->_snake_body.push_back(this->_head + this->_width * 2);
	this->_snake_body.push_back(this->_head + this->_width * 3);
	for (size_t i = 0; i < this->_snake_body.size(); i++)
	{
		if (this->_level[this->_snake_body[i]] == FOOD)
		{
			spawn_food(this->_width * this->_height, this->_level, FOOD);
			break ;
		}
	}
	this->_level[this->_snake_body[0]] = SNAKE_HEAD;
	this->_level[this->_snake_body[1]] = SNAKE_BODY;
	this->_level[this->_snake_body[2]] = SNAKE_BODY;
	this->_level[this->_snake_body[3]] = SNAKE_BODY;
}

void	Snake::erase(void)
{
	while (this->_snake_body.size() > 0)
	{
		this->_level[this->_snake_body.front()] = BACKGROUND;
		this->_snake_body.pop_front();
	}
}

bool	Snake::is_out_of_bounds(void)
{
	return (this->_head < 0 || this->_head >= this->_width * this->_height
		|| (this->_direction == LEFT  && (this->_head + 1) % this->_width == 0)
		|| (this->_direction == RIGHT && (this->_head)     % this->_width == 0));
}

int		Snake::get_head(void)
{
	return this->_snake_body.front();
}

int		Snake::get_score(void)
{
	return this->_score;
}

bool	Snake::is_alive(void)
{
	return this->_alive;
}

bool	Snake::move(int key)
{
	if (this->_direction == UP)
	{
		if (key == RIGHT)
		{
			this->_head += 1;
			this->_direction = RIGHT;
		}
		else if (key == LEFT)
		{
			this->_head -= 1;
			this->_direction = LEFT;
		}
		else
			this->_head -= this->_width;
	}
	else if (this->_direction == DOWN)
	{
		if (key == RIGHT)
		{
			this->_head += 1;
			this->_direction = RIGHT;
		}
		else if (key == LEFT)
		{
			this->_head -= 1;
			this->_direction = LEFT;
		}
		else
			this->_head += this->_width;
	}
	else if (this->_direction == RIGHT)
	{
		if (key == UP)
		{
			this->_head -= this->_width;
			this->_direction = UP;
		}
		else if (key == DOWN)
		{
			this->_head += this->_width;
			this->_direction = DOWN;
		}
		else
			this->_head += 1;
	}
	else if (this->_direction == LEFT)
	{
		if (key == UP)
		{
			this->_head -= this->_width;
			this->_direction = UP;
		}
		else if (key == DOWN)
		{
			this->_head += this->_width;
			this->_direction = DOWN;
		}
		else
			this->_head -= 1;
	}
	if ((this->_level[this->_head] != BACKGROUND && this->_level[this->_head] != FOOD
	&& this->_level[this->_head] != BONUS_FOOD) || is_out_of_bounds())
	{
		if (this->_level[this->_head] == SNAKE_BODY || this->_level[this->_head] == SNAKE_HEAD)
			this->_sound->snake_crash_play();
		else
			this->_sound->wall_crash_play();
		erase();
		this->_alive = false;
		return false;
	}
	else
	{
		if (this->_level[this->_head] != FOOD && this->_level[this->_head] != BONUS_FOOD)
		{
			this->_level[this->_snake_body[this->_snake_body.size() - 1]] = 0;
			this->_snake_body.pop_back();
		}
		else
		{
			this->_score += (this->_level[this->_head] == FOOD ? 1 : 3);
			if (this->_level[this->_head] == FOOD)
			{
				this->_sound->apple_crunch_play();
			    spawn_food(this->_width * this->_height, this->_level, FOOD);
			}
			else
				this->_sound->apple_crunch_bonus_play();
		}
		this->_level[this->_snake_body.front()] = SNAKE_BODY;
		this->_level[this->_head] = SNAKE_HEAD;
		this->_snake_body.push_front(this->_head);
	}
	return true;
}
