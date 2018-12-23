/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_meny.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 20:21:47 by anesteru          #+#    #+#             */
/*   Updated: 2018/12/23 14:13:08 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nibbler.hpp"

enum	eMenu {START, DIFFICULTY, PLAYERS, EXIT};

void			start_menu(IGUI *&gui, int &p, int &dif, void *&handle, int height, int width, int *level)
{
	char		d[3][7] = {"Easy", "Medium", "Hard"};
	int			line = START;

	gui->initiate_menu_text(line, dif, p);
	while (gui->is_ON())
	{
		while (gui->poll_event())
		{
			if (gui->event_type() == KEY_PRESSED)
			{
				int gui_key;
				if ((gui_key = gui->key_code()) == GUI_SDL || gui_key == GUI_SFML)
				{
					change_library(gui, gui_key, handle);
					gui = create(handle, level, width, height);
					gui->initiate_menu_text(line, dif, p);
					break ;
				}
				else if (gui->key_code() == ESCAPE)
					gui->close_window();
				else if (line > 0 && gui->get_key_code() == UP)
				{
					gui->set_string_color(line--, WHITE);
					gui->set_string_color(line, CYAN);
				}
				else if (line < 3 && gui->get_key_code() == DOWN)
				{
					gui->set_string_color(line++, WHITE);
					gui->set_string_color(line, CYAN);
				}
				else if (gui->key_code() == ENTER)
				{
					if (line == START)
						return ;
					else if (line == EXIT)
					{
						gui->close_window();
						return ;
					}
					else if (line == DIFFICULTY)
					{
						dif = (dif + 1) % 3;
						gui->set_menu_string(line, "Difficulty     " + std::string(d[dif]));
					}
					else if (line == PLAYERS)
					{
						p = (p == 1) ? 2 : 1;
						gui->set_menu_string(line, "Players      " + std::to_string(p));
					}
				}
			}
			else if (gui->event_type() == WINDOW_CLOSED)
				gui->close_window();
		}
		gui->clear_window();
		gui->draw_menu();
		gui->display_window();
	}
}
