#ifndef _TRIE_ENGINE_H_
#define _TRIE_ENGINE_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "BaseEngine.h"

class Trie{
	private:
		struct Node{
			char data;
			bool isWord;
			std::vector<Node*> children;
			Node(char data, bool isWord);
			~Node();
		};
		Node* root;
	public:
		Trie();
		~Trie();
		void insert(const std::string & word);
		bool search(const std::string & word);
};

class TrieEngine : public BaseEngine{
	private:
		std::vector<Trie> db;
	public:
		TrieEngine();
		TrieEngine(const int & size);
		~TrieEngine();
        void insert(const int & id,const std::string & word);
		bool search(const std::vector<std::string> & search , std::vector<int> & result);
};

#endif

