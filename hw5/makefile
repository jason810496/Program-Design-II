CXX = g++
CXXFLAGS = -w -std=c++14

SRCDIR = src
OBJDIR = obj
BINDIR = bin
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
EXECUTABLE = main

all: main
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)

main: search
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(OBJDIR)/main.o

search: parser trie hash rbtree
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/SearchEngine.cpp -o $(OBJDIR)/SearchEngine.o

parser:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/Parser.cpp -o $(OBJDIR)/Parser.o

trie: $(SRCDIR)/BaseEngine.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/TrieEngine.cpp -o $(OBJDIR)/TrieEngine.o

hash: $(SRCDIR)/BaseEngine.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/HashEngine.cpp -o $(OBJDIR)/HashEngine.o

rbtree: $(SRCDIR)/BaseEngine.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/RbTreeEngine.cpp -o $(OBJDIR)/RbTreeEngine.o



clean:
	rm -f $(OBJECTS) $(EXECUTABLE)