##
## Makefile for Makefile in /home/apollo/rendu/bestbomberman
##
## Made by ribeaud antonin
## Login   <ribeau_a@epitech.net>
##
## Started on  Mon Apr 28 17:02:54 2014 ribeaud antonin
## Last update Sun May  4 02:54:55 2014 Mehdi Chouag
##

NAME		=	bomberman

SOURCES		=	srcs/main.cpp \
			srcs/Menu.cpp \
			srcs/Core.cpp \
			srcs/Char.cpp \
			srcs/AObject.cpp \
			srcs/Cube.cpp \
			srcs/Engine.cpp \
			srcs/Map.cpp \
			srcs/Mybot.cpp \
			srcs/Floor.cpp \
			srcs/Background.cpp \
			srcs/Networking.cpp \
			srcs/Camera.cpp \
			srcs/Bombs.cpp

OBJECTS		=	$(SOURCES:.cpp=.o)

CXX 		= g++
CXXFLAGS	+=	-I ./header -I ./bomberlib -Wall

LDFLAGS		+=	-L ./bomberlib/ -Wl,--no-as-needed -Wl,--rpath=./bomberlib -lfmodex64 -ldl -lGLU -lGL -lgdl_gl -lSDL2 -lGLEW -lpthread -lrt -lfbxsdk -lsfml-audio

DEPS := $(OBJECTS:.o=.d)

all: $(NAME)
	@if [ -t 1 ]; then echo -e -n "\033[34m" ; fi
	@echo "$(NAME) Up to date !"
	@if [ -t 1 ]; then echo -e -n "\033[0m" ; fi

$(NAME):	$(OBJECTS)
	@if [ -t 1 ]; then echo -e -n "\033[34m" ; fi
	@echo -e -n "Linking :" $(NAME)
	@if [ -t 1 ]; then echo -e -n "\033[0m" ; fi
	@$(CXX) $(OBJECTS) -o $(NAME) $(LDFLAGS)
	@if [ -t 1 ]; then echo -e -n "\033[32m" ; fi
	@echo -e [OK]
	@if [ -t 1 ]; then echo -e -n "\033[0m" ; fi

%.o: %.cpp
	@if [ -t 1 ]; then echo -e -n "\033[34m" ; fi
	@echo -e "Compile :" $<
	@if [ -t 1 ]; then echo -e -n "\033[0m" ; fi
	@$(CXX) -MMD -MP $(CXXFLAGS) -o $@ -c $<
	@if [ -t 1 ]; then echo -e -n "\033[32m" ; fi
	@echo -e [OK]
	@if [ -t 1 ]; then echo -e -n "\033[0m" ; fi

clean:
	@if [ -t 1 ]; then echo -e -n "\033[34m" ; fi
	@echo -e -n "Deleting objects and dependancies..."
	@if [ -t 1 ]; then echo -e -n "\033[0m" ; fi
	@rm -f $(OBJECTS)
	@rm -f $(DEPS)
	@if [ -t 1 ]; then echo -e -n "\033[32m" ; fi
	@echo -e [OK]
	@if [ -t 1 ]; then echo -e -n "\033[0m" ; fi

fclean:	clean
	@if [ -t 1 ]; then echo -e -n "\033[34m" ; fi
	@echo -e -n "Deleting Executable..."
	@if [ -t 1 ]; then echo -e -n "\033[0m" ; fi
	@rm -f $(NAME)
	@if [ -t 1 ]; then echo -e -n "\033[32m" ; fi
	@echo -e [OK]
	@if [ -t 1 ]; then echo -e -n "\033[0m" ; fi

re:		fclean	all

.PHONY: all clean fclean re

-include $(DEPS)
