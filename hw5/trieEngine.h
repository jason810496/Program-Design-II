#define TRIE_ENGINE_INCLUDED

#ifdef TRIE_ENGINE_INCLUDED

#include <string>
#include <vector>
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
		void printNode(Node* node);
	public:
		Trie();
		~Trie();
		void insert(const std::string & word);
		bool search(const std::string & word);
};

class TrieEngine : public BaseEngine{
	private:
		std::vector<Trie> TrieList;
	public:
		TrieEngine();
		~TrieEngine();
        void insert(const int & ithLine,const std::string & word);
		bool search(const std::vector<std::string> & search , std::vector<std::string> & result);
};

#endif

