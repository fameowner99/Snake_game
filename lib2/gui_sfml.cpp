#include "gui_sfml.hpp"

GUI::GUI(int *level, int width, int height) : _width(width), _height(height),
_map(level, width, height), _window(sf::VideoMode(width * 100, height * 100 + 100), "SSSnake")
{
	if (!this->_font.loadFromFile("resources/arial.ttf"))
		throw std::runtime_error("font not found");
	if (!this->_map.load("resources/6_100.png"))
		throw std::runtime_error("textures not found");
	initiate_menu_text(0, 0, 1);
	initiate_text();

}

GUI::~GUI(void) {}

void	GUI::initiate_menu_text(int line, int dif, int players)
{
	this->_menu[0].setFont(this->_font);
	this->_menu[0].setPosition(200, this->_height *  25);
	this->_menu[0].setCharacterSize(65);
	this->_menu[0].setString("Start");
	this->_menu[0].setFillColor(sf::Color::Cyan);

	this->_menu[1].setFont(this->_font);
	this->_menu[1].setPosition(200, this->_height *  25 + 100);
	this->_menu[1].setCharacterSize(65);
	if (dif == 0)
		this->_menu[1].setString("Difficulty     Easy");
	else if (dif == 1)
		this->_menu[1].setString("Difficulty     Medium");
	else 
		this->_menu[1].setString("Difficulty     Hard");
	this->_menu[2].setFont(this->_font);
	this->_menu[2].setPosition(200, this->_height *  25 + 200);
	this->_menu[2].setCharacterSize(65);
	if (players == 1)
		this->_menu[2].setString("Players      1");
	else
		this->_menu[2].setString("Players      2");

	this->_menu[3].setFont(this->_font);
	this->_menu[3].setPosition(200, this->_height *  25 + 300);
	this->_menu[3].setCharacterSize(65);
	this->_menu[3].setString("Exit");
	this->_menu[0].setFillColor(sf::Color::White);
	this->_menu[1].setFillColor(sf::Color::White);
	this->_menu[2].setFillColor(sf::Color::White);
	this->_menu[3].setFillColor(sf::Color::White);
	this->_menu[line].setFillColor(sf::Color::Cyan);
}

void	GUI::set_menu_string(int line, const std::string &str)
{
	this->_menu[line].setString(str);
}

void	GUI::set_string_color(int line, eColor color)
{
	if (color == CYAN)
		this->_menu[line].setFillColor(sf::Color::Cyan);
	else if (color == WHITE)
		this->_menu[line].setFillColor(sf::Color::White);
}

void	GUI::draw_menu(void)
{
	this->_window.draw(this->_menu[0]);
	this->_window.draw(this->_menu[1]);
	this->_window.draw(this->_menu[2]);
	this->_window.draw(this->_menu[3]);
}

void	GUI::initiate_text(void)
{
	this->_score1.setFont(this->_font);
	this->_score1.setCharacterSize(65);
	this->_score1.setPosition(20, this->_height * 100 + 10);

	this->_speed.setFont(this->_font);
	this->_speed.setCharacterSize(65);
	this->_speed.setPosition(this->_width * 50 - 210, this->_height * 100 + 10);

	this->_score2.setFont(this->_font);
	this->_score2.setCharacterSize(65);
	this->_score2.setPosition(this->_width * 100 - 260, this->_height * 100 + 10);

	this->_winner.setFont(this->_font);
	this->_winner.setCharacterSize(220);
	this->_winner.setPosition(this->_width * 50 - 500, 0);
}

bool	GUI::is_ON(void)
{
	return this->_window.isOpen();
}

bool	GUI::poll_event(void)
{
	return this->_window.pollEvent(this->_event);
}

void	GUI::display_window(void)
{
	this->_window.display();
}

void	GUI::close_window(void)
{
	this->_window.close();
}

void	GUI::clear_window(void)
{
	this->_window.clear();
}

int		GUI::event_type(void)
{
	if (this->_event.type == sf::Event::KeyPressed)
		return KEY_PRESSED;
	else if (this->_event.type == sf::Event::Closed)
		return WINDOW_CLOSED;
	return -1;
}

int		GUI::key_code(void)
{
	if (this->_event.key.code == sf::Keyboard::Numpad1)
		return (GUI_SDL);
	else if (this->_event.key.code == sf::Keyboard::Escape)
		return ESCAPE;
	else if (this->_event.key.code == sf::Keyboard::P)
		return P;
	else if (this->_event.key.code == sf::Keyboard::Add)
		return ADD;
	else if (this->_event.key.code == sf::Keyboard::Subtract)
		return SUBTRACT;
	else if (this->_event.key.code == sf::Keyboard::Enter)
		return ENTER;
	else if (this->_event.key.code >= sf::Keyboard::Left
		&&   this->_event.key.code <= sf::Keyboard::Down)
		return ARROWS;
	else if (this->_event.key.code == sf::Keyboard::W
		||   this->_event.key.code == sf::Keyboard::A
		||   this->_event.key.code == sf::Keyboard::S
		||   this->_event.key.code == sf::Keyboard::D)
		return WASD;
	return -1;
}

int		GUI::get_key_code(void)
{
	if (this->_event.key.code == sf::Keyboard::W
	||  this->_event.key.code == sf::Keyboard::Up)
		return UP;
	if (this->_event.key.code == sf::Keyboard::A
	||  this->_event.key.code == sf::Keyboard::Left)
		return LEFT;
	if (this->_event.key.code == sf::Keyboard::S
	||  this->_event.key.code == sf::Keyboard::Down)
		return DOWN;
	if (this->_event.key.code == sf::Keyboard::D
	||  this->_event.key.code == sf::Keyboard::Right)
		return RIGHT;
	return -1;
}

void	GUI::set_score1_string(const std::string &str)
{
	this->_score1.setString("s1:" + str);
	this->_window.draw(this->_score1);
}

void	GUI::set_score2_string(const std::string &str)
{
	this->_score2.setString("s2:" + str);
	this->_window.draw(this->_score2);
}

void	GUI::set_speed_string(const std::string &str)
{
	this->_speed.setString("speed: " + str);
	this->_window.draw(this->_speed);
}

void	GUI::set_winner_string(const std::string &str)
{
	this->_winner.setString(str);
}

void	GUI::display_winner_string(void)
{
	this->_window.draw(this->_winner);
}

void	GUI::draw(void)
{
	this->_map.redraw();
	this->_window.draw(this->_map);
}

extern "C" GUI		*create_object(int *level, int width, int height)
{
	return new GUI(level, width, height);
}

extern "C" void		destroy_object(GUI *gui)
{
	delete gui;
}

