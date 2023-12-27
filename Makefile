#
# Makefile for saucer shoot game using Dragonfly
#
# Copyright Mark Claypool and WPI, 2016-2023
#
# 'make' to build executable
# 'make depend' to generate new dependency list
# 'make clean' to remove all constructed files
#
# Variables of interest:
#   GAMESRC is the source code files for the game
#   GAME is the game main() source
#   EXECUTABLE is the name of the runnable game
#   ENG is the name of the Dragonfly engine
#

# Compiler.
CC= g++

LINKDIR= -L./lib
INCDIR= -I./include

CFLAGS= -Wall
LINKLIB= -l$(ENG) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lrt
ENG= dragonfly-x64-linux

######

GAMESRC= src/Bullet.cpp src/Hero.cpp src/Saucer.cpp src/Reticle.cpp src/Explosion.cpp src/EventNuke.cpp src/Points.cpp

GAME= game.cpp
EXECUTABLE= game
OBJECTS= $(GAMESRC:.cpp=.o)
CFLAGS:= $(CFLAGS) -std=c++11

.PHONY: all clean

all: $(EXECUTABLE) Makefile

$(EXECUTABLE): $(OBJECTS) $(GAME) $(GAMESRC) 
	$(CC) $(CFLAGS) $(GAME) $(OBJECTS) -o $@ $(INCDIR) $(LINKDIR) $(LINKLIB) 

.cpp.o: 
	$(CC) $(CFLAGS) -c $< -o $@ $(INCDIR)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) core dragonfly.log Makefile.bak *~

# DO NOT DELETE
