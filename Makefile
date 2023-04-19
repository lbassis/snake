CC=gcc

IDIR=./include
SRCDIR=./src
OBJDIR=./obj
BINDIR=./bin

CFLAGS=-I$(IDIR) -Wall -g
LDFLAGS=-lncurses -lpthread

DEPS=include/player.h include/interface.h
OBJ=$(OBJDIR)/main.o $(OBJDIR)/interface.o $(OBJDIR)/player.o

TARGET=$(BINDIR)/game

all: $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(CFLAGS) $(LDFLAGS)
	@echo Game compiled!

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)

clean:
	stty sane
	clear	
	rm -rf $(OBJ) $(TARGET)
