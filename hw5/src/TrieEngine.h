#ifndef _TRIE_ENGINE_H_
#define _TRIE_ENGINE_H_

#include <string>
#include <vector>
#include <map>
#include <set>

#include "BaseEngine.h"

class Trie{
	private:
		struct Node{
			char data;
			std::set<int> isWord;
			std::vector<Node*> children;
			Node(char data);
			Node(char data, int id);
			~Node();
		};
		Node* root;
	public:
		Trie();
		~Trie();
		void insert(const int &id,const std::string & word);
		bool search(const std::string & word);
		bool search(const std::string & word,std::vector<int> & result);
};

class TrieEngine : public BaseEngine{
	private:
		Trie db;
	public:
		TrieEngine();
		TrieEngine(const int & size);
		~TrieEngine();
        void insert(const int & id,const std::string & word);
		bool search(const std::vector<std::string> & search , std::vector<int> & result);
};

#endif

