#define BASE_ENGINE_INCLUDED

#ifdef BASE_ENGINE_INCLUDED

#include <string>
#include <vector>

class BaseEngine{
	protected:
		int lineCount;
	public:
		BaseEngine();
		~BaseEngine();
		virtual void insert(const int & ithLine,const std::string & word);
		virtual bool search(const std::vector<std::string> & search , std::vector<std::string> & result);
};

#endif