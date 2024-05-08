TARGET = Tetris.exe 
CC = gcc
CCFLAGS := -static -O3
SRCS := $(wildcard *.c)
OBJS := bin/$(SRCS:.c=.o)
ARS := -lGameController -lErrorHandler -lFileIO -lGameLogic -lUserIO
export BUILD_DIR := '..\..\bin\'
export TEST_BUILD_DIR := '..\bin\tests\'

all: GameLogic UserIO FileIO GameController ErrorHandler Resources tests main

.PHONY: GameLogic
GameLogic:     
	$(MAKE) -C ./src/GameLogic/

.PHONY: UserIO	
UserIO:
	$(MAKE) -C ./src/UserIO/

.PHONY: FileIO
FileIO:
	$(MAKE) -C ./src/FileIO/

.PHONY: GameController
GameController:
	$(MAKE) -C ./src/GameController/

.PHONY: ErrorHandler
ErrorHandler:
	$(MAKE) -C ./src/ErrorHandler/
	
.PHONY: Resources
Resources:
	$(MAKE) -C ./res/icon/

.PHONY: tests
tests:
	$(MAKE) -C ./tests/ErrorHandler
	$(MAKE) -C ./tests/FileIO
	$(MAKE) -C ./tests/GameController
	$(MAKE) -C ./tests/GameLogic
	
	.\tests\ErrorHandler\tests.exe
	
	.\tests\FileIO\tests.exe
	
	.\tests\GameLogic\tests.exe
	
	.\tests\GameController\tests.exe

.PHONY: main
main:
		$(CC) $(CCFLAGS) -c -o ./bin/main.o main.c
		$(CC) $(CCFLAGS) -Lbin/ -obin/$(TARGET) bin/resource.o $(OBJS) $(ARS) 
		strip bin/$(TARGET)

.PHONY: clean
clean:
	rd bin /S /Q
	mkdir bin
	mkdir bin\tests
