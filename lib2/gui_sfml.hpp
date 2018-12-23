#ifndef GUI_SFML_HPP
# define GUI_SFML_HPP

# include "tilemap.hpp"
# include "IGUI.hpp"
# include <SFML/Graphics.hpp>
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

	void	initiate_text(void);

	int					_width;
	int					_height;
	TileMap				_map;
	sf::RenderWindow	_window;
	sf::Font			_font;
	sf::Text			_menu[4];
	sf::Text			_score1;
	sf::Text			_score2;
	sf::Text			_speed;
	sf::Text			_winner;
	sf::Clock			_clock1;
	sf::Clock			_clock2;
	sf::Event			_event;
};

extern "C" GUI		*create_object(int *level, int width, int height);

extern "C" void		destroy_object(GUI *gui);

#endif
