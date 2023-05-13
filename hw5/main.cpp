#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_multimap>
#include <multimap>
using namespace std;

const string TRIE = "trie";
const string HASH = "hash";
const string RBTREE = "rbtree";

class Parser{
	private:
		stringstream raw;
		stringstream pars;
		fstream ifs;
		vector<string> result;
		int wordCount;
		int lineCount;
	public:
		Parser();
		Parser(const int & reserverdSize);
		~Parser();
		void readCorpus(const string & filename);
		const vector<string> & parsed();
		const int & size();
};

Parser::Parser(){}

Parser::Parser(const int & reserverdSize){
	result.reserve(reserverdSize);
}

Parser::~Parser(){}

void Parser::readCorpus(const string & filename){
	

	ifs.open(filename, ios::in);
	if(ifs.is_open()){
		lineCount = 1;	// init line count
		string line;
		while(getline(ifs, line)){
			// new line parsed
			wordCount = 0; // init word count 
			raw.clear();
			pars.clear(); // init stream

			raw.str(line);
			raw>>quoted(line); // remove `id,`
			raw>>quoted(line); // get quoted string

			pars.str(line);
			while(pars >> line && line.size() > 0){
				result.push_back(line);
			}
			// parsed result 
			for(const auto & word : result){
				cout<<word<<endl;
				wordCount++;
			}

			lineCount++; // next line
			result.clear();
		}
	}
	ifs.close();
	ifs.clear();
}

const vector<string> & Parser::parsed(){
	return result;
}

const int & Parser::size(){
	return wordCount;
}


class Trie{
	private:
		struct Node{
			char data;
			bool isWord;
			vector<Node*> children;
			Node(char data, bool isWord);
			~Node();
		};
		Node* root;
		void printNode(Node* node);
	public:
		Trie();
		~Trie();
		void insert(const string & word);
		bool search(const string & word);
};

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

void Trie::insert(const string & word){
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

bool Trie::search(const string & word){
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

class BaseEngine{
	protected:
		int lineCount;
	public:
		BaseEngine();
		~BaseEngine();
		virtual void insert(const int & ithLine,const string & word);
		virtual bool search(const vector<string> & search , vector<string> & result);
};


class TrieEngine : public BaseEngine{
	private:
		vector<Trie> TrieList;
	public:
		TrieEngine();
		~TrieEngine();
		bool search(const int & ith, const string & word);
};

class HashEngine : public BaseEngine {
	private:
		vector< unordered_set<string> > db;
	public:
		HashEngine();
		HashEngine(int reserverdSize);
		~HashEngine();
		bool search(const int & ith, const string & word);
		bool search(const string & word);
};

class RbTreeEngine : public BaseEngine{
	private:
		vector<string> words;
		vector<string> results;
		void search(string word);
	public:
		RbTreeEngine();
		RbTreeEngine(int reserverdSize);
		~RbTreeEngine();
		bool search(const int & ith, const string & word);
		bool search(const string & word);
};


class SearchEngine{
	private:
		Parser parser;
		string type;
		BaseEngine* engine;
		int lineCount;
	public:
		SearchEngine(const string & engineType);
		~SearchEngine();
		bool search(const string & word);
		bool search(const int & ith, const string & word);
};

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


int main(int argc, char** argv){
	Parser parser;
	parser.readCorpus(argv[1]);
	return 0;
}