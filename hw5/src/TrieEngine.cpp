#include "TrieEngine.h"

//// Trie Implementation ////

Trie::Node::Node(char data, const int id){
	this->data = data;
	this->isWord.insert(id);
}

Trie::Node::Node(char data){
	this->data = data;
}

Trie::Node::~Node(){
	for(auto & child : children){
		delete child;
	}
}

Trie::Trie(){
	root = new Node('\0');
}

Trie::~Trie(){
	delete root;
}

void Trie::insert(const int &id,const std::string & word){
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
			Node* newNode = new Node(c);
			node->children.push_back(newNode);
			node = newNode;
		}
	}

	node->isWord.insert(id);
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
	return true;
}

bool Trie::search(const std::string & word,std::vector<int> & result){
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

	for(const auto & id : node->isWord){
		result.push_back(id);
	}
	return true;
}

//// Trie Implementation End ////


//// TrieEngine Implementation ////

TrieEngine::TrieEngine(){
}

TrieEngine::~TrieEngine(){
}

void TrieEngine::insert(const int & id,const std::string & word){
	db.insert(id,word);
}

bool TrieEngine::search(const std::vector<std::string> & search , std::vector<int> & result){
	int k = search.size();
    std::map<int,int> bucket;

    for(const auto & word : search){
		std::vector<int> tmp;
		db.search(word,tmp);
		for(const auto & id : tmp){
			bucket[id]++;
		}
	}


    for(const auto & p : bucket){
        if(p.second == k){
            result.push_back(p.first);
        }
    }
    
    
    if(result.empty() ){
        result.push_back(-1);
        return false;
    }

    return true;
}

//// TrieEngine Implementation End ////