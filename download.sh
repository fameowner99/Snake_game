#/bin/bash

LINK1="https://github.com/fameowner99/SDL_LIBRARY.git"

LINK2="https://github.com/fameowner99/SFML_FRAMEWORKS.git"

LINK3=~/GLFW_Library

GLFW_LIB="./GLFW_Library"

DIRECTORY1="./SDL_Frameworks"

DIRECTORY2="./SFML_Frameworks"

DIRECTORY3="."

if [ -d "$DIRECTORY1" ]; then
	rm -rf $DIRECTORY1
fi

if [ -d "$DIRECTORY2" ]; then
	rm -rf $DIRECTORY2
fi

if [ -d "$GLFW_LIB" ]; then
	rm -rf $GLFW_LIB
fi

git clone $LINK1 $DIRECTORY1

git clone $LINK2 $DIRECTORY2

cp -R $LINK3 $DIRECTORY3
