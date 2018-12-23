# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anesteru <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/14 20:06:52 by anesteru          #+#    #+#              #
#    Updated: 2018/12/23 14:09:38 by vmiachko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	nibbler
SOUND_LIB		=	sound.dylib
GRAPHICS_LIB1	=	lib1.dylib
GRAPHICS_LIB2	=	lib2.dylib
GRAPHICS_LIB3	=	lib3.dylib

CC				=	clang++

SDL_PATH		=	-I SDL_Frameworks/SDL2_ttf.framework/Headers -I SDL_Frameworks/SDL2.framework/Headers
GLFW_PATH		=	-I GLFW_Library/ftgl_text/include -I GLFW_Library
FLAGS			=	-Wall -Werror -Wextra -std=c++14
FDIR_FLAG		=	-F SFML_Frameworks
FWORK_FLAGS		=	-framework sfml-graphics -framework sfml-window -framework sfml-system
SDL_FLAGS		=	-framework SDL2 -F SDL_Frameworks -rpath SDL_Frameworks -framework SDL2_ttf
GLFW_FLAGS		=	GLFW_Library/ftgl_text/lib/libftgl.2.1.3.dylib GLFW_Library/libglfw.3.2.dylib
AUDIO_FLAG		=	-framework sfml-audio
DYN_LIB_FLAG	=	-dynamiclib -fPIC

SRC				=	main.cpp	snake.cpp	start_meny.cpp	spawn.cpp
INC				=	nibbler.hpp		snake.hpp	IGUI.hpp	ISound.hpp

SOUND_SRC		=	sounds.cpp
SOUND_INC		=	sounds.hpp

G_LIB1_SRC		=	gui.cpp
G_LIB1_INC		=	gui.hpp

G_LIB2_INC		=	gui_sfml.hpp	tilemap.hpp
G_LIB2_SRC		=	gui_sfml.cpp	tilemap.cpp

G_LIB3_INC		=	gui_glfw.hpp
G_LIB3_SRC		=	gui_glfw.cpp glad.cpp

OBJ				=	$(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))
INC_FILES		=	$(addprefix $(INC_DIR), $(INC))

SOUND_OBJ		=	$(addprefix $(SOUND_DIR), $(SOUND_SRC:.cpp=.o))
SOUND_HEAD		=	$(addprefix $(SOUND_DIR), $(SOUND_INC))

G_LIB1_OBJ		=	$(addprefix $(G_LIB1_DIR), $(G_LIB1_SRC:.cpp=.o))
G_LIB1_HEAD		=	$(addprefix $(G_LIB1_DIR), $(G_LIB1_INC))

G_LIB2_OBJ		=	$(addprefix $(G_LIB2_DIR), $(G_LIB2_SRC:.cpp=.o))
G_LIB2_HEAD		=	$(addprefix $(G_LIB2_DIR), $(G_LIB2_INC))

G_LIB3_OBJ		=	$(addprefix $(G_LIB3_DIR), $(G_LIB3_SRC:.cpp=.o))
G_LIB3_HEAD		=	$(addprefix $(G_LIB3_DIR), $(G_LIB3_INC))


SRC_DIR			=	./src/
OBJ_DIR			=	./obj/
INC_DIR			=	./includes/

SOUND_DIR		=	./soundlib/
G_LIB1_DIR		=	./lib1/
G_LIB2_DIR		=	./lib2/
G_LIB3_DIR		=	./lib3/

BLUE			=	\033[0;36m
RED				=	\033[0;31m
NO_COLOR		=	\033[0m


all: $(SOUND_LIB) $(GRAPHICS_LIB1) $(GRAPHICS_LIB2) $(NAME) 

obj:
	mkdir -p obj

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(INC_FILES) | obj
	$(CC)  $(FLAGS) $(FDIR_FLAG) $(SDL_PATH)  -I $(INC_DIR) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(FWORK_FLAGS)  $(FDIR_FLAG) $(OBJ) -o $(NAME)
	@echo "$(BLUE)$(NAME)$(NO_COLOR)  is ready"


$(SOUND_DIR)%.o: $(SOUND_DIR)%.cpp $(SOUND_HEAD)
	$(CC) $(FLAGS) -I $(INC_DIR) $(FDIR_FLAG) -c $< -o $@

$(SOUND_LIB): $(SOUND_OBJ)
	$(CC) $(FLAGS) $(AUDIO_FLAG) $(FDIR_FLAG) $(DYN_LIB_FLAG) $(SOUND_OBJ) -o $@
	@echo "dynamic sound library  $(BLUE)$(SOUND_LIB)$(NO_COLOR)  created"


$(G_LIB1_DIR)%.o: $(G_LIB1_DIR)%.cpp $(G_LIB1_HEAD)
	$(CC) $(FLAGS) -I $(INC_DIR) $(SDL_PATH)  -c $< -o $@

$(GRAPHICS_LIB1): $(G_LIB1_OBJ)
	$(CC) $(FLAGS) $(SDL_FLAGS) $(DYN_LIB_FLAG) $(G_LIB1_OBJ) -o $@
	@echo "dynamic graphics library  $(BLUE)$(GRAPHICS_LIB1)$(NO_COLOR)  created"


$(G_LIB2_DIR)%.o: $(G_LIB2_DIR)%.cpp $(G_LIB2_HEAD)
	$(CC) $(FLAGS) -I $(INC_DIR) $(FDIR_FLAG) -c $< -o $@

$(GRAPHICS_LIB2): $(G_LIB2_OBJ)
	$(CC) $(FLAGS) $(FWORK_FLAGS) $(FDIR_FLAG) $(DYN_LIB_FLAG) $(G_LIB2_OBJ) -o $@
	@echo "dynamic graphics library  $(BLUE)$(GRAPHICS_LIB2)$(NO_COLOR)  created"

$(G_LIB3_DIR)%.o: $(G_LIB3_DIR)%.cpp $(G_LIB3_HEAD) 
	$(CC) $(FLAGS) -I $(INC_DIR) $(GLFW_PATH) -c $< -o $@

$(GRAPHICS_LIB3): $(G_LIB3_OBJ) 
	$(CC) $(FLAGS) $(GLFW_FLAGS) $(DYN_LIB_FLAG) $(G_LIB3_OBJ) -o $@
	@echo "dynamic graphics library  $(BLUE)$(GRAPHICS_LIB3)$(NO_COLOR)  created"

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(SOUND_OBJ)
	@rm -rf $(G_LIB1_OBJ)
	@rm -rf $(G_LIB2_OBJ)
	@rm -rf $(G_LIB3_OBJ)
	@echo "object files  deleted"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(SOUND_LIB)
	@rm -f $(GRAPHICS_LIB1)
	@rm -f $(GRAPHICS_LIB2)
	@rm -f $(GRAPHICS_LIB3)
	@echo "$(RED)$(NAME)  $(SOUND_LIB)  $(GRAPHICS_LIB1)  $(GRAPHICS_LIB2)  $(GRAPHICS_LIB3)$(NO_COLOR)  deleted"

libclean:
	@rm -rf SDL_Frameworks
	@rm -rf SFML_Frameworks
	@rm -rf GLFW_Library

re: fclean all

.PHONY: all clean fclean re

