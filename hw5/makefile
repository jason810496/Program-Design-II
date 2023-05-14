CXX = g++
CXXFLAGS = -w -std=c++14

SRCDIR = src
OBJDIR = obj
BINDIR = bin
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
EXECUTABLE = main

all: base trie hash rbtree
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)

pareser:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/Parser.cpp -o $(OBJDIR)/Parser.o

base:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/BaseEngine.cpp -o $(OBJDIR)/BaseEngine.o

trie: base
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/TrieEngine.cpp -o $(OBJDIR)/TrieEngine.o

hash: base
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/HashEngine.cpp -o $(OBJDIR)/HashEngine.o

rbtree: base
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/RbTreeEngine.cpp -o $(OBJDIR)/RbTreeEngine.o

search

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)