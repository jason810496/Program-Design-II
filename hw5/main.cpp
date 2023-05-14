#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include "src/Constant.h"
#include "src/SearchEngine.h"


int main(int argc, char** argv){
	SearchEngine search_engine(TRIE);
	search_engine.readCorpus(argv[1]);
	search_engine.answerQuery(argv[2]);
	return 0;
}