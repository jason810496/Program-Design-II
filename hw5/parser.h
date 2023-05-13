#define PARSER_INCLUDED

#ifdef PARSER_INCLUDED

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

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
		const std::vector<std::string> & parsed();
		const int & size();
};

#endif