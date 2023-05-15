#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>

#include "BaseEngine.h"

class Parser{
	private:
        std::stringstream pars;
        std::fstream ifs;
		int wordCount;
		int lineCount;
	public:
		Parser();
		~Parser();
		std::string trim(const std::string & str);
		void readCorpus(const std::string & filename);
		void readCorpus(const std::string & filename, BaseEngine* engine);
		void answerQuery(const std::string & filename, BaseEngine* engine);
};

#endif