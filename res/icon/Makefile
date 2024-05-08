TARGET = resource.res
CC = gcc
CCFLAGS := -static -O3

SRCS := $(wildcard *.rc)
OBJS := $(SRCS:.rc=.o)

$(OBJS) : $(SRCS)
	windres $< $(BUILD_DIR)$@

.PHONY: clean
clean:
	del $(TARGET) *.o /Q /S

