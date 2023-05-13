#include "TrieEngine.h"

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