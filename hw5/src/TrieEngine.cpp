#include "TrieEngine.h"

//// Trie Implementation ////

Trie::Node::Node(char data, bool isWord){
	this->data = data;
	this->isWord = isWord;
}
Trie::Node::~Node(){
	for(auto & child : children){
		delete child;
	}
}

Trie::Trie(){
	root = new Node('\0', false);
}

Trie::~Trie(){
	delete root;
}

void Trie::insert(const std::string & word){
	Node* node = root;
	for(const auto & c : word){
		bool found = false;
		for(auto & child : node->children){
			if(child->data == c){
				node = child;
				found = true;
				break;
			}
		}
		if(!found){
			Node* newNode = new Node(c, false);
			node->children.push_back(newNode);
			node = newNode;
		}
	}
	node->isWord = true;
}

bool Trie::search(const std::string & word){
	Node* node = root;
	for(const auto & c : word){
		bool found = false;
		for(auto & child : node->children){
			if(child->data == c){
				node = child;
				found = true;
				break;
			}
		}
		if(!found){
			return false;
		}
	}
	return node->isWord;
}

//// Trie Implementation End ////


//// TrieEngine Implementation ////

TrieEngine::TrieEngine(){
}

TrieEngine::TrieEngine(const int & size){
	db.resize(size);
}

TrieEngine::~TrieEngine(){
}

void TrieEngine::insert(const int & id,const std::string & word){
	if( id >= db.size() ){
		db.resize(id+10);
	}
	db[id].insert(word);
}

bool TrieEngine::search(const std::vector<std::string> & search , std::vector<int> & result){
	int k = search.size();
    std::unordered_map<int,int> bucket;

    for(const auto & word : search){
		for(int i = 0 ; i < db.size() ; ++i){
			if( db[i].search(word) ){
				bucket[i]++;
			}
		}
	}


    for(int i=1;i<=lineCount;i++){
        if(bucket[i] == k){
            result.push_back(i);
        }
    }

	if( result.empty() ){
		result.push_back(-1);
		return false;
	}

	sort(result.begin(),result.end());
	return true;
}

//// TrieEngine Implementation End ////