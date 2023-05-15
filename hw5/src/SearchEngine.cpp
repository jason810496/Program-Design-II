#include "SearchEngine.h"

SearchEngine::SearchEngine(const std::string & engineType){
	type = engineType;
	if(type == TRIE){
		engine = new TrieEngine();
	}else if(type == HASH){
		engine = new HashEngine();
	}else if(type == RBTREE){
		engine = new RbTreeEngine();
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