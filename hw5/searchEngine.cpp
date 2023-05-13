#include "SearchEngine.h"

SearchEngine::SearchEngine(const string & engineType){
	type = engineType;
	if(type == TRIE){
		engine = new TrieEngine();
	}else if(type == HASH){
		engine = new HashEngine();
	}else if(type == RBTREE){
		engine = new RbTreeEngine();
	}
}