#include "Parser.h"

Parser::Parser(){}

Parser::Parser(const int & reserverdSize){
	result.reserve(reserverdSize);
}

Parser::~Parser(){}

void Parser::readCorpus(const std::string & filename){
	

	ifs.open(filename, std::ios::in);
	if(ifs.is_open()){
		lineCount = 1;	// init line count
		std::string line;
		while(getline(ifs, line)){
			// new line parsed
			wordCount = 0; // init word count 
			raw.clear();
			pars.clear(); // init stream

			raw.str(line);
			raw>>quoted(line); // remove `id,`
			raw>>quoted(line); // get quoted std::string

			pars.str(line);
			while(pars >> line && line.size() > 0){
				result.push_back(line);
			}
			// parsed result 
			for(const auto & word : result){
				std::cout<<word<<std::endl;
				wordCount++;
			}

			lineCount++; // next line
			result.clear();
		}
	}
	ifs.close();
	ifs.clear();
}