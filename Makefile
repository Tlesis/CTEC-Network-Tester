CC=g++
CFLAGS=-O2 -std=c++20 -Isrc

ODIR=build
NAME:=networkTester.out


_OBJ=$(wildcard */*/*.cpp)
_OBJ+=$(wildcard */*.cpp)
OBJ=$(patsubst %.cpp,$(ODIR)/%.o,$(_OBJ))

.PHONY: clean run always

$(ODIR)/%.o: %.cpp always
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) $^ $(CFLAGS) -o $(NAME)

clean:
	@rm -rf $(ODIR) $(NAME)

run:
	./$(NAME)

always:
	mkdir -p build/src