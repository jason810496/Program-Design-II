#include "Parser.h"
#include<algorithm>

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
		lineCount = 0;	// init line count
		std::string line;
		while(getline(ifs, line)){

			int idx = 0;
			while(line[idx] != ','){
				idx++;
			}
			int id = strtoll(line.substr(0,idx).c_str(),NULL,10);
			
			while(line[idx] != '\"'){
				idx++;
			}
			
			std::string tmp = "";
			char c;
			while( idx < line.size() ){
				c = line[idx];
				if( c == ' '){
					if(tmp.size() > 0){
						std::cout<<tmp<<' ';
						tmp = "";
					}
					idx++;
					continue;
				}
				if( 'A' <= c && c <= 'Z' ){
					tmp += c - 'A' + 'a';
				}
				if( c < 'a' || 'z' < c ){
					idx++;
					continue;
				}
				tmp += c;
				idx++;
			}
			std::cout<<tmp<<' ';

		}
	}
	ifs.close();
	ifs.clear();
}

void Parser::readCorpus(const std::string & filename, BaseEngine* engine){
	

	ifs.open(filename, std::ios::in);
	if(ifs.is_open()){
		lineCount = 0;	// init line count
		std::string line;
		while(getline(ifs, line)){

			int idx = 0;
			while(line[idx] != ','){
				idx++;
			}
			int id = strtoll(line.substr(0,idx).c_str(),NULL,10);
			
			while(line[idx] != '\"'){
				idx++;
			}
			
			std::string tmp = "";
			char c;
			while( idx < line.size() ){
				c = line[idx];
				if( c == ' '){
					if(tmp.size() > 0){
						engine->insert(id, tmp);
						tmp = "";
					}
					idx++;
					continue;
				}
				if( 'A' <= c && c <= 'Z' ){
					tmp += c - 'A' + 'a';
				}
				if( c < 'a' || 'z' < c ){
					idx++;
					continue;
				}
				tmp += c;
				idx++;
			}
			engine->insert(id, tmp);
			lineCount++;
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
		
		// std::cout<<"line count : "<<lineCount<<"\n";
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

			std::cout<<answer[0];
			for(int i=1;i<answer.size();++i){
				std::cout<<' '<<answer[i];
			}
			std::cout<<'\n';

			query.clear();
			answer.clear();
		}
	}
	ifs.close();
	ifs.clear();
}