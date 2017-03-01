CC = g++ # compiler
CFLAGS = -Wall -std=c++11 # compile flags
LIBS = # libs

SRCS = main.cpp city.cpp # source files
OBJS = $(SRCS:.c=.o) # object files

TARG = main # target

all: $(TARG)
# generates the target executable
$(TARG): $(OBJS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS)

%.o: %.c # generates the object files
	$(CC) $(CFLAGS) -std=c++11 -c $*.cpp

# cleans stuff
clean:
	rm -f $(OBJS) $(TARG) *~
