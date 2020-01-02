EXE = gravite
OBJS = main.o Univers.o Rendu.o Horloge.o Corps.o
SRC = src

CXXFLAGS = -g -O2 -Wall -Werror -std=c++11 -lX11 
LDFLAGS =
LDLIBS = -lstdc++ -L/usr/lib/ -lsfml-system -lsfml-window -lsfml-graphics -pthread -lm

CPPFLAGS = -I/usr/include/SFML


all: $(EXE)

$(EXE):$(SRC)/$(OBJS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@
	
run :
	./$(EXE)

debug :
	gdb -tui $(EXE)
	
clean:
	rm -f $(OBJS)
	rm -f $(EXE)
	
.PHONY: clean
