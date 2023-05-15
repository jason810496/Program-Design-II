
#ifndef _BASE_ENGINE_H_
#define _BASE_ENGINE_H_


#include <string>
#include <vector>

class BaseEngine{
	protected:
		int lineCount;
	public:
		BaseEngine() = default;
		~BaseEngine() = default;
		void setLineCount(const int & count){ lineCount = count; };
		virtual void insert(const int & id,const std::string & word){};
		virtual bool search(const std::vector<std::string> & search , std::vector<int> & result){};
};

#endif