#ifndef IGUI_HPP

#define IGUI_HPP

enum	eEvents {KEY_PRESSED, ESCAPE, P, ADD, SUBTRACT, ENTER, UP, LEFT, DOWN, RIGHT, WASD, ARROWS, WINDOW_CLOSED, GUI_SFML, GUI_SDL, GUI_ALLEGRO, GUI_GLFW};
enum	eColor {WHITE, CYAN};

class IGUI
{
public:
	virtual bool	is_ON(void) = 0;
	virtual bool	poll_event(void) = 0;
	virtual void	display_window(void) = 0;
	virtual void	close_window(void) = 0;
	virtual void	clear_window(void) = 0;
	virtual int		event_type(void) = 0;
	virtual int		key_code(void) = 0;
	virtual int		get_key_code(void) = 0;
	virtual void	set_score1_string(const std::string &str) = 0;
	virtual void	set_score2_string(const std::string &str) = 0;
	virtual void	set_speed_string(const std::string &str) = 0;
	virtual void	set_winner_string(const std::string &str) = 0;
	virtual void	display_winner_string(void) = 0;
	virtual void	initiate_menu_text(int line, int dif, int players) = 0;
	virtual void	set_menu_string(int line, const std::string &str) = 0;
	virtual void	set_string_color(int line, eColor color) = 0;
	virtual void	draw_menu(void) = 0;
	virtual void	draw(void) = 0;
};

#endif