#ifdef PARSER_INCLUDED
#define PARSER_INCLUDED

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "BaseEngine.h"

class Parser{
	private:
        std::stringstream raw;
        std::stringstream pars;
        std::fstream ifs;
		std::vector<std::string> result;
		int wordCount;
		int lineCount;
	public:
		Parser();
		Parser(const int & reserverdSize);
		~Parser();
		void readCorpus(const std::string & filename);
		void readCorpus(const std::string & filename, BaseEngine* engine);
		void answerQuery(const std::string & filename, BaseEngine* engine);
		const std::vector<std::string> & parsed();
		const int & size();
};

#endif