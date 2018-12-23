#ifndef ISOUND_HPP

#define ISOUND_HPP

class ISound
{
	public:
		virtual void	apple_crunch_play(void) = 0;
		virtual void	apple_crunch_bonus_play(void) = 0;
		virtual void	snake_crash_play(void) = 0;
		virtual void	wall_crash_play(void) = 0;
		virtual void	background_song_play(void) = 0;
};

#endif