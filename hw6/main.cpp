#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include "src/Constant.h"
#include "src/SearchEngine.h"
#include "src/Optimization.h"


int main(int argc, char** argv){
	int k = atoi(argv[3]);
	// std::cout<<"K:"<<k<<std::endl;
	SearchEngine search_engine(RBTREE,k);
	search_engine.readCorpus(argv[1]);
	search_engine.answerQuery(argv[2]);
	return 0;
}