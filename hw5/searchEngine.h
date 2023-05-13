#define SEARCH_ENGINE_INCLUDED
#ifdef SEARCH_ENGINE_INCLUDED

#include <string>
#include <vector>
#include "BaseEngine.h"
#include "Parser.h"

class SearchEngine{
	private:
		Parser parser;
		std::string type;
		BaseEngine* engine;
		int lineCount;
	public:
		SearchEngine(const std::string & engineType);
		~SearchEngine();
		void insert(const int & ithLine,const std::string & word);
		bool search(const std::vector<std::string> & search , std::vector<std::string> & result);
};

#endif