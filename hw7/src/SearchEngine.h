
#ifndef _SEARCHENGINE_H_
#define _SEARCHENGINE_H_

#include <string>
#include <vector>

#include "Constant.h"
#include "Parser.h"

#include "BaseEngine.h"

#include "TrieEngine.h"
#include "HashEngine.h"
#include "RbTreeEngine.h"


class SearchEngine{
	private:
		Parser parser;
		std::string type;
		BaseEngine* engine;
		int lineCount;
	public:
		SearchEngine(const std::string & engineType,const int & k);
		~SearchEngine();
		void readCorpus(const std::string & filename);
		void answerQuery(const std::string & filename);
		void insert(const int & id,const std::string & word);
		bool search(const std::vector<std::string> & search , std::vector<int> & result);
};

#endif