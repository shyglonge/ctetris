TARGET = main.exe 

CC = gcc
CCFLAGS := -static -O3
SRCS := $(wildcard *.c)
OBJS := $(TEST_BUILD_DIR)$(SRCS:.c=.o)
ARS := -lGameController

main:
	$(CC) $(CCFLAGS) -c -o tests.o tests.c
	$(CC) $(CCFLAGS) -L../../bin/ -otests.exe tests.o $(ARS) 
