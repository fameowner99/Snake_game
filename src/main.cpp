#include "nibbler.hpp"


static void		destroy(ISound *sound, void *handle)
{
	void	(*destroy_sound)(ISound *);
	destroy_sound = (void (*)(ISound *))dlsym(handle, "destroy_object");
	destroy_sound(sound);
}

void	destroy(IGUI *gui, void *handle)
{
	void	(*destroy_gui)(IGUI *);
	destroy_gui = (void (*)(IGUI *))dlsym(handle, "destroy_object");
	destroy_gui(gui);
}

static ISound	*create(void *handle)
{
	ISound	*(*create_sound)();
	create_sound = (ISound *(*)())dlsym(handle, "create_object");
	return (ISound *)create_sound();
}

IGUI		*create(void *handle, int *level, int width, int height)
{
	IGUI	*(*create_gui)(int *, int, int);
	 
	create_gui = (IGUI *(*)(int *, int, int))dlsym(handle, "create_object");
	return (IGUI *)create_gui(level, width, height);
}

void		change_library(IGUI *gui, int gui_key, void *&handle_gui)
{
	destroy(gui, handle_gui);
	dlclose(handle_gui);
	if (gui_key == GUI_SDL)
		handle_gui = dlopen("lib1.dylib", RTLD_LAZY);
	else if (gui_key == GUI_SFML)
		handle_gui = dlopen("lib2.dylib", RTLD_LAZY);
	else if (gui_key == GUI_GLFW)
		handle_gui = dlopen("lib3.dylib", RTLD_LAZY);
	if (!handle_gui)
		throw std::runtime_error("dynamic graphics library is missing!");
}

void		game(int *level, int &width, int &height)
{	
	void	*handle_sound = dlopen("sound.dylib", RTLD_LAZY);
	if (!handle_sound)
		throw std::runtime_error("dynamic sound library is missing!");
	ISound	*sound = create(handle_sound);
	sound->background_song_play();

	void	*handle_gui = dlopen("lib2.dylib", RTLD_LAZY);
	if (!handle_gui)
		throw std::runtime_error("dynamic graphics library is missing!");
	IGUI	*gui = create(handle_gui, level, width, height);


	int dif = 0, players_count = 1;
	start_menu(gui, players_count, dif, handle_gui, height, width, level);
	Snake	*snake1, *snake2;
	if (players_count == 1)
	{
		snake1 = new Snake(width, height, level, MIDLE_POS, sound);
		if (dif != 0)
			spawn_walls(level, snake1->get_head(), snake1->get_head(), width, width * height, dif);
	}
	else
	{
		snake1 = new Snake(width, height, level, RIGHT_POS, sound);
		snake2 = new Snake(width, height, level, LEFT_POS, sound);
		if (dif != 0)
			spawn_walls(level, snake1->get_head(), snake2->get_head(), width, width * height, dif);
	}
	spawn_food(width * height, level, FOOD);
	bool	pause = false, start_pause = true;
	int		key = -1, key2 = -1, frame_time = TIME_PER_FRAME, sec = 0, draw = 0;

	int sum_time = 0;
	int	food_time = 0;
	auto t1 = std::chrono::high_resolution_clock::now();
	auto t2 = std::chrono::high_resolution_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
	while (gui->is_ON())
	{
		if (pause == false && start_pause == false && food_time > TIME_FOOD_SPAWN)
		{
			if (frame_time > 50000)
				frame_time -= frame_time / 500;
			if (sec++ % 4 == 3 && rand() % 4 == 0)
				spawn_food(width * height, level, BONUS_FOOD);
			food_time = 0;
		}
		if (pause == false && start_pause == false && sum_time >= frame_time)
		{

			if (players_count == 1 && snake1->move(key) == false)
			{
				gui->set_winner_string("score: " + std::to_string(snake1->get_score()));
				snake1->reset();
				start_pause = true;
				frame_time = TIME_PER_FRAME;
				draw = sec;
				food_time = 0;
				sum_time = 0;
			}
			if (players_count == 2
			&& ((snake1->is_alive() == true && snake1->move(key) == false && snake2->is_alive() == false)
			|| (snake2->is_alive() == true && snake2->move(key2) == false && snake1->is_alive() == false)))
			{
				if (snake1->get_score() == snake2->get_score())
					gui->set_winner_string("draw");
				else
					gui->set_winner_string("p" + std::to_string(snake1->get_score() > snake2->get_score() ? 2 : 1) + " won");
				snake1->reset();
				snake2->reset();
				start_pause = true;
				frame_time = TIME_PER_FRAME;
				draw = sec;
				key2 = -1;
				food_time = 0;
				sum_time = 0;
			}
			key = -1;
			sum_time = 0;
		}
		while (gui->poll_event())
		{
			if (gui->event_type() == KEY_PRESSED)
			{
				int gui_key;
				if ((gui_key = gui->key_code()) == GUI_SFML || gui_key == GUI_SDL || gui_key == GUI_GLFW)
				{
					change_library(gui, gui_key, handle_gui);
					gui = create(handle_gui, level, width, height);
					break ;
				}
				else if (gui->key_code() == ESCAPE)
					gui->close_window();
				else if (gui->key_code() == ARROWS)
					key = gui->get_key_code();
				else if (players_count == 2 && gui->key_code() == WASD)
					key2 = gui->get_key_code();
				else if (gui->key_code() == P)
					pause = !pause;
				else if (gui->key_code() == ADD && frame_time > 50000)
 					frame_time -= frame_time / 100;
				else if (gui->key_code() == SUBTRACT && frame_time < TIME_PER_FRAME)
 					frame_time += frame_time / 100;
 				if (start_pause == true)
 					start_pause = false;
			}
			if (gui->event_type() == WINDOW_CLOSED)
				gui->close_window();
		}

		/***** DRAWING ***/
		gui->clear_window();
		if (players_count == 1)
			gui->set_score1_string(std::to_string(snake1->get_score()));
		else if (players_count == 2)
		{
			gui->set_score1_string(std::to_string(snake2->get_score()));
			gui->set_score2_string(std::to_string(snake1->get_score()));
		}
		gui->set_speed_string(std::to_string((float)1000000 / frame_time).substr(0, 5));
		gui->draw();
		if (draw == sec)
			gui->display_winner_string();
		gui->display_window();
	
	t1 = t2;
	t2 = std::chrono::high_resolution_clock::now();
	elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
	sum_time += elapsed_time;
	food_time += elapsed_time;
	}
	destroy(sound, handle_sound);
	destroy(gui, handle_gui);
	delete snake1;
	if (players_count == 2)
		delete snake2;
}

int		main(int argc, char **argv)
{
	int width, height;
	
	try
	{
		if (argc != 3 || (width = std::stoi(argv[1])) < 10 || width > 50
					|| (height = std::stoi(argv[2])) < 10 || height > 25)
		{
			std::cout << "usage: " << argv[0] << " width(10..50) height(10..25)" << std::endl;
			return 1;
		}
	}
	catch (...)
	{
		std::cout << "usage: " << argv[0] << " width(10..50) height(10..25)" << std::endl;
		return 1;
	}
	srand(clock());
	int level[width * height];
	memset(level, BACKGROUND, sizeof(level));
	try
	{
		game(level, width, height);
	}
	catch (std::runtime_error e)
	{
		std::cout << "Runtime error: " << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cout << "Another error was cought!" << std::endl;
		return 1;
	}
	return 0;
}
