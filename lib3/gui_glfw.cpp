#include "gui_glfw.hpp"

bool	g_key_pressed;
int		g_key;


static void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)window, (void)key, (void)scancode, (void)mods;
	if (action == GLFW_PRESS)
	{
		g_key = key;
		g_key_pressed = true;
	}
	else
		g_key = -1;
}

GUI::GUI(int *level, int width, int height): _level(level), _width(width), _height(height),
font_menu("resources/arial.ttf"), font("resources/arial.ttf"), font_winner("resources/arial.ttf")
{
	glfwInit();
	window = glfwCreateWindow(_width * 50, _height * 50 + 50, "SNAKE", NULL, NULL);
	if (!window)
		throw std::runtime_error("Failed to create GLFW window");
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("Failed to initialize GLAD");

	if (font_menu.Error())
		throw std::runtime_error("Couldn't open font");
	font_menu.FaceSize(80);
	if (font.Error())
		throw std::runtime_error("Couldn't open font");
	font.FaceSize(70);
	font_winner.FaceSize(120);
	colors[0] = 0, colors[1] = 0, colors[2] = 0, colors[3] = 0;
	square_w_size = (float)2 / _width;
	square_h_size = (float)2 / (_height + 1);
	glfwSetKeyCallback(window, key_callback);
}

GUI::~GUI(void)
{
	 window = nullptr;
	 glfwTerminate();
}


