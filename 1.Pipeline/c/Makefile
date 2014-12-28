# Original: http://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
# the compiler: gcc for C program, define as g++ for C++
CC = clang

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#  -Wextra turn on extra flags that are not enabled by -Wall
#  -Werror make all warnings into errors.
CFLAGS = -g -Wall -Wextra -Werror

LDFLAGS =

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

# the build target executable:
TARGET = pipeline

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CCFLAGS) -c $<

%.o: %.c
	$(CC) $(CCFLAGS) -c $<

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET) $(TARGET).exe
