CXX = g++

CXXFLAGS = -std=c++11 -Wall -g -Iinclude

LDFLAGS =


EXEC = tp2.out

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.cpp)

OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))


all: $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC): $(OBJECTS)
	@mkdir -p $(BINDIR) # Garante que a pasta bin exista
	$(CXX) $(LDFLAGS) -o $@ $^


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR) # Garante que a pasta obj exista
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	@echo "Limpando arquivos compilados..."
	rm -f $(OBJECTS) $(BINDIR)/$(EXEC)

run: all
	@echo "Executando o programa..."
	./$(BINDIR)/$(EXEC) entrada.txt

.PHONY: all clean run