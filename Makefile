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
			srcs/Camera.cpp

OBJECTS		=	$(SOURCES:.cpp=.o)

CXXFLAGS	+=	-I ./header -I ./bomberlib -g3

LDFLAGS		+=	-L ./bomberlib/ -Wl,--no-as-needed -Wl,--rpath=./bomberlib -lfmodex64 -ldl -lGLU -lGL -lgdl_gl -lSDL2 -lGLEW -lpthread -lrt -lfbxsdk -lsfml-audio

all: $(NAME)

$(NAME):	$(OBJECTS)
		g++ $(OBJECTS) -o $(NAME) $(LDFLAGS) -g

clean:
	rm -f $(OBJECTS)

fclean:	clean
		rm -f $(NAME)

re:		fclean	all
