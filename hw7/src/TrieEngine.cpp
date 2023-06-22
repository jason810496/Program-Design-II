#include "TrieEngine.h"
#include<cmath>
#include<algorithm>
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

Trie::Node* Trie::searchNode(const std::string & word){
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
			return nullptr;
		}
	}
	return node;
}

//// Trie Implementation End ////


//// TrieEngine Implementation ////

TrieEngine::TrieEngine(const int & k){
	kTop = k;
}

TrieEngine::~TrieEngine(){
}

void TrieEngine::insert(const int & id,const std::string & word){
	db.insert(id,word);
}

bool TrieEngine::search(const std::vector<std::string> & search , std::vector<int> & result){
	std::map<int,double> id_idf_table;
	
	for(const auto & word : search){
		int apperance = 0;
		Trie::Node *node = db.searchNode(word);
		if(node == nullptr){
			continue;
		}
		double idf = log10( (double)lineCount / (double)node->isWord.size() );
		
		for(const auto & id : node->isWord){
			id_idf_table[id]+= idf;
		}
	}

    int idx=0;
    std::vector<std::pair<int,double>> tmp((int)id_idf_table.size());
    for(const auto & id_idf : id_idf_table){
        tmp[idx++] = std::pair<int,double>(id_idf.first,id_idf.second);
    }
    std::sort(tmp.begin(),tmp.end(),[](const std::pair<int,double> & a,const std::pair<int,double> & b){
        return a.second == b.second ? a.first<b.first: a.second > b.second;
    });


    for(int i=0;i<tmp.size() && i<kTop;++i){
        if( std::abs(tmp[i].second) < 1e-6 ){
            break;
        }
        result.push_back(tmp[i].first);
    }

    while(result.size() < kTop){
        result.push_back(-1);
    }

    return true;
}

//// TrieEngine Implementation End ////