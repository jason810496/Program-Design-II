#include "Parser.h"

Parser::Parser(){}

Parser::~Parser(){}

std::string Parser::trim(const std::string & str){
	std::string result = "";
	for(const char & c : str){
		if( 'A' <= c && c <= 'Z' ){
			result += c - 'A' + 'a';
		}
		if( c < 'a' || 'z' < c ){
			continue;
		}
		result += c;
	}
	return result;
}

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

			std::vector<std::string> result;
			while(pars >> line && line.size() > 0){
				result.push_back( trim(line) );
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

void Parser::readCorpus(const std::string & filename, BaseEngine* engine){
	

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
				engine->insert(lineCount, trim(line) );
			}

			lineCount++; // next line
		}
	}
	ifs.close();
	ifs.clear();

	engine->setLineCount(lineCount);
}

void Parser::answerQuery(const std::string & filename, BaseEngine* engine){
	std::vector<std::string> query;
	std::vector<int> answer;
	query.reserve(1005);
	answer.reserve(1005);

	ifs.open(filename, std::ios::in);
	if(ifs.is_open()){
		lineCount = 1;	// init line count
		std::string line;
		while(getline(ifs, line)){
			// new line parsed
			pars.clear(); // init stream
			pars.str(line);
			
			while(pars >> line && line.size() > 0){
				query.push_back( trim(line) );
			}

			// output
			engine->search(query,answer);
			for(const int & id : answer){
				std::cout<<id<<' ';
			}
			std::cout<<'\n';

			query.clear();
			answer.clear();
		}
	}
	ifs.close();
	ifs.clear();
}