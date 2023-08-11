CXX = g++
CXXFLAGS = -w -std=c++14

SRCDIR = src
OBJDIR = obj
BINDIR = bin
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
EXECUTABLE = hw7

testall:
	./hw7 test/testcase1/corpus1 test/testcase1/query1 1 > result/result1_1.txt
	diff result/result1_1.txt test/testcase1/result_1
	./hw7 test/testcase1/corpus1 test/testcase1/query1 2 > result/result1_2.txt
	diff result/result1_2.txt test/testcase1/result_2
	./hw7 test/testcase1/corpus1 test/testcase1/query1 3 > result/result1_3.txt
	diff result/result1_3.txt test/testcase1/result_3
	./hw7 test/testcase2/corpus2 test/testcase2/query2 1 > result/result2_1.txt
	diff result/result2_1.txt test/testcase2/result_1
	./hw7 test/testcase2/corpus2 test/testcase2/query2 2 > result/result2_2.txt
	diff result/result2_2.txt test/testcase2/result_2
	./hw7 test/testcase2/corpus2 test/testcase2/query2 3 > result/result2_3.txt
	diff result/result2_3.txt test/testcase2/result_3
	./hw7 test/testcase3/corpus3 test/testcase3/query3 1 > result/result3_1.txt
	diff result/result3_1.txt test/testcase3/result_1
	./hw7 test/testcase3/corpus3 test/testcase3/query3 2 > result/result3_2.txt
	diff result/result3_2.txt test/testcase3/result_2
	./hw7 test/testcase3/corpus3 test/testcase3/query3 3 > result/result3_3.txt
	diff result/result3_3.txt test/testcase3/result_3


owen:
	$(CXX) $(CXXFLAGS) owen.cpp -o $(EXECUTABLE)

# all:
# 	$(CXX) $(CXXFLAGS) owen.cpp -o $(EXECUTABLE)

all: main
	$(CXX) $(CXXFLAGS) obj/HashEngine.o obj/Parser.o obj/RbTreeEngine.o obj/TrieEngine.o obj/SearchEngine.o obj/main.o -o $(EXECUTABLE)

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