TARGET = tests.exe 

CC = gcc
CCFLAGS := -static -O3
SRCS := $(wildcard *.c)
OBJS := $(TEST_BUILD_DIR)$(SRCS:.c=.o)
ARS := -lErrorHandler -lGameController -lFileIO -lGameLogic -lUserIO

main:
	$(CC) $(CCFLAGS) -c -o $(TEST_BUILD_DIR)tests.o tests.c
	$(CC) $(CCFLAGS) -L../bin/ -o$(TEST_BUILD_DIR)tests.exe $(TEST_BUILD_DIR)tests.o $(ARS) 
