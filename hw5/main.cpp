#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include "constant.h"
#include "Parser.h"
#include "SearchEngine.h"


int main(int argc, char** argv){
	SearchEngine search_engine(TRIE);
	search_engine.readCorpus(argv[1]);
	search_engine.answerQuery(argv[2]);
	return 0;
}