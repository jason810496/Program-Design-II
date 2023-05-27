#include "SearchEngine.h"

SearchEngine::SearchEngine(const std::string & engineType,const int & k){
	type = engineType;
	if(type == TRIE){
		engine = new TrieEngine(k);
	}else if(type == HASH){
		engine = new HashEngine(k);
	}else if(type == RBTREE){
		engine = new RbTreeEngine(k);
	}
}

SearchEngine::~SearchEngine(){
	delete engine;
}

void SearchEngine::readCorpus(const std::string & filename){
	parser.readCorpus(filename,engine);
}

void SearchEngine::answerQuery(const std::string & filename){
	parser.answerQuery(filename,engine);
}

void SearchEngine::insert(const int & id,const std::string & word){
	engine->insert(id,word);
}

bool SearchEngine::search(const std::vector<std::string> & search , std::vector<int> & result){
	return engine->search(search,result);
}