#include "gui.hpp"

bool GUI::createTexture(const char *path, SDL_Texture *&texture)
{
	SDL_Surface *tmp;

	tmp = SDL_LoadBMP(path);
	if (!tmp)
		return (false);
	texture = SDL_CreateTextureFromSurface(renderer, tmp);

	if (texture == NULL)
		return (false);
	SDL_FreeSurface(tmp);
	return (true);
}

void GUI::createRenderer()
{
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	if (!createTexture("resources/greensquare.bmp", snakePart))
		throw std::runtime_error("Couldn't load image or create texture! (resources/greensquare.bmp)");
	if (!createTexture("resources/yellowcircle.bmp", food))
		throw std::runtime_error("Couldn't load image or create texture! (resources/yellowcircle.bmp)");
	if (!createTexture("resources/redcircle.bmp", food_bonus))
		throw std::runtime_error("Couldn't load image or create texture! (resources/redcircle.bmp)");
	if (!createTexture("resources/wall.bmp", wall))
		throw std::runtime_error("Couldn't load image or create texture! (resources/wall.bmp)");
	if (!createTexture("resources/yellowsquare.bmp", snakeHead))
		throw std::runtime_error("Couldn't load image or create texture! (resources/yellowsquare.bmp)");
	if (!createTexture("resources/background.bmp", background))
		throw std::runtime_error("Couldn't load image or create texture! (resources/background.bmp)");	
}

void GUI::createWindow()
{
	window = SDL_CreateWindow("SNAKE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		_width * 50, _height * 50 + 50, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (window == nullptr)
	{
		std::cout << "There was error initializing the window!" << std::endl
			 << SDL_GetError() << std::endl;
	}

}

GUI::GUI(int *level, int width, int height) : _level(level), _width(width), _height(height)
{

	SDL_Init( SDL_INIT_EVERYTHING );
	if (TTF_Init() < 0)
		throw std::runtime_error(TTF_GetError());
	white = {255, 255, 255, 0};
	green = {124, 252, 0, 0};
	window = nullptr;
    renderer = nullptr;
    p1 = nullptr;
    p2 = nullptr;
    winner = nullptr;
    speed = nullptr;
    start = nullptr;
    difficulty = nullptr;
    players = nullptr;
    exit_menu = nullptr;
   
	createWindow();
	createRenderer();
	font = TTF_OpenFont("resources/arial.ttf", 30);
	if (!font)
		throw std::runtime_error("Couldn't find font");
	font_menu = TTF_OpenFont("resources/arial.ttf", 45);
	if (!font_menu)
		throw std::runtime_error("Couldn't find font");
	font_winner = TTF_OpenFont("resources/arial.ttf", 60);
	if (!font_winner)
		throw std::runtime_error("Couldn't find font");
	colors[0] = 0;
	colors[1] = 0;
	colors[2] = 0;
	colors[3] = 0;
}

GUI::~GUI(void)
{
	SDL_DestroyTexture(p1);
    SDL_DestroyTexture(p2);
    SDL_DestroyTexture(speed);
    SDL_DestroyTexture(winner);
    SDL_DestroyTexture(start);
	SDL_DestroyTexture(difficulty);
	SDL_DestroyTexture(players);
	SDL_DestroyTexture(exit_menu);
	TTF_CloseFont(font);
	TTF_CloseFont(font_winner);
	TTF_CloseFont(font_menu);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void	GUI::initiate_menu_text(int line, int dif, int players)
{

	text_menu[0] = "START";
	text_menu[1] = "DIFFICULTY    ";
	if (players == 1)
		text_menu[2] = "PLAYERS    1";
	else
		text_menu[2] = "PLAYERS    2";
	text_menu[3] = "EXIT";
	if (dif == 0)
		text_menu[1] += "EASY";
	else if (dif == 1)
		text_menu[1] += "MEDIUM";
	else if (dif == 2)
		text_menu[1] += "HARD";
	colors[line] = 1;
	
	
}

void	GUI::set_menu_string(int line, const std::string &str)
{
	text_menu[line] = str;
	std::transform(text_menu[line].begin(), text_menu[line].end(),text_menu[line].begin(), ::toupper);
}

void	GUI::set_string_color(int line, eColor color)
{
	colors[line] = color;
}

void	GUI::draw_menu(void)
{

	SDL_Surface *tmp;
	
	tmp = TTF_RenderText_Solid(font_menu, text_menu[0].c_str(), colors[0] == 0 ? white : green);
	start = SDL_CreateTextureFromSurface(renderer, tmp);
	
	SDL_FreeSurface(tmp);

	tmp = TTF_RenderText_Solid(font_menu, text_menu[1].c_str(), colors[1] == 0 ? white : green);
	difficulty = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);

	tmp = TTF_RenderText_Solid(font_menu, text_menu[2].c_str(), colors[2] == 0 ? white : green);
	players = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);


	tmp = TTF_RenderText_Solid(font_menu, text_menu[3].c_str(), colors[3] == 0 ? white : green);
	exit_menu = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);

	SDL_Rect pos;
	
	SDL_QueryTexture(start, NULL, NULL, &pos.w, &pos.h);
	pos.x = _width * 50 / 2 - pos.w / 2;
	pos.y = _height * 50 / 2 - 200;
	SDL_RenderCopy(renderer, start, NULL, &pos);

	SDL_QueryTexture(difficulty, NULL, NULL, &pos.w, &pos.h);
	pos.x = _width * 50 / 2 - pos.w / 2;
	pos.y = _height * 50 / 2 - 100;
	SDL_RenderCopy(renderer, difficulty, NULL, &pos);

	SDL_QueryTexture(players, NULL, NULL, &pos.w, &pos.h);
	pos.x = _width * 50 / 2 - pos.w / 2;
	pos.y = _height * 50 / 2;
	SDL_RenderCopy(renderer, players, NULL, &pos);

	SDL_QueryTexture(exit_menu, NULL, NULL, &pos.w, &pos.h);
	pos.x = _width * 50 / 2 - pos.w / 2;
	pos.y = _height * 50 / 2 + 100;
	SDL_RenderCopy(renderer, exit_menu, NULL, &pos);

	SDL_DestroyTexture(start);
	SDL_DestroyTexture(difficulty);
	SDL_DestroyTexture(players);
	SDL_DestroyTexture(exit_menu);
	start = nullptr;
	difficulty = nullptr;
	players = nullptr;
	exit_menu = nullptr;
}


