TARGET = main.exe 

CC = gcc
CCFLAGS := -static -O3
SRCS := $(wildcard *.c)
OBJS := $(TEST_BUILD_DIR)$(SRCS:.c=.o)
ARS := -lErrorHandler -lGameController -lFileIO -lGameLogic -lUserIO

main:
	$(CC) $(CCFLAGS) -c -o tests.o tests.c
	$(CC) $(CCFLAGS) -L../../bin/ -otests.exe tests.o $(ARS) 
