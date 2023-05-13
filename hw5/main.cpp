#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>


#include "Parser.h"
#include "TrieEngine.h"


int main(int argc, char** argv){
	Parser parser;
	parser.readCorpus(argv[1]);
	return 0;
}