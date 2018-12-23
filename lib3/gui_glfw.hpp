#ifndef GUI_GLFW_HPP

#define GUI_GLFW_HPP

#include <string>
#include "IGUI.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <GLUT/glut.h>
#include <FTGL/ftgl.h>
#include <iostream>
#include <random>

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
		GLFWwindow		*window;
		int				colors[4];
		std::string 	text_menu[4];
		int 			*_level;
		int 			_width;
		int 			_height;
		std::string 	_p1;
		std::string 	_p2;
		std::string 	_winner;
		std::string 	_speed;
		FTGLPixmapFont font_menu;
		FTGLPixmapFont font;
		FTGLPixmapFont font_winner;
		float square_w_size;
		float square_h_size;
		void		draw_p1();
		void		draw_p2();
		void		draw_speed();

};

extern "C" GUI		*create_object(int *level, int width, int height);

extern "C" void		destroy_object(GUI *gui);

#endif