void	GUI::initiate_menu_text(int line, int dif, int players)
{
	glPixelTransferf(GL_RED_BIAS, 0.5f);
	glPixelTransferf(GL_GREEN_BIAS, 1.0f);
	glPixelTransferf(GL_BLUE_BIAS, 1.0f);
	text_menu[0] = "START";
	text_menu[1] = "DIFFICULTY  ";
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

void	setColorWhite()
{
		glPixelTransferf(GL_RED_BIAS, 0.5f);
		glPixelTransferf(GL_GREEN_BIAS, 1.0f);
		glPixelTransferf(GL_BLUE_BIAS, 1.0f);
}

void	setColorRed()
{
		glPixelTransferf(GL_RED_BIAS, -0.5f);
		glPixelTransferf(GL_GREEN_BIAS, -1.0f);
		glPixelTransferf(GL_BLUE_BIAS, -1.0f);
}

void	GUI::draw_menu(void)
{
	if (colors[0] == 1)
		setColorRed();
	font_menu.Render(text_menu[0].c_str(), -1, FTPoint(_width * 50
		- (text_menu[0].length() + 1) * 20 , _height * 50 + 300));
	setColorWhite();
	if (colors[1] == 1)
		setColorRed();
	font_menu.Render(text_menu[1].c_str(), -1, FTPoint(_width * 50
		- (text_menu[1].length() + 1) * 20 , _height * 50 + 100));
	setColorWhite();
	if (colors[2] == 1)
		setColorRed();
	font_menu.Render(text_menu[2].c_str(), -1, FTPoint(_width * 50
		- (text_menu[2].length() + 1) * 20 , _height * 50 - 100));
	setColorWhite();
	if (colors[3] == 1)
		setColorRed();
	font_menu.Render(text_menu[3].c_str(), -1, FTPoint(_width * 50
		- (text_menu[3].length() + 1) * 20 , _height * 50 - 300));
	setColorWhite();
}

bool	GUI::is_ON(void)
{
	return (window && !glfwWindowShouldClose(window));
}

bool	GUI::poll_event(void)
{
	glfwPollEvents();
	if (g_key_pressed == true)
	{
		g_key_pressed = false;
		return true;
	}
	return (false);
}

void	GUI::display_window(void)
{
	glfwSwapBuffers(window);
}

void	GUI::close_window(void)
{
	glfwTerminate();
	window = nullptr;
}

void	GUI::clear_window(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
}

int		GUI::event_type(void)
{
	return (KEY_PRESSED);
}

int		GUI::key_code(void)
{
	if (g_key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		return (-1);
	}
	else if (g_key == GLFW_KEY_P)
		return (P);
	else if (g_key == GLFW_KEY_W || g_key == GLFW_KEY_A
		||   g_key == GLFW_KEY_S || g_key == GLFW_KEY_D)
		return (WASD);
	else if (g_key == GLFW_KEY_RIGHT || g_key == GLFW_KEY_LEFT
		||   g_key == GLFW_KEY_UP    || g_key == GLFW_KEY_DOWN)
		return (ARROWS);
	else if (g_key == GLFW_KEY_KP_SUBTRACT)
		return (SUBTRACT);
	else if (g_key == GLFW_KEY_KP_ADD)
		return (ADD);
	else if (g_key == GLFW_KEY_ENTER)
		return (ENTER);
	else if (g_key == GLFW_KEY_KP_1)
		return (GUI_SDL);
	else if (g_key == GLFW_KEY_KP_2)
		return (GUI_SFML);
	return (-1);
}

int		GUI::get_key_code(void)
{
	if (g_key == GLFW_KEY_D || g_key == GLFW_KEY_RIGHT)
		return (RIGHT);
	else if (g_key == GLFW_KEY_A || g_key == GLFW_KEY_LEFT)
		return (LEFT);
	else if (g_key == GLFW_KEY_W || g_key == GLFW_KEY_UP)
		return (UP);
	else if (g_key == GLFW_KEY_S || g_key == GLFW_KEY_DOWN)
		return (DOWN);
	return (-1);
}

void	GUI::set_score1_string(const std::string &str)
{
	_p1 = "s1: " + str;
	font.Render(_p1.c_str(), -1, FTPoint(10, 20));
}

void	GUI::set_score2_string(const std::string &str)
{
	_p2 = "s2: " + str;
	font.Render(_p2.c_str(), -1, FTPoint(_width * 50 * 2 - 230, 20));
}

void	GUI::set_speed_string(const std::string &str)
{
	_speed = "speed " + str;
	font.Render(_speed.c_str(), -1, FTPoint(_width * 50 - (_speed.length() - 1) * 25, 20));
}

void	GUI::set_winner_string(const std::string &str)
{
	_winner = str;
}

void	GUI::display_winner_string(void)
{
	font_winner.Render(_winner.c_str(), -1, FTPoint(_width * 50 - _winner.length() / 2 * 50, _height * 50 * 1.75));
}

static void	draw_square(double x1, double y1, double s_w, double s_h, float a, float b, float c)
{
    glColor3d(a, b, c);
    glBegin(GL_POLYGON);

    glVertex2d(x1 + s_w, y1 + s_h);
    glVertex2d(x1 + s_w, y1 - s_h);
    glVertex2d(x1 - s_w, y1 - s_h);
    glVertex2d(x1 - s_w, y1 + s_h);

    glEnd();
}

static void	draw_line(float height_point)
{
	glLineWidth(2.5);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(1.0, height_point, 0.0);
	glVertex3f(-1.0, height_point, 0.0);
	glEnd();
}

void	GUI::draw(void)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	
	float w_s = -1 + square_w_size / 2;
	float h_s = 1 - square_h_size / 2;
	for (int counter = 0, i = 0; i < _height; i++, h_s -= square_h_size)
	{
		float w_p = w_s;
		for (int j = 0; j < _width; j++, counter++, w_p += square_w_size)
		{
			if (_level[counter] == 1)
				draw_square(w_p, h_s, square_w_size / 2, square_h_size / 2, 1, 1, 0);
			else if (_level[counter] == 2)
				draw_square(w_p, h_s, square_w_size / 2, square_h_size / 2, 0.5, 0.7, 0.3);
			else if (_level[counter] == 3)
				draw_square(w_p, h_s, square_w_size / 2, square_h_size / 2, 1, 0.8, 0.8);
			else if (_level[counter] == 4)
				draw_square(w_p, h_s, square_w_size / 2, square_h_size / 2, 1, 0.1, 0.7);
			else if (_level[counter] == 5)
				draw_square(w_p, h_s, square_w_size / 2, square_h_size / 2, 0.7, 0.4, 0);
		}
	}
	draw_line(square_h_size - 1);
}

extern "C" GUI		*create_object(int *level, int width, int height)
{
	return new GUI(level, width, height);
}

extern "C" void		destroy_object(GUI *gui)
{
	delete gui;
}
