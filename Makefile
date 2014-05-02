##
## Makefile for Makefile in /home/apollo/rendu/bestbomberman
## 
## Made by ribeaud antonin
## Login   <ribeau_a@epitech.net>
## 
## Started on  Mon Apr 28 17:02:54 2014 ribeaud antonin
## Last update Thu May  1 17:06:56 2014 ribeaud antonin
##

NAME		=	bomberman

SOURCES		=	srcs/main.cpp \
			srcs/AObject.cpp \
			srcs/Core.cpp \
			srcs/Background.cpp \
			srcs/Intro.cpp \
			srcs/Floor.cpp \
			srcs/Char.cpp \
			srcs/Cube.cpp \
			srcs/Case.cpp \
			srcs/Map.cpp \
			srcs/Sound.cpp

OBJECTS		=	$(SOURCES:.cpp=.o)

CXXFLAGS	+=	-I ./header -I ./bomberlib -g3

LDFLAGS		+=	-L ./bomberlib/ -Wl,--no-as-needed -Wl,--rpath=./bomberlib -lfmodex64 -ldl -lGLU -lGL -lgdl_gl -lSDL2 -lGLEW -lpthread -lrt -lfbxsdk -lsfml-audio

all: $(NAME)

$(NAME):	$(OBJECTS)
		g++ $(OBJECTS) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJECTS)

fclean:	clean
		rm -f $(NAME)

re:		fclean	all
