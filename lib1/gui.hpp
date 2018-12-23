#ifndef GUI_HPP
# define GUI_HPP

#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "IGUI.hpp"
#include <iostream>
#include <algorithm>



class GUI: public IGUI
{
public:
	GUI(int *level, int width, int height);
	virtual ~GUI(void);
	virtual bool	is_ON(void);
	virtual bool	poll_event(void);
	virtual void	display_window(void);
	virtual void	close_window(void);
	virtual void	clear_window(void);
	virtual int		event_type(void);
	virtual int		key_code(void);
	virtual int		get_key_code(void);
	virtual void	set_score1_string(const std::string &str);
	virtual void	set_score2_string(const std::string &str);
	virtual void	set_speed_string(const std::string &str);
	virtual void	set_winner_string(const std::string &str);
	virtual void	display_winner_string(void);
	virtual void	initiate_menu_text(int line, int dif, int players);
	virtual void	set_menu_string(int line, const std::string &str);
	virtual void	set_string_color(int line, eColor color);
	virtual void	draw_menu(void);
	virtual void	draw(void);

private:
	typedef std::chrono::high_resolution_clock Clock;
	SDL_Window   *window;
	SDL_Event     event;
	SDL_Texture* snakePart;
	SDL_Texture *snakeHead;
	SDL_Texture* food;
	SDL_Texture* food_bonus;
	SDL_Texture* wall;
	SDL_Texture	*background;
	SDL_Renderer *renderer;
	TTF_Font	*font;
	TTF_Font	*font_winner;
	TTF_Font	*font_menu;
	SDL_Texture *p1;
	SDL_Texture *p2;
	SDL_Texture *winner;
	SDL_Texture *speed;
	SDL_Texture *start;
	SDL_Texture *difficulty;
	SDL_Texture *players;
	SDL_Texture *exit_menu;
	std::string _p1;
	std::string _p2;
	std::string _winner;
	std::string _speed;
	int colors[4];
	std::string text_menu[4];


	int 	*_level;
	int 	_width;
	int 	_height;
	void	createWindow();
	bool	createTexture(const char* path, SDL_Texture *&texture);
	void	createRenderer();
	void		draw_p1();
	void		draw_p2();
	void		draw_speed();
	void		draw_objects();
	void		draw_lower_texture();
	SDL_Color white;
	SDL_Color green;

};


extern "C" GUI		*create_object(int *level, int width, int height);

extern "C" void		destroy_object(GUI *gui);

#endif
