SOURCES := src/compiler.cpp src/lexer.cpp
# Objs are all the sources, with .cpp replaced by .o
OBJS := $(SOURCES:.cpp=.o)

all: run

# Compile the binary 't' by calling the compiler with cflags, lflags, and any libs (if defined) and the list of objects.
jklc: $(SOURCES)
	g++ -o jklc $(SOURCES)

# Get a .o from a .cpp by calling compiler with cflags and includes (if defined)
.cpp.o:
	g++ -c $<

run: jklc
	./jklc

.PHONY: all run