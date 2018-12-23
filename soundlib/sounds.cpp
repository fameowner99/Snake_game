/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   sounds.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 21:19:41 by anesteru          #+#    #+#             */
/*   Updated: 2018/11/01 21:19:42 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sounds.hpp"

extern "C" Sound	*create_object()
{
	return new Sound;
}

extern "C" void destroy_object(Sound *sound)
{
	delete sound;
}

Sound::Sound(void)
{
	this->_buffer[0].loadFromFile("resources/apple-crunch12.wav");
	this->_buffer[1].loadFromFile("resources/apple-crunch16.wav");
	this->_buffer[2].loadFromFile("resources/lsdj15.wav");
	this->_buffer[3].loadFromFile("resources/altemark_noise.wav");
	this->_music.openFromFile("resources/dambient_8_bit_loop.ogg");
}

Sound::~Sound(void) {}

void	Sound::apple_crunch_play(void)
{
	this->_sound.setBuffer(this->_buffer[0]);
	this->_sound.setVolume(150);
	this->_sound.play();
}

void	Sound::apple_crunch_bonus_play(void)
{
	this->_sound.setBuffer(this->_buffer[1]);
	this->_sound.play();
}

void	Sound::snake_crash_play(void)
{
	this->_sound.setBuffer(this->_buffer[2]);
	this->_sound.setVolume(80);
	this->_sound.play();
}

void	Sound::wall_crash_play(void)
{
	this->_sound.setBuffer(this->_buffer[3]);
	this->_sound.setVolume(45);
	this->_sound.play();
}

void	Sound::background_song_play(void)
{
	this->_music.setLoop(true);
    this->_music.setVolume(10);
	this->_music.play();
}
