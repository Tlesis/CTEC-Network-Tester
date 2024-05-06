IDIR=include
CC=g++
CFLAGS=-g -Wall -std=c++20 -Isrc
FRAMEWORKS=

ODIR=build
NAME:=networkTester.out

LIBS=

ARGS=

_OBJ=$(wildcard */*/*.cpp)
_OBJ+=$(wildcard */*.cpp)
_OBJ+=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp,$(ODIR)/%.o,$(_OBJ))

.PHONY: clean run always

$(ODIR)/%.o: %.cpp always
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) $^ $(CFLAGS) $(LIBS) -o $(NAME)

clean:
	@rm -rf $(ODIR) $(NAME)

run:
	./$(NAME) $(ARGS)

always:
	mkdir -p build/src