bool	GUI::is_ON(void)
{
	return (window);
}


bool	GUI::poll_event(void)
{
	return (SDL_PollEvent(&event));
}

void	GUI::display_window(void)
{
	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);
}

void	GUI::close_window(void)
{
	window = nullptr;
}

void	GUI::clear_window(void)
{
	SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

}

int		GUI::event_type(void)
{
	if (event.type == SDL_QUIT)
		return (WINDOW_CLOSED);
	else if (event.type == SDL_KEYDOWN)
		return (KEY_PRESSED);
	return (-1);

}

int		GUI::key_code(void)
{

	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			return (ESCAPE);
		else if (event.key.keysym.sym == SDLK_p)
			return (P);
		else if (event.key.keysym.sym == SDLK_KP_PLUS)
			return (ADD);
		else if (event.key.keysym.sym == SDLK_KP_MINUS)
			return (SUBTRACT);
		else if (event.key.keysym.sym == SDLK_RETURN)
			return (ENTER);
		else if (event.key.keysym.sym  == SDLK_LEFT
			||	 event.key.keysym.sym  == SDLK_RIGHT
			||	 event.key.keysym.sym  == SDLK_UP
			||	 event.key.keysym.sym  == SDLK_DOWN)
			return (ARROWS);
		else if (event.key.keysym.sym == SDLK_a
			||	 event.key.keysym.sym == SDLK_w 
			||	 event.key.keysym.sym == SDLK_s 
			||	 event.key.keysym.sym == SDLK_d)
			return (WASD);
		else if (event.key.keysym.sym == SDLK_KP_2)
			return (GUI_SFML);
	}
	return (-1);
}

int		GUI::get_key_code(void)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym  == SDLK_LEFT
		|| 	event.key.keysym.sym == SDLK_a)
			return (LEFT);
		else if (event.key.keysym.sym  == SDLK_RIGHT
		||		 event.key.keysym.sym == SDLK_d)
			return (RIGHT);
		else if (event.key.keysym.sym  == SDLK_UP
		||		 event.key.keysym.sym == SDLK_w)
			return (UP);
		else if (event.key.keysym.sym  == SDLK_DOWN
		||		 event.key.keysym.sym == SDLK_s)
			return (DOWN);
	}
	return (-1);
}

void	GUI::set_score1_string(const std::string &str)
{
	_p1 = "s1: " + str;

}

void	GUI::set_score2_string(const std::string &str)
{
	_p2 = "s2: " + str;
}

void	GUI::set_speed_string(const std::string &str)
{
	_speed = "speed " + str;
}

void	GUI::set_winner_string(const std::string &str)
{
	_winner = str;
}

void	GUI::display_winner_string(void)
{
	std::transform(_winner.begin(), _winner.end(),_winner.begin(), ::toupper);
	SDL_Surface *tmp;
	tmp = TTF_RenderText_Solid(font_winner, _winner.c_str(), white);
	winner = SDL_CreateTextureFromSurface(renderer, tmp);
	
	SDL_FreeSurface(tmp);

	SDL_Rect pos;
	 pos.y = 50;

    
	SDL_QueryTexture(winner, NULL, NULL, &pos.w, &pos.h);
	pos.x = _width * 25 - pos.w / 2;
	SDL_RenderCopy(renderer, winner, NULL, &pos);
	
}

void	GUI::draw_p1()
{
	SDL_Rect pos;
	SDL_Surface *tmp;

	tmp = TTF_RenderText_Solid(font, _p1.c_str(), white);
	p1 = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);
	pos.x = 20;
	pos.y = _height * 50 + 10;
	SDL_QueryTexture(p1, NULL, NULL, &pos.w, &pos.h);
 	SDL_RenderCopy(renderer, p1, NULL, &pos);
}

void	GUI::draw_p2()
{
	SDL_Rect pos;
	SDL_Surface *tmp;

	tmp = TTF_RenderText_Solid(font, _p2.c_str(), white);
	p2 = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);
	pos.x = _width * 50 - 120;
	pos.y = _height * 50 + 10;
	SDL_QueryTexture(p2, NULL, NULL, &pos.w, &pos.h);
	SDL_RenderCopy(renderer, p2, NULL, &pos);
}

void	GUI::draw_speed()
{
	SDL_Rect pos;
	SDL_Surface *tmp;

	tmp = TTF_RenderText_Solid(font, _speed.c_str(), white);
	speed = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);
	pos.y = _height * 50 + 10;
	SDL_QueryTexture(speed, NULL, NULL, &pos.w, &pos.h);
	pos.x = _width / 2 * 50 - pos.w / 2;
	SDL_RenderCopy(renderer, speed, NULL, &pos);
}

void	GUI::draw_objects()
{
	int c = 0;
	SDL_Rect dst;

    dst.h = 50;
    dst.w = 50;
   
	for (int i = 0; i < _height; ++i)
	{
		for (int j = 0; j < _width; j++, c++)
		{
			dst.x = j * 50;
			dst.y = i * 50;
			
			if (_level[c] == 1)
				SDL_RenderCopy(renderer, snakePart, nullptr, &dst);
			else if (_level[c] == 2)
				SDL_RenderCopy(renderer, snakeHead, nullptr, &dst);
			else if (_level[c] == 3)
				SDL_RenderCopy(renderer, food, nullptr, &dst);
			else if (_level[c] == 4)
				SDL_RenderCopy(renderer, food_bonus, nullptr, &dst);
			else if (_level[c] == 5)
				SDL_RenderCopy(renderer, wall, nullptr, &dst);
		}
	}
}

void	GUI::draw_lower_texture()
{
	SDL_Rect dst;

	dst.h = 50;
    dst.w = 50;
	for (int i = 0; i < _width; ++i)
	{	
		dst.y = (_height) * 50;
		dst.x = i * 50;
		SDL_RenderCopy(renderer, background, nullptr, &dst);
	}
}

void	GUI::draw(void)
{

	draw_objects();
	draw_lower_texture();
	draw_p1();
	draw_p2();
	draw_speed();
	

    SDL_DestroyTexture(p1);
    SDL_DestroyTexture(p2);
    SDL_DestroyTexture(speed);
    SDL_DestroyTexture(winner);
    
    p1 = nullptr;
    p2 = nullptr;
    speed = nullptr;
    winner = nullptr;
}

extern "C" GUI		*create_object(int *level, int width, int height)
{
	return new GUI(level, width, height);
}

extern "C" void		destroy_object(GUI *gui)
{
	delete gui;
}
