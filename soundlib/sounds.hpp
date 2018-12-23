/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 22:18:38 by anesteru          #+#    #+#             */
/*   Updated: 2018/11/01 22:18:39 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUND_HPP
# define SOUND_HPP

#include <SFML/Audio.hpp>
#include <iostream>
#include "ISound.hpp"

class	Sound: public ISound
{
public:

	Sound(void);
	virtual ~Sound(void);
	virtual void	apple_crunch_play(void);
	virtual void	apple_crunch_bonus_play(void);
	virtual void	snake_crash_play(void);
	virtual void	wall_crash_play(void);
	virtual void	background_song_play(void);

private:
	sf::SoundBuffer		_buffer[4];
	sf::Sound			_sound;
	sf::Music			_music;
};

#endif
