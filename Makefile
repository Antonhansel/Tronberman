##
## Makefile for Makefile in /home/apollo/rendu/bestbomberman
##
## Made by ribeaud antonin
## Login   <ribeau_a@epitech.net>
##
## Started on  Mon Apr 28 17:02:54 2014 ribeaud antonin
## Last update Sat May 10 22:39:35 2014 Mehdi Chouag
##

NAME		=	bomberman

SOURCES		=	srcs/main.cpp \
			srcs/Loader.cpp \
			srcs/Menu.cpp \
			srcs/Core.cpp \
			srcs/Char.cpp \
			srcs/AObject.cpp \
			srcs/Cube.cpp \
			srcs/Engine.cpp \
			srcs/Map.cpp \
			srcs/Player.cpp \
			srcs/Mybot.cpp \
			srcs/Floor.cpp \
			srcs/Background.cpp \
			srcs/Networking.cpp \
			srcs/Camera.cpp \
			srcs/Text.cpp \
			srcs/Sound.cpp \
			srcs/Bombs.cpp

OBJECTS		=	$(SOURCES:.cpp=.o)

CXX 		= g++

CXXFLAGS	+=	-I ./header -I ./bomberlib -Wall -g -pg
LDFLAGS		+=	-pg -L ./bomberlib/ -Wl,--no-as-needed -Wl,--rpath=./bomberlib -lfmodex64 -ldl -lGLU -lGL -lgdl_gl -lSDL2 -lGLEW -lpthread -lrt -lfbxsdk -lsfml-audio

DEPS := $(OBJECTS:.o=.d)

all: $(NAME)
	@if [ -t 1 ]; then tput setaf 2 ; fi
	@echo "$(NAME) Up to date !"
	@if [ -t 1 ]; then tput sgr0 ; fi

$(NAME):	$(OBJECTS)
	@if [ -t 1 ]; then tput setaf 4 ; fi
	@echo -n "Linking :" $(NAME)
	@if [ -t 1 ]; then tput sgr0 ; fi
	@$(CXX) $(OBJECTS) -o $(NAME) $(LDFLAGS)
	@if [ -t 1 ]; then tput setaf 2 ; fi
	@echo [OK]
	@if [ -t 1 ]; then tput sgr0 ; fi

%.o: %.cpp
	@if [ -t 1 ]; then tput setaf 4 ; fi
	@echo "Compile :" $<
	@if [ -t 1 ]; then tput sgr0 ; fi
	@$(CXX) -MMD -MP $(CXXFLAGS) -o $@ -c $<
	@if [ -t 1 ]; then tput setaf 2 ; fi
	@echo [OK]
	@if [ -t 1 ]; then tput sgr0 ; fi

clean:
	@if [ -t 1 ]; then tput setaf 4 ; fi
	@echo -n "Deleting objects and dependancies..."
	@if [ -t 1 ]; then tput sgr0 ; fi
	@rm -f $(OBJECTS)
	@rm -f $(DEPS)
	@if [ -t 1 ]; then tput setaf 2 ; fi
	@echo [OK]
	@if [ -t 1 ]; then tput sgr0 ; fi

fclean:	clean
	@if [ -t 1 ]; then tput setaf 4 ; fi
	@echo -n "Deleting Executable..."
	@if [ -t 1 ]; then tput sgr0 ; fi
	@rm -f $(NAME)
	@if [ -t 1 ]; then tput setaf 2 ; fi
	@echo [OK]
	@if [ -t 1 ]; then tput sgr0 ; fi

re:		fclean	all

.PHONY: all clean fclean re

-include $(DEPS)
