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

all: $(NAME)
	@echo -e "\033[34m$(NAME) Up to date !\033[0m"

$(NAME):	$(OBJECTS)
	@echo -e -n "\033[34mLinking :" $(NAME) "\033[0m"
	@$(CXX) $(OBJECTS) -o $(NAME) $(LDFLAGS)
	@echo -e "\033[32m"[OK]"\033[0m"

%.o: %.cpp
	@echo -e "\033[34mCompile :" $< "\033[0m"
	@$(CXX) $(CXXFLAGS) -o $@ -c $<
	@echo -e "\033[32m"[OK]"\033[0m"

clean:
	@echo -e -n "\033[34mDeleting objects...\033[0m"
	@rm -f $(OBJECTS)
	@echo -e "\033[32m"[OK]"\033[0m"

fclean:	clean
	@echo -e -n "\033[34mDeleting Executable...\033[0m"
	@rm -f $(NAME)
	@echo -e "\033[32m"[OK]"\033[0m"

re:		fclean	all

.PHONY: all clean fclean re
