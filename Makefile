## Makefile for Makefile in /home/apollo/rendu/bestbomberman
##
## Made by ribeaud antonin
## Login   <ribeau_a@epitech.net>
##
## Started on  Mon Apr 28 17:02:54 2014 ribeaud antonin
## Last update Thu May 29 10:47:31 2014 ribeaud antonin
##

NAME		=	bomberman

SOURCES		=	srcs/main.cpp \
				srcs/Loader.cpp \
				srcs/Particles.cpp \
				srcs/Menu.cpp \
				srcs/CubeAnim.cpp \
				srcs/Core.cpp \
				srcs/ParticleEngine.cpp \
				srcs/AObject.cpp \
				srcs/Cube.cpp \
				srcs/Engine.cpp \
				srcs/Map.cpp \
				srcs/MapFiller.cpp \
				srcs/Player.cpp \
				srcs/Mybot.cpp \
				srcs/Floor.cpp \
				srcs/Background.cpp \
				srcs/Networking.cpp \
				srcs/Camera.cpp \
				srcs/Text.cpp \
				srcs/Sound.cpp \
				srcs/Bombs.cpp \
				srcs/Bonus.cpp \
				srcs/Saving.cpp \
				srcs/Generator.cpp \
				srcs/Preview.cpp \
				srcs/AInput.cpp \
				srcs/Hud.cpp \
				srcs/Md5.cpp \
				srcs/ScopedLock.cpp \
				srcs/Thread.cpp \
				srcs/NetworkProtocol.pb.cpp \
				srcs/Function.cpp

OBJECTS		=	$(SOURCES:.cpp=.o)

CXX 		= g++

CXXFLAGS	+=	-I ./header -I ./bomberlib -Wall -I./bomberlib/protobuf
LDFLAGS		+=	-L ./bomberlib/ -Wl,--no-as-needed -Wl,--rpath=./bomberlib \
	-lfmodex64 -ldl -lGLU -lGL -lgdl_gl -lSDL2 -lGLEW -lpthread -lrt -lfbxsdk \
	-lsfml-audio -pthread \
	-I./bomberlib/protobuf -L./bomberlib/protobuf -lprotobuf

# Debug and profiling flags

# CXXFLAGS	+= -g -pg
# LDFLAGS 	+= -g -pg

GREEN 		= 	@if [ -t 1 ]; then tput setaf 2 ; fi
BLUE 		= 	@if [ -t 1 ]; then tput setaf 4 ; fi
RESET 		= 	@if [ -t 1 ]; then tput sgr0 ; fi

DEPS := $(OBJECTS:.o=.d)

all: $(NAME)
	$(GREEN)
	@echo "$(NAME) Up to date !"
	$(RESET)

$(NAME):	$(OBJECTS)
	$(BLUE)
	@echo -n "Linking :" $(NAME)
	$(RESET)
	@$(CXX) $(OBJECTS) -o $(NAME) $(LDFLAGS)
	$(GREEN)
	@echo " [OK]"
	$(RESET)

%.o: %.cpp
	$(BLUE)
	@echo -n "Compile :" $<
	$(RESET)
	@$(CXX) -MMD -MP $(CXXFLAGS) -o $@ -c $< 2> ./tmp || echo -n ""
	@if [ -s ./tmp ] ; then \
		if [ -t 1 ]; then tput setaf 1 ; fi ; \
		echo " [Error]" ; \
		if [ -t 1 ]; then tput sgr0 ; fi ;\
		cat ./tmp ; rm ./tmp ; exit 1; \
	else \
		if [ -t 1 ]; then tput setaf 2 ; fi ; \
		echo " [OK]" ; \
		if [ -t 1 ]; then tput sgr0 ; fi ;\
		rm ./tmp ; \
	fi

clean:
	$(BLUE)
	@echo -n "Deleting objects and dependancies..."
	$(RESET)
	@rm -f $(OBJECTS)
	@rm -f $(DEPS)
	$(GREEN)
	@echo [OK]
	$(RESET)

fclean:	clean
	$(BLUE)
	@echo -n "Deleting Executable..."
	$(RESET)
	@rm -f $(NAME)
	$(GREEN)
	@echo [OK]
	$(RESET)

re:		fclean	all

.PHONY: all clean fclean re

-include $(DEPS)
