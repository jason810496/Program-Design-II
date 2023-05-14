CXX = g++
CXXFLAGS = -w -std=c++14

SRCDIR = src
OBJDIR = obj
BINDIR = bin
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
EXECUTABLE = hw5

all: main
	$(CXX) $(CXXFLAGS) obj/Constant.o obj/BaseEngine.o obj/HashEngine.o obj/Parser.o obj/RbTreeEngine.o obj/TrieEngine.o obj/SearchEngine.o obj/main.o -o $(EXECUTABLE)

# all: main
# 	$(CXX) $(CXXFLAGS) obj/Constant.o obj/BaseEngine.o obj/HashEngine.o obj/Parser.o obj/RbTreeEngine.o obj/TrieEngine.o obj/SearchEngine.o obj/main.o -o $(EXECUTABLE)

main: search
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(OBJDIR)/main.o

search: const base parser trie hash rbtree
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/SearchEngine.cpp -o $(OBJDIR)/SearchEngine.o

parser: const
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/Parser.cpp -o $(OBJDIR)/Parser.o

trie: base
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/TrieEngine.cpp -o $(OBJDIR)/TrieEngine.o

hash: base
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/HashEngine.cpp -o $(OBJDIR)/HashEngine.o

rbtree: base
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/RbTreeEngine.cpp -o $(OBJDIR)/RbTreeEngine.o

base: $(SRCDIR)/BaseEngine.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/BaseEngine.h -o $(OBJDIR)/BaseEngine.o

const: $(SRCDIR)/Constant.h
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/Constant.h -o $(OBJDIR)/Constant.o

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)