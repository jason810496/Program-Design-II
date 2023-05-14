#ifndef _PARSER_H_
#define _PARSER_H_

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
		int wordCount;
		int lineCount;
	public:
		Parser();
		~Parser();
		void readCorpus(const std::string & filename);
		void readCorpus(const std::string & filename, BaseEngine* engine);
		void answerQuery(const std::string & filename, BaseEngine* engine);
};

#endif