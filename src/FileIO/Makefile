TARGET = FileIO.o
CC = gcc
CCFLAGS := -static -O3

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
TARGET_AR := lib$(TARGET:.o=.a)


$(OBJS) : $(SRCS)
	$(CC) $(CCFLAGS) -c -o $(BUILD_DIR)$@ $<
	ar rcs $(BUILD_DIR)$(TARGET_AR) $(BUILD_DIR)$(OBJS)

.PHONY: clean
clean:
	del $(TARGET) *.o /Q /